//======================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//更新记录：20220621
//======================================================================
.include "include.inc"
.align 2
//start 函数定义区域
.type  USART2_IRQHandler, function
.global USART2_IRQHandler
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
	push  {r0-r7,lr}   //r7,lr进栈保护（r7后续申请空间用，lr中为进入中断前pc的值）
	//uint_8 flag
	sub sp,#4         //通过移动sp指针获取地址
	mov r7,sp         //将获取到的地址赋给r7
	//接收字节
	mov r1,r7         //r1=r7 作为接收一个字节的地址
 	mov r0,#UART_User		//串口号
 	bl  uart_re1      	//调用接收一个字节子函数
 	ldr r1,=0x20003000  //接收到数据部分的存入地址gcRecvBuf
	bl  emuart_frame  //调用帧解析函数,r0=数据部分长度
	cmp r0,#0			//若成功解析帧格式，跳转协议解析
	bne USART2_IRQHandler_success_revc
	//否则直接退出
	bl  USART2_IRQHandler_exit    //break
USART2_IRQHandler_success_revc:
	//握手协议: (byte)11, (byte)'a', (byte)'u', (byte)'a', (byte)'r', (byte)'t', (byte)'?'
	ldr r0,=0x20003000
	ldrb r0,[r0]		//读取数据部分第一位->r0
	cmp r0,#11		//判断握手协议
	bne USART2_IRQHandler_next
	ldr r0,=handshake_check_str	//string1
	ldr r1,=0x20003000
	add r1,#1			//string2
	mov r2,#6			//字符串长度
	bl cmp_string
	cmp r0,#0
	bne USART2_IRQHandler_next	//不是握手协议
	//与上位机握手，确立通信关系
	mov r0,#UARTA
	ldr r1,=handshake_send_str
	bl  uart_send_string
	//亮蓝灯，约1s后熄灭
	bl Light_Connected
	bl USART2_IRQHandler_exit    //break
USART2_IRQHandler_next:
	ldr r0,=0x20003000
	ldrb r0,[r0]		//读取数据部分第一位（指令）->r0
 	cmp r0,#7			//大于7，指令无效
 	bhi USART2_IRQHandler_exit
	ldr r1,=mLightCommand
	str r0,[r1]			//指令保存至mLightCommand变量
	//调用Light_Control
	bl  Light_Control
	ldr r1,=success_command_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
USART2_IRQHandler_exit:
	//解除屏蔽，并且恢复现场
	cpsie   i         //解除屏蔽中断
	add r7,#4         //还原r7
	mov sp,r7         //还原sp
	pop {r0-r7,pc}    //r7,pc出栈，还原r7的值；pc←lr,即返回中断前程序继续执行
      
      
//========================内部函数===================================
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
//程序名称：Light_Control
//参数说明：无
//返回值说明：无
//程序功能：根据灯指令（mLightCommand），对LED灯进行操作
//  1=》红灯亮  2=》蓝灯亮  3=》绿灯亮  4=》青灯亮(蓝,绿)
//  5=》紫灯亮(蓝,红)  6=》黄灯亮(红,绿)  7=》白灯亮(红,蓝,绿)  0=》所有灯灭
//======================================================================
Light_Control:
	push {r0-r7,lr}
	//首先关掉所有的灯
	ldr r0,=LIGHT_RED //灭红灯
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_GREEN //灭绿灯
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_BLUE //灭蓝灯
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	//读取灯指令保存至r0
	ldr r0,=mLightCommand
	ldr r0,[r0]
	//判断r0是不是0
	cmp r0,#0
	bne Light_Control_case_1	//不为0，判断并亮灯
	//若为0直接结束
	ldr r1,=light_off_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
	bl  Light_Control_exit
Light_Control_case_1:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#1
	bne Light_Control_case_2			//不等于1转判断2
	//等于1的情况:RED
	ldr r0,=LIGHT_RED
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_red_on_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
	b Light_Control_exit			//break
Light_Control_case_2:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#2
	bne Light_Control_case_3			//不等于2转判断3
	//等于2的情况:BLUE
	ldr r0,=LIGHT_BLUE
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_blue_on_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
	b Light_Control_exit			//break
Light_Control_case_3:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#3
	bne Light_Control_case_4			//不等于3转判断4
	//等于5的情况:GREEN
	ldr r0,=LIGHT_GREEN
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_green_on_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
	b Light_Control_exit			//break
Light_Control_case_4:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#4
	bne Light_Control_case_5			//不等于4转判断5
	//等于4的情况:BLUE+GREEN
	ldr r0,=LIGHT_BLUE
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_GREEN
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_cyan_on_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
	b Light_Control_exit			//break
Light_Control_case_5:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#5
	bne Light_Control_case_6			//不等于5转判断6
	//等于5的情况:RED+BLUE
	ldr r0,=LIGHT_RED
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_BLUE
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_purple_on_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
	b Light_Control_exit			//break
Light_Control_case_6:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#6
	bne Light_Control_case_7			//不等于6转判断7
	//等于6的情况:RED+GREEN
	ldr r0,=LIGHT_RED
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_GREEN
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_yellow_on_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
	b Light_Control_exit			//break
Light_Control_case_7:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#7
	bne Light_Control_exit			//不等于1转判断2
	//等于7的情况:RED+BLUE+GREEN
	ldr r0,=LIGHT_RED
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_BLUE
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_GREEN
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_white_on_string		//r1指明字符串
 	mov r0,#UART_User        //串口号
	bl  uart_send_string    //向原串口回发
Light_Control_exit:	
	pop  {r0-r7,pc}


//======================================================================
//程序名称：Light_Connected
//参数说明：无
//返回值说明：无
//程序功能：点亮蓝灯，连接成功后调用
//======================================================================
Light_Connected:
	push {r0-r7,lr}
	//首先关掉所有的灯
	ldr r0,=LIGHT_RED //灭红灯
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_GREEN //灭绿灯
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_BLUE //灭蓝灯
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_BLUE //亮蓝灯
	ldr r1,=LIGHT_ON
	bl  gpio_set
Light_Connected_exit:	
	pop  {r0-r7,pc}
