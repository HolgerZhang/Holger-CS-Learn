//=======================================================================================
//文件名称：main.s
//功能概要：UART接收到字符串“open”时打开LED灯，接收到字符串“close”时关闭LED灯
//版权所有：张昊
//版本更新：20220610
//=======================================================================================
.include "include.inc"    //头文件中主要定义了程序中需要使用到的一些常量
//（0）数据段与代码段的定义
//（0.1）定义数据存储data段开始，实际数据存储在RAM中
.section .data
//（0.1.1）定义需要输出的字符串，标号即为字符串首地址,\0为字符串xfgi结束标志
instruction:
	.ascii "----------------------------------------------------------------------\n"
    .ascii "金葫芦提示：\n"
    .ascii "本实验主要实现的功能是：\n"
    .ascii "向串口发送字符串“open”或者“close”来控制开发板上的蓝色LED灯，\n"
    .ascii "MCU的UART接收到字符串“open”时打开LED灯，接收到字符串“close”时关闭LED灯\n"
    .ascii "----------------------------------------------------------------------\n\0"
light_on_string:
	.string "LED on!\r\n"
light_off_string:
	.string "LED off!\r\n"
.global light_on_string
.global light_off_string
//string_test:
//	.ascii "Assembly call  c's uart2!"
//（0.1.2）定义变量
.align 4               //.word格式四字节对齐
mMainLoopCount:		   //定义主循环次数变量
	.word 0
//mFlag:				   //定义灯的状态标志,1为亮，0为暗
//	.byte 'A'	
//.align 4
//mLightCount:
//    .word 0
.align 4
light_flag:			//灯的状态标志 L-亮 A-暗
	.word 'L'
.global light_flag
.align 4
recv_state:			//接收状态 0-7
	.word 0
.global recv_state

.equ MainLoopNUM,10000000  //主循环次数设定值（常量）

//（0.2）定义代码存储text段开始，实际代码存储在Flash中
.section   .text
.syntax unified           		  //指示下方指令为ARM和thumb通用格式
.thumb                    		  //Thumb指令集
.type main function               //声明main为函数类型
.global main               	      //将main定义成全局函数，便于芯片初始化之后调用
.align 2                          //指令和数据采用2字节对齐，兼容Thumb指令集

//----------------------------------------------------------------------                        
//声明使用到的内部函数
//main.c使用的内部函数声明处

//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程，参见书稿）
main:
//（1）======启动部分（开头）主循环前的初始化工作==========================================
//（1.1）声明main函数使用的局部变量

//（1.2）【不变】关总中断
	cpsid i   
//（1.3）给主函数使用的局部变量赋初值
	
//（1.4）给全局变量赋初值
	
//（1.5）用户外设模块初始化
//  初始化蓝灯, r0、r1、r2是gpio_init的入口参数
	ldr r0,=LIGHT_BLUE     //r0指明端口和引脚（用=，是因为常量>=256，且要用ldr指令）
	mov r1,#GPIO_OUTPUT    //r1指明引脚方向为输出
	mov r2,#LIGHT_ON       //r2指明引脚的初始状态为亮
	bl  gpio_init          //调用gpio初始化函数
//  初始化串口UARTA
	mov r0,#UARTA               //r0=更新串口
    ldr r1,=UART_BAUD
    bl  uart_init
//（1.6）使能模块中断
	mov r0,#UARTA               //r0指明串口号
    bl  uart_enable_re_int     //调用串口中断使能函数
//（1.7）【不变】开总中断
	cpsie  i  
	ldr r0,=instruction
	bl printf
	
	//bl .   //在此打桩(.表示当前地址)，理解发光二极管为何亮起来了？
	
//（1）======启动部分（结尾）==========================================

//（2）======主循环部分（开头）========================================
main_loop:                      //主循环标签（开头）
////（2.1）主循环次数变量mMainLoopCount+1
//		ldr r2,=mMainLoopCount     //r2←mMainLoopCount的地址
//		ldr r1, [r2]
//		add r1,#1
//		str r1,[r2]	
////（2.2）未达到主循环次数设定值，继续循环
//        ldr r2,=MainLoopNUM
//		cmp r1,r2
//		blO  main_loop     //未达到，继续循环
////（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理
////（2.3.1）清除循环次数变量
//		ldr r2,=mMainLoopCount     //r2←mMainLoopCount的地址
//		mov r1,#0
//		str r1,[r2]	
////（2.3.2）如灯状态标志mFlag为'L'，灯的闪烁次数+1并显示，改变灯状态及标志
//		//判断灯的状态标志
//		ldr r2,=mFlag		   
//		ldr r6,[r2]
//		cmp r6,#'L'			
//		bne main_light_off	   //mFlag不等于'L'转
//		//mFlag等于'L'情况
//		ldr r2,=mFlag           //灯的状态标志改为'A'
//		mov r7,#'A'
//		str r7,[r2]             
//		ldr r0,=LIGHT_BLUE      //亮灯
//		ldr r1,=LIGHT_ON
//		bl  gpio_set          
//		//mFlag等于'L'情况处理完毕，转
//		b main_exit  
////（2.3.3）如灯状态标志mFlag为'A'，改变灯状态及标志
//main_light_off:
//        ldr r2,=mFlag		   //灯的状态标志改为'L'
//		mov r7,#'L'
//		str r7,[r2]   
//        ldr r0,=LIGHT_BLUE      //暗灯
//		ldr r1,=LIGHT_OFF
//		bl  gpio_set  
//main_exit:
//	mov r0,#UARTA
//	ldr r1,=string_test
//	bl uart_send_string
	b main_loop                 //继续循环
//（2）======主循环部分（结尾）========================================
.end         //整个程序结束标志（结尾）
