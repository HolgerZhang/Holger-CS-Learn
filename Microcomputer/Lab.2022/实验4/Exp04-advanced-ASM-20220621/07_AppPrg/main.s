//=======================================================================================
//文件名称：main.s
//功能概要：上位机通过串口调试软件发送指令（数字）控制三色LED灯
//版权所有：张昊
//版本更新：20220621
//=======================================================================================
.include "include.inc"    //头文件中主要定义了程序中需要使用到的一些常量
//（0）数据段与代码段的定义
//（0.1）定义数据存储data段开始，实际数据存储在RAM中
.section .data
//（0.1.1）定义需要输出的字符串，标号即为字符串首地址,\0为字符串xfgi结束标志
instruction:
	.ascii "----------------------------------------------------------------------\n"
    .ascii "金葫芦提示：\n"
    .ascii "本实验主要实现的功能是：上位机通过串口调试软件发送指令（数字）控制三色LED灯\n"
    .ascii "  1=》红灯亮  2=》蓝灯亮  3=》绿灯亮  4=》青灯亮\n"
    .ascii "  5=》紫灯亮  6=》黄灯亮  7=》白灯亮  0=》所有灯灭\n"
    .ascii "----------------------------------------------------------------------\n\0"
print_command_string:
	.string "Command #%d: %d\r\n"		//打印指令信息
success_command_string:
	.string "Command executed!\r\n"		//串口返回的信息（成功执行）
unknown_command_string:
	.string "Unknown command!\r\n"		//串口返回的信息（未知指令）
.global print_command_string
.global success_command_string
.global unknown_command_string
//灯亮状态输出字符串
light_red_on_string:
	.string "[RED LED ON] "
.global light_red_on_string
light_blue_on_string:
	.string "[BLUE LED ON] "
.global light_blue_on_string
light_green_on_string:
	.string "[GREEN LED ON] "
.global light_green_on_string
light_cyan_on_string:
	.string "[CYAN LED ON] "
.global light_cyan_on_string
light_purple_on_string:
	.string "[PURPLE LED ON] "
.global light_purple_on_string
light_yellow_on_string:
	.string "[YELLOW LED ON] "
.global light_yellow_on_string
light_white_on_string:
	.string "[WHITE LED ON] "
.global light_white_on_string
light_off_string:
	.string "[LED OFF] "
.global light_off_string

//握手字符串
handshake_check_str:
	.string "auart?"
.global handshake_check_str
handshake_send_str:
	.string "I am an uart"
.global handshake_send_str

//（0.1.2）定义变量
.align 4               //.word格式四字节对齐
mMainLoopCount:		   //定义主循环次数变量，数据格式为字，初始值为0
	.word 0
.global mMainLoopCount
.align 4               //.word格式四字节对齐
mLightCommand:			//定义灯控制命令
	.word 0
.global mLightCommand

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
//  初始化LED灯, r0、r1、r2是gpio_init的入口参数
	ldr r0,=LIGHT_BLUE     //r0指明端口和引脚（用=，是因为常量>=256，且要用ldr指令）
	mov r1,#GPIO_OUTPUT    //r1指明引脚方向为输出
	mov r2,#LIGHT_ON       //r2指明引脚的初始状态为亮
	bl  gpio_init          //调用gpio初始化函数
	ldr r0,=LIGHT_RED     //r0指明端口和引脚（用=，是因为常量>=256，且要用ldr指令）
	mov r1,#GPIO_OUTPUT    //r1指明引脚方向为输出
	mov r2,#LIGHT_ON       //r2指明引脚的初始状态为亮
	bl  gpio_init          //调用gpio初始化函数
	ldr r0,=LIGHT_GREEN     //r0指明端口和引脚（用=，是因为常量>=256，且要用ldr指令）
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
	b main_loop                 //死循环
//（2）======主循环部分（结尾）========================================

.end         //整个程序结束标志（结尾）
