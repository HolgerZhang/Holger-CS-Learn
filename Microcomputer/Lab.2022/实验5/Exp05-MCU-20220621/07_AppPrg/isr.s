//======================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：SD-ARM(sumcu.suda.edu.cn) 张昊
//更新记录：20220622
//======================================================================
.include "include.inc"

//start 函数定义区域
.global USART2_IRQHandler
.type  USART2_IRQHandler, function

.section   .text
.syntax unified           	
.thumb                   
.global SysTick_Handler
.type  SysTick_Handler, function
.align 2   


//end  函数定义区域

//========================中断函数服务例程===================================
.section .text
//======================================================================
//程序名称：UARTA_Handler（UARTA接收中断处理程序）
//触发条件：收到一个字节触发
//程序功能：接收PC机下发的时间
//======================================================================
USART2_IRQHandler:
	//（1）屏蔽中断，并且保存现场
	cpsid  i          //关可屏蔽中断
	push {r0-r7,lr}      //r7,lr进栈保护（r7后续申请空间用，lr中为进入中断前pc的值）
	//uint_8 flag
	sub sp,#4         //通过移动sp指针获取地址
	mov r7,sp         //将获取到的地址赋给r7
	//（2）接收字节
	mov r1,r7         //r1=r7 作为接收一个字节的地址
	mov r0,#UARTA		//r0指明串口号
	bl  uart_re1      //调用接收一个字节子函数
	ldr r1,=received_data
	str r0,[r1]		//保存接收到的数据
	//分状态处理  
	ldr r3,=recv_state
	ldr r2,[r3]
	cmp r2,#0         //State 0: num->1, other->8
	beq USART2_IRQHandler_state0
	cmp r2,#1         //State 1: num->2, other->8
	beq USART2_IRQHandler_state1
	cmp r2,#2         //State 2: ':'->3, other->8
	beq USART2_IRQHandler_state2
	cmp r2,#3         //State 3: num->4, other->8
	beq USART2_IRQHandler_state3
	cmp r2,#4         //State 4: num->5, other->8
	beq USART2_IRQHandler_state4
	cmp r2,#5         //State 5: ':'->6, other->8
	beq USART2_IRQHandler_state5
	cmp r2,#6         //State 6: num->7, other->8
	beq USART2_IRQHandler_state6
	cmp r2,#7         //State 7: num->10, other->8
	beq USART2_IRQHandler_state7
	cmp r2,#8         //State 8:[Start] $->9, other->8
	beq USART2_IRQHandler_state8
	cmp r2,#9         //State 9: $->0, other->8
	beq USART2_IRQHandler_state9
	cmp r2,#10         //State 10: #->11, other->8
	beq USART2_IRQHandler_state10
	cmp r2,#11         //State 11: #->set_new_time->8, other->8
	beq USART2_IRQHandler_state11
	bl  USART2_IRQHandler_exit
