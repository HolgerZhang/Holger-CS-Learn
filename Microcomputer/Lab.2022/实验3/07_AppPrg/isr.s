//======================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//更新记录：2019-09-27 V1.0
//======================================================================
.include "include.inc"

//start 函数定义区域
.type  USART2_IRQHandler, function
.global USART2_IRQHandler
.type  cmp_string, function
.type  data_isempty, function
//end  函数定义区域

//========================中断函数服务例程===================================
.section .text
//======================================================================
//程序名称：UARTA_Handler（UARTA接收中断处理程序）
//触发条件：收到一个字节触发
//程序功能：回发接收到的字节
//======================================================================
USART2_IRQHandler:
//屏蔽中断，并且保存现场
      cpsid  i          //关可屏蔽中断
      push {r0-r7,lr}      //r0-r7,lr进栈保护（r7后续申请空间用，lr中为进入中断前pc的值）
      //uint_8 flag
	  sub sp,#4         //通过移动sp指针获取地址
	  mov r7,sp         //将获取到的地址赋给r7
//接收字节
      mov r1,r7         //r1=r7 作为接收一个字节的地址
      mov r0,#UARTA		//r0指明串口号
      bl  uart_re1      //调用接收一个字节子函数，接收到的存到r0
      ldr r1,=0x20003000  //接收到数据部分的存入地址gcRecvBuf
      bl  emuart_frame  //调用帧解析函数,r0=数据部分长度
      cmp r0,#0			//若成功解析帧格式，跳转协议解析
      bne UARTA_IRQHandler_success_revc
      //否则直接退出
      bl UARTA_IRQHandler_finish    //break
UARTA_IRQHandler_success_revc:
      //握手协议: (byte)11, (byte)'a', (byte)'u', (byte)'a', (byte)'r', (byte)'t', (byte)'?'
      ldr r0,=0x20003000
      ldrb r0,[r0]		//读取数据部分第一位->r0
      cmp r0,#11		//判断握手协议
      bne UARTA_IRQHandler_next_r
      ldr r0,=handshake_check_str	//string1
      ldr r1,=0x20003000
      add r1,#1			//string2
      mov r2,#6			//字符串长度
      bl cmp_string
      cmp r0,#0
      bne UARTA_IRQHandler_next_r	//不是握手协议
      //与上位机握手，确立通信关系
      mov r0,#UARTA
      ldr r1,=handshake_send_str
      bl  uart_send_string
      bl UARTA_IRQHandler_finish    //break
