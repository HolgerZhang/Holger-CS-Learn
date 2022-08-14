//======================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//更新记录：20220610
//======================================================================
.include "include.inc"
.align 2
//start 函数定义区域
.type  USART2_IRQHandler, function
.global USART2_IRQHandler
//end  函数定义区域

/*
自动机：
   1 -p- 2 -e- 3 -n- 0(openLED)
  /o
0
 c\ 
   5 -l- 6 -o- 7 -s- 8 -e- 0(closeLED)
*/

//========================中断函数服务例程===================================
.section .text
//======================================================================
//程序名称：UARTA_Handler（UARTA接收中断处理程序）
//触发条件：收到一个字节触发
//程序功能：回发接收到的字节
//======================================================================
USART2_IRQHandler:
//（1）屏蔽中断，并且保存现场
	cpsid  i          //关可屏蔽中断
	push {r7,lr}      //r7,lr进栈保护（r7后续申请空间用，lr中为进入中断前pc的值）
	//uint_8 flag
	sub sp,#4         //通过移动sp指针获取地址
	mov r7,sp         //将获取到的地址赋给r7
//（2）接收字节
	mov r1,r7         //r1=r7 作为接收一个字节的地址
	mov r0,#UARTA		//r0指明串口号
	bl  uart_re1      //调用接收一个字节子函数
	//处理接受到的信息  
	ldr r3,=recv_state
	ldr r2,[r3]
	cmp r2,#0         //State 0: o->1, c->5, other->0
	beq state0
	cmp r2,#1         //State 1: open, p->2, other->0
	beq state1
	cmp r2,#2         //State 2: open, e->3, other->0
	beq state2
	cmp r2,#3         //State 3: open, n->openLED->0
	beq state3
	cmp r2,#5         //State 5: close, l->6, other->0
	beq state5
	cmp r2,#6         //State 5: close, o->7, other->0
	beq state6
	cmp r2,#7         //State 6: close, s->8, other->0
	beq state7
	cmp r2,#8         //State 7: close, e->closeLED->0
	beq state8
state0:
	cmp r0,#'o'		//o->1
	bne state0_c
	mov r2,#1
	str r2,[r3]
	bl USART2_IRQHandler_exit
state0_c:
	cmp r0,#'c'		//c->5
	bne state0_other
	mov r2,#5
	str r2,[r3]
	bl USART2_IRQHandler_exit
state0_other:
	mov r2,#0		//other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state1:
	cmp r0,#'p'       //p->2
	bne state1_other
	mov r2,#2
	str r2,[r3]
	bl USART2_IRQHandler_exit
state1_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state2:
	cmp r0,#'e'       //e->3
	bne state2_other
	mov r2,#3
	str r2,[r3]
	bl USART2_IRQHandler_exit
state2_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state3:
	cmp r0,#'n'       //n->openLED
	bne state3_other
	//LED ON
	bl led_on_caller
state3_other:
	mov r2,#0         //all->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state5:
	cmp r0,#'l'       //l->6
	bne state5_other
	mov r2,#6
	str r2,[r3]
	bl USART2_IRQHandler_exit
state5_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state6:
	cmp r0,#'o'       //o->7
	bne state6_other
	mov r2,#7
	str r2,[r3]
	bl USART2_IRQHandler_exit
state6_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state7:
	cmp r0,#'s'       //s->8
	bne state7_other
	mov r2,#8
	str r2,[r3]
	bl USART2_IRQHandler_exit
state7_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state8:
	cmp r0,#'e'       //e->closeLED
	bne state8_other
	//LED OFF
	bl led_off_caller
state8_other:
	mov r2,#0         //all->0
	str r2,[r3] 
USART2_IRQHandler_exit:
//（3）发送字节
//	mov r1,r0			//r1存放串口接收到的数据，作为uart_send1的入口参数
//	mov r0,#UARTA		//r0指明串口号
//	bl  uart_send1    //向原串口回发
//（4）解除屏蔽，并且恢复现场
	cpsie   i         //解除屏蔽中断
	add r7,#4         //还原r7
	mov sp,r7         //还原sp
	pop {r7,pc}       //r7,pc出栈，还原r7的值；pc←lr,即返回中断前程序继续执行

led_on_caller:
	push {r0-r7,lr}
	ldr r0,=LIGHT_BLUE	//暗灯
	ldr r1,=LIGHT_ON
	bl  gpio_set
	mov r0,#UARTA		//Light on
	ldr r1,=light_on_string
	bl uart_send_string
	pop {r0-r7,pc}

led_off_caller:
	push {r0-r7,lr}
	ldr r0,=LIGHT_BLUE	//暗灯
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	mov r0,#UARTA		//Light off
	ldr r1,=light_off_string
	bl uart_send_string
	pop {r0-r7,pc}