//Hour
USART2_IRQHandler_state0:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state0_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state0_other
	//收到字符0-9
	sub r0,r0,#'0'		//转为数字0-9
	ldr r1,=new_hour	//存入new_hour
	str r0,[r1]
	mov r0,#1			//转1
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state0_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state1:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state1_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state1_other
	//收到字符0-9
	sub r0,r0,#'0'		//转为数字0-9
	ldr r3,=new_hour	//new_hour=new_hour*10+r0
	ldr r1,[r3]
	mov r2,#10
	mul r1,r2,r1
	add r0,r0,r1
	str r0,[r3]
	mov r0,#2			//转2
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state1_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state2:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#':'
	bne USART2_IRQHandler_state2_other
	//收到冒号
	mov r0,#3			//转3
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state2_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
//Minute
USART2_IRQHandler_state3:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state3_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state3_other
	//收到字符0-9
	sub r0,r0,#'0'		//转为数字0-9
	ldr r1,=new_minute	//存入new_minute
	str r0,[r1]
	mov r0,#4			//转4
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state3_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state4:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state4_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state4_other
	//收到字符0-9
	sub r0,r0,#'0'		//转为数字0-9
	ldr r3,=new_minute	//new_minute=new_minute*10+r0
	ldr r1,[r3]
	mov r2,#10
	mul r1,r2,r1
	add r0,r0,r1
	str r0,[r3]
	mov r0,#5			//转5
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state4_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state5:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#':'
	bne USART2_IRQHandler_state5_other
	//收到冒号
	mov r0,#6			//转6
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state5_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
//Second
USART2_IRQHandler_state6:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state6_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state6_other
	//收到字符0-9
	sub r0,r0,#'0'		//转为数字0-9
	ldr r1,=new_second	//new_second
	str r0,[r1]
	mov r0,#7			//转7
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state6_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state7:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state7_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state7_other
	//收到字符0-9
	sub r0,r0,#'0'		//转为数字0-9
	ldr r3,=new_second	//new_second=new_second*10+r0
	ldr r1,[r3]
	mov r2,#10
	mul r1,r2,r1
	add r0,r0,r1
	str r0,[r3]
	mov r0,#10			//转10
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state7_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state8:
	//重置接收到的时间
	mov r0,#0
	ldr r1,=new_hour
	str r0,[r1]
	ldr r1,=new_minute
	str r0,[r1]
	ldr r1,=new_second
	str r0,[r1]
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'$'
	bne USART2_IRQHandler_state8_other
	//收到$
	mov r0,#9			//转9
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state8_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state9:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	//收到$
	cmp r0,#'$'
	bne USART2_IRQHandler_state9_other
	mov r0,#0			//转0
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state9_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state10:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	//收到#
	cmp r0,#'#'
	bne USART2_IRQHandler_state10_other
	mov r0,#11			//转11
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state10_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state11:
	//处理收到的字节
	ldr r0,=received_data
	ldr r0,[r0]
	//收到#
	cmp r0,#'#'
	bne USART2_IRQHandler_state11_other
	//set_time:
	ldr r0,=new_hour
	ldr r0,[r0]
	cmp r0,#23		//新小时>23
	bhi USART2_IRQHandler_state11_other
	ldr r1,=new_minute
	ldr r1,[r1]
	cmp r1,#59		//新分钟>59
	bhi USART2_IRQHandler_state11_other
	ldr r2,=new_second
	ldr r2,[r2]
	cmp r2,#59		//新秒数>59
	bhi USART2_IRQHandler_state11_other
	//只有正确时间格式才存入
	ldr r3,=hour
	str r0,[r3]
	ldr r3,=minute
	str r1,[r3]
	ldr r3,=second
	str r2,[r3]
	mov r0,#60
	ldr r1,=last_second
	str r0,[r1]
	ldr r1,=gcount
	mov r0,#0
	str r0,[r1]
USART2_IRQHandler_state11_other:
	mov r0,#8			//转8
	ldr r1,=recv_state
	str r0,[r1]
	//（4）解除屏蔽，并且恢复现场
USART2_IRQHandler_exit:
	cpsie   i         //解除屏蔽中断
	add r7,#4         //还原r7
	mov sp,r7         //还原sp
	pop {r0-r7,pc}       //r7,pc出栈，还原r7的值；pc←lr,即返回中断前程序继续执行



//===================================================================
//函数名称：SysTick_Handler
//参数说明：无
//函数返回：无
//功能概要：SysTick定时器中断服务例程
//===================================================================
SysTick_Handler:
	push {r0,r1,r2,lr}
	ldr r0,=gcount
	ldr r1,[r0]
	cmp r1,#50
	bcs SysTick_Handler_1s
	add r1,#1
	str r1,[r0]
	b   SysTick_Handler_Exit
SysTick_Handler_1s:
    mov r1,#0
    str r1,[r0]
    b   add_sec
SysTick_Handler_Exit:
    pop {r0,r1,r2,pc} 
     
    
add_sec:
    ldr r0,=second
    ldr r1,[r0]
    cmp r1,#59
    bcs sec60  //秒>=59
    add r1,#1
    str r1,[r0]//秒<59
    b   add_sec_exit
sec60:         //秒>=59
    mov r1,#0
    str r1,[r0]
    ldr r0,=minute
    ldr r1,[r0]
    cmp r1,#59
    bcs min60  //分>=59
    add r1,#1
    str r1,[r0]//分<59
    b   add_sec_exit
min60:         //分>=59
    mov r1,#0
    str r1,[r0]
    ldr r0,=hour
    ldr r1,[r0]
    cmp r1,#23
    bcs hour23  //时>=23
    add r1,#1
    str r1,[r0]//时<23
    b   add_sec_exit
hour23:
    mov r1,#0
    str r1,[r0]
add_sec_exit: 
    b   SysTick_Handler_Exit
    
    