UARTA_IRQHandler_next_r:
      //读逻辑地址: "r"+扇区号1B+偏移量(2B)+读字节数1B
      ldr r0,=0x20003000
      ldrb r0,[r0]		//读取数据部分第一位->r0
      cmp r0,#'r'		//读取（按逻辑地址）
      bne UARTA_IRQHandler_next_a
      //flash_read_logic(flash_ContentDetail,gcRecvBuf[1],(gcRecvBuf[2]<<8)|gcRecvBuf[3],gcRecvBuf[4]);
      ldr r0,=flash_ContentDetail
      ldr r1,=0x20003000
      add r1,#1
      ldrb r1,[r1]		//r1=gcRecvBuf[1]
      ldr r2,=0x20003000
      add r2,#2
      ldrb r2,[r2]
      lsl r2,r2,#8		//r2=gcRecvBuf[2]<<8
      ldr r3,=0x20003000
      add r3,#3
      ldrb r3,[r3]		//gcRecvBuf[3]
      orr r2,r2,r3		//r2=(gcRecvBuf[2]<<8)|gcRecvBuf[3]
      ldr r3,=0x20003000
      add r3,#4
      ldrb r3,[r3]		//r3=gcRecvBuf[4]
      bl flash_read_logic
      //判空
      ldr r0,=flash_ContentDetail
      ldr r1,=0x20003000
      add r1,#4
      ldrb r1,[r1]		//r1=gcRecvBuf[4]
      bl data_isempty
      cmp r0,#0
      beq UARTA_IRQHandler_next_r_empty  //为空跳转
      //不为空，发送数据
      mov r0,#UARTA
      ldr r1,=0x20003000
      add r1,#4
      ldrb r1,[r1]		//r1=gcRecvBuf[4]
      ldr r2,=flash_ContentDetail
      bl uart_sendN
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_r_empty:
      //为空，发送空信息
      mov r0,#UARTA
      ldr r1,=flash_str1
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_a:
      //读物理地址: "a"+地址4B+读字节数1B
      ldr r0,=0x20003000
      ldrb r0,[r0]		//读取数据部分第一位->r0
      cmp r0,#'a'		//读取（按物理地址）
      bne UARTA_IRQHandler_next_w
      //flash_read_physical(flashRead,(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)|(gcRecvBuf[3]<<8)|gcRecvBuf[4],gcRecvBuf[5]);
      ldr r0,=flash_ContentDetail
      ldr r1,=0x20003000
      add r1,#1
      ldrb r1,[r1]
      lsl r1,r1,#24		//r1=gcRecvBuf[1]<<24
      ldr r2,=0x20003000
      add r2,#2	
      ldrb r2,[r2]
      lsl r2,r2,#16		//gcRecvBuf[2]<<16
      orr r1,r1,r2		//r1=(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)
      ldr r2,=0x20003000
      add r2,#3
      ldrb r2,[r2]
      lsl r2,r2,#8		//gcRecvBuf[3]<<8
      orr r1,r1,r2		//r1=(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)|(gcRecvBuf[3]<<8)
      ldr r2,=0x20003000
      add r2,#4
      ldrb r2,[r2]		//gcRecvBuf[4]
      orr r1,r1,r2		//r1=(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)|(gcRecvBuf[3]<<8)|gcRecvBuf[4]
      ldr r2,=0x20003000
      add r2,#5
      ldrb r2,[r2]		//r2=gcRecvBuf[5]
      bl flash_read_physical
      //判空
      ldr r0,=flash_ContentDetail
      ldr r1,=0x20003000
      add r1,#5
      ldrb r1,[r1]		//r1=gcRecvBuf[5]
      bl data_isempty
      cmp r0,#0
      beq UARTA_IRQHandler_next_a_empty  //为空跳转
      //不为空，发送数据
      mov r0,#UARTA
      ldr r1,=0x20003000
      add r1,#5
      ldrb r1,[r1]		//r1=gcRecvBuf[5]
      ldr r2,=flash_ContentDetail
      bl uart_sendN
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_a_empty:
      //为空，发送空信息
      mov r0,#UARTA
      ldr r1,=flash_str1
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_w:
      //写入: "w"+扇区号1B+偏移量(2B)+写入字节数1B+写入数据nB
      ldr r0,=0x20003000
      ldrb r0,[r0]		//读取数据部分第一位->r0
      cmp r0,#'w'		//写入
      bne UARTA_IRQHandler_next_e
      //写入前先擦除：flash_erase(gcRecvBuf[1]);
      ldr r0,=0x20003000
      add r0,#1
      ldrb r0,[r0]		//r0=gcRecvBuf[1]
      bl flash_erase
      cmp r0,#0
      bne UARTA_IRQHandler_next_w_failed  //不为0,跳转失败
      //flash_write(gcRecvBuf[1], (gcRecvBuf[2]<<8)|gcRecvBuf[3],gcRecvBuf[4],&gcRecvBuf[5]);
      ldr r0,=0x20003000
      add r0,#1
      ldrb r0,[r0]		//r0=gcRecvBuf[1]
      ldr r1,=0x20003000
      add r1,#2
      ldrb r1,[r1]
      lsl r1,r1,#8		//r1=gcRecvBuf[2]<<8
      ldr r2,=0x20003000
      add r2,#3
      ldrb r2,[r2]		//gcRecvBuf[3]
      orr r1,r1,r2		//r1=(gcRecvBuf[2]<<8)|gcRecvBuf[3]
      ldr r2,=0x20003000
      add r2,#4
      ldrb r2,[r2]		//r2=gcRecvBuf[4]
      ldr r3,=0x20003000
      add r3,#5			//r3=&gcRecvBuf[5]
      bl flash_write
      cmp r0,#0
      bne UARTA_IRQHandler_next_w_failed  //不为0,跳转失败
      //为0，写入成功
      mov r0,#UARTA
      ldr r1,=flash_str5
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_w_failed:
      //写入失败
      mov r0,#UARTA
      ldr r1,=flash_str6
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
//      //TEST recv
//      mov r0,#UARTA
//      ldr r1,=0x20003000
//      add r1,#1
//      ldrb r1,[r1]		//r1=gcRecvBuf[1]
//      bl uart_send1
//      mov r0,#UARTA
//      ldr r1,=0x20003000
//      add r1,#2
//      ldrb r1,[r1]		//r1=gcRecvBuf[2]
//      bl uart_send1
//      mov r0,#UARTA
//      ldr r1,=0x20003000
//      add r1,#3
//      ldrb r1,[r1]		//gcRecvBuf[3]
//      bl uart_send1
//      mov r0,#UARTA
//      ldr r1,=0x20003000
//      add r1,#4
//      ldrb r1,[r1]		//r1=gcRecvBuf[4]
//      ldr r2,=0x20003000
//      add r2,#5			//r2=&gcRecvBuf[5]
//      bl uart_sendN
//      bl UARTA_IRQHandler_finish  //break
//      //TEST revc end
UARTA_IRQHandler_next_e:
      //擦除: "e"+扇区号1B
      ldr r0,=0x20003000
      ldrb r0,[r0]		//读取数据部分第一位->r0
      cmp r0,#'e'		//擦除
      bne UARTA_IRQHandler_next_default
      //flash_erase(gcRecvBuf[1]);
      ldr r0,=0x20003000
      add r0,#1
      ldrb r0,[r0]		//r0=gcRecvBuf[1]
      bl flash_erase
      cmp r0,#0
      bne UARTA_IRQHandler_next_e_failed  //不为0,跳转失败
      //为0，擦除成功
      mov r0,#UARTA
      ldr r1,=flash_str3
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_e_failed:
      //擦除失败
      mov r0,#UARTA
      ldr r1,=flash_str4
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_default:  //default
      ldr r1,=unknown_info_str
      mov r0,#UARTA		//r0指明串口号
      bl  uart_send_string
//解除屏蔽，并且恢复现场
UARTA_IRQHandler_finish:
      cpsie   i         //解除屏蔽中断
      add r7,#4         //还原r7
      mov sp,r7         //还原sp
      pop {r0-r7,pc}       //r0-r7,pc出栈，还原r7的值；pc←lr,即返回中断前程序继续执行


//=========================内部函数====================================
//======================================================================
//函数名称：cmp_string
//函数参数：r0-string1，r1-string2，r2-字符串长度
//函数返回：0-相同，1-不同
//函数功能：比较两字符串是否相同
//======================================================================
cmp_string:
	push {r1-r7,lr}
	mov r3,#0	//计数变量
	mov r7,#0	//result, 0=eq, 1=neq
cmp_string_loop:
	cmp r3,r2	//若r3>=r2，结束循环
	bge cmp_string_exit
	ldrb r4,[r0,r3]	//r4=r0[r3]
	ldrb r5,[r1,r3]	//r4=r1[r3]
	add r3,#1	//r3++
	cmp r4,r5	//若相等，继续循环
	beq cmp_string_loop
	mov r7,#1	//不相等，r6=1，结束循环
cmp_string_exit:
	mov r0,r7
	pop {r1-r7,pc}

//======================================================================
//函数名称：data_isempty
//函数参数：r0-data，r1-长度
//函数返回：0-empty，1-not
//函数功能：检查读出的data数组是否为空
//======================================================================
data_isempty:
	push {r1-r7,lr}
	mov r2,#0	//计数变量
	mov r3,#0	//0-empty，1-not
data_isempty_loop:
	cmp r2,r1	//若r2>=r1，结束循环
	bge data_isempty_exit
	ldrb r4,[r0,r2] //r4=r0[r2]
	add r2,#1		//r2++
	cmp r4,#0xff  //若相等，继续循环
	beq data_isempty_loop
	//若不等，则有数据，不为空，结束循环
	mov r3,#1
data_isempty_exit:
	mov r0,r3
	pop {r1-r7,pc}
	
