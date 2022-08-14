//=======================================================================================
//文件名称：main.s
//功能概要：Flash扇区操作验证试验（利用printf输出提示信息）
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//版本更新：20180810-20201129
//=======================================================================================
.include "include.inc"    //头文件中主要定义了程序中需要使用到的一些常量
//（0）数据段与代码段的定义
//（0.1）定义数据存储data段开始，实际数据存储在RAM中
.section .data
//（0.1.1）定义需要输出的字符串，标号即为字符串首地址,\0为字符串xfgi结束标志
hello_information:           //字符串标号
    .ascii "----------------------------------------------------------------------\n"
    .ascii "金葫芦提示：\n"
    .ascii "           Flash扇区操作验证试验                                       \n"
    .ascii "     Flash扇区有固定的檫除次数，若频繁檫除，可能损坏Flash扇区           \n"
    .ascii "     所以，Flash操作只在芯片上电，程序下载的时候进行一次                \n"        
    .ascii "----------------------------------------------------------------------\n\0"
data_format:
    .ascii "%d\n\0"                 //printf使用的数据格式控制符
	
	
//------------------------------------flash构件相关提示--------------------------------
type_str:
    .string "Flash操作结果提示：64扇区前32字节内容为： %s"

str_1:            			           //字符串标签
    .string "Assembly call c's printf!\r\n"  //使用说明见01_Doc下文档
str_2:            			           //字符串标签
    .string "Assembly call c's UARTA!\r\n"   //使用说明见01_Doc下文档

flash_str1:
    .string "Flash操作结果提示：该扇区内容为空!\r\n"             //flash判空结果提示语句，
flash_str2:
	.string "Flash操作结果提示：该扇区内容不为空!!!!!\r\n"    //flash判空结果提示语句，
flash_str3:
    .string "Flash操作结果提示：扇区内容擦除成功!\r\n"             //flash擦除结果提示语句，
flash_str4:
	.string "Flash操作结果提示：扇区内容擦除不成功!!!!!\r\n"    //flash擦除结果提示语句，
flash_str5:
    .string "Flash操作结果提示：扇区内容写入成功!\r\n"             //flash写入结果提示语句，
flash_str6:
	.string "Flash操作结果提示：扇区内容写入不成功!!!!!\r\n"    //flash写入结果提示语句，
.global flash_str1
.global flash_str2
.global flash_str3
.global flash_str4
.global flash_str5
.global flash_str6

unknown_info_str:
	.string "未知的操作！\r\n"
.global unknown_info_str

info_str1:
	.string "Flash操作提示：判断64扇区内容是否为空！\r\n"    //Flash判空结果提示语句，
info_str2:
	.string "Flash操作提示：擦除64扇区，然后再判断64扇区是否为空，看檫除操作是否成功！\r\n"    //flash判空结果提示语句，
info_str3:
	.string "Flash操作提示：向64扇区指定地址写入数据，再读出写入的数据，看有无错误!\r\n"    //flash判空结果提示语句，

flash_Content:
	.string "Welcome to Soochow University!\r\n"    //即将要写入Flash的内容

flash_ContentDetail:
	.string "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n"   //存储从Flash中读出的数据
.global flash_ContentDetail
	
//dataRecvBuff:	//接收到的数据部分
//	.ascii "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
//.global dataRecvBuff

handshake_check_str:
	.string "auart?"
.global handshake_check_str

handshake_send_str:
	.string "I am an uart"
.global handshake_send_str

.equ addr,0x8020000	   //64扇区首地址

number:
  .word  0x800

	
	
//（0.1.2）定义变量
.align 4               //.word格式四字节对齐
mMainLoopCount:		   //定义主循环次数变量
	.word 0
mFlag:				   //定义灯的状态标志,1为亮，0为暗
	.byte 'A'	
.align 4
mLightCount:
    .word 0

.equ MainLoopNUM,556677  //主循环次数设定值（常量）

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
	//初始化蓝灯, r0、r1、r2是gpio_init的入口参数
	ldr r0,=LIGHT_BLUE     //r0指明端口和引脚（用=，是因为常量>=256，且要用ldr指令）
	mov r1,#GPIO_OUTPUT    //r1指明引脚方向为输出
	mov r2,#LIGHT_ON       //r2指明引脚的初始状态为亮
	bl  gpio_init          //调用gpio初始化函数
    //Flash初始化
    bl  flash_init
    //初始化串口UARTA
	mov r0, #UARTA
    ldr r1, =UART_BAUD
	bl  uart_init

//（1.6）使能模块中断
	mov r0, #UARTA			//r0指明串口号
    bl  uart_enable_re_int	//调用串口中断使能函数
//（1.7）【不变】开总中断
	cpsie  i  

	ldr r0,=hello_information   //r0=待显示字符串
	bl  printf		            //调用printf显示字符串

//（1.8）对Flash的操作
	//判断64扇区是否为空
	//输出提示信息“Flash操作提示：判断64扇区内容是否为空！”
	mov r0, #UART_User		//向串口发送信息
	ldr r1, =info_str1
	bl  uart_send_string
	ldr r0, =info_str1		//使用printf输出
	bl  printf
	//判断64扇区是否为空
	ldr r0, =addr
	ldr r1, =number
	ldr r1, [r1]
	bl  flash_isempty		//flash_isempty(addr, number)
	cmp r0, #1				//若为空（r0=1）则转跳
	beq flash_empty
	//不为空，读出扇区内容
	//输出不为空提示信息
	mov r0, #UART_User		//向串口发送信息
	ldr r1, =flash_str2
	bl  uart_send_string
	ldr r0, =flash_str2		//使用printf输出
	bl  printf
	//读出扇区内容到flash_ContentDetail
	ldr r0, =flash_ContentDetail
	ldr r1, =addr
	mov r2, #0x20
	bl flash_read_physical	//flash_read_physical(&flash_ContentDetail, addr, 0x20)
	//输出扇区内容
	mov r0, #UART_User		//向串口发送信息
	ldr r1, =flash_ContentDetail
	bl  uart_send_string
	ldr r0, =type_str		//使用printf输出
	ldr r1, =flash_ContentDetail
	bl  printf
	//擦除该扇区的内容，再判空
	//输出擦除再判空的提示信息
	mov r0, #UART_User		//向串口发送信息
	ldr r1, =info_str2
	bl  uart_send_string
	ldr r0, =info_str2		//使用printf输出
	bl  printf
	//擦除该扇区的内容
	mov r0, #64
	bl flash_erase			//flash_erase(64)
	//判空
	ldr r0, =addr
	ldr r1, =number
	ldr r1, [r1]
	bl flash_isempty		//flash_isempty(addr, number)
	cmp r0, #1				//若为空（r0=1）则转跳【成功擦除】
	beq flash_empty
	//仍不为空【擦除失败】，输出提示信息并结束
	mov r0, #UART_User		//向串口发送信息
	ldr r1, =flash_str2
	bl  uart_send_string
	ldr r0, =flash_str2		//使用printf输出
	bl  printf
	bl  main_loop			//结束对Flash的操作
flash_empty:     //为空，写入内容
	//输出扇区为空的提示信息
	mov r0, #UART_User		//向串口发送信息
	ldr r1, =flash_str1
	bl  uart_send_string
	ldr r0, =flash_str1		//使用printf输出
	bl  printf
	//输出扇区为空的提示信息
	mov r0, #UART_User		//向串口发送信息
	ldr r1, =info_str3
	bl  uart_send_string
	ldr r0, =info_str3		//使用printf输出
	bl  printf
	//向64扇区写入内容
//	ldr r0, =addr
//	mov r1, #0x20
//	ldr r2, =flash_Content
//	bl flash_write_physical	//flash_write_physical(addr, 0x20, &flash_Content)
	//flash_write(64, 0, 32, &flash_Content);
	mov r0, #64
	mov r1, #0
	mov r2, #32
	ldr r3, =flash_Content
	bl flash_write
	//读取64扇区内容
	ldr r0, =flash_ContentDetail
	ldr r1, =addr
	mov r2, #0x20
	bl flash_read_physical	//flash_read_physical(&flash_ContentDetail, addr, 0x20)
	//输出扇区内容
	mov r0, #UART_User		//向串口发送信息
	ldr r1, =flash_ContentDetail
	bl  uart_send_string
	ldr r0, =type_str		//使用printf输出
	ldr r1, =flash_ContentDetail
	bl  printf	
//（1）======启动部分（结尾）==========================================

//（2）======主循环部分（开头）========================================
main_loop:                      //主循环标签（开头）
//（2.1）主循环次数变量mMainLoopCount+1
		ldr r2,=mMainLoopCount     //r2←mMainLoopCount的地址
		ldr r1, [r2]
		add r1,#1
		str r1,[r2]	
//（2.2）未达到主循环次数设定值，继续循环
        ldr r2,=MainLoopNUM
		cmp r1,r2
		blO  main_loop     //未达到，继续循环
//（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理
//（2.3.1）清除循环次数变量
		ldr r2,=mMainLoopCount     //r2←mMainLoopCount的地址
		mov r1,#0
		str r1,[r2]	
//（2.3.2）如灯状态标志mFlag为'L'，灯的闪烁次数+1并显示，改变灯状态及标志	
		//判断灯的状态标志
		ldr r2,=mFlag		   
		ldr r6,[r2]
		cmp r6,#'L'			
		bne main_light_off	   //mFlag不等于'L'转
		//mFlag等于'L'情况
		ldr r3,=mLightCount	   //灯的闪烁次数mLightCount+1
		ldr r1,[r3]
		add r1,#1				
		str r1,[r3]

		ldr r2,=mFlag           //灯的状态标志改为'A'
		mov r7,#'A'
		str r7,[r2]             
		ldr r0,=LIGHT_BLUE      //亮灯
		ldr r1,=LIGHT_ON
		bl  gpio_set          

		//mFlag等于'L'情况处理完毕，转
		b main_exit  
//（2.3.3）如灯状态标志mFlag为'A'，改变灯状态及标志
main_light_off:
        ldr r2,=mFlag		   //灯的状态标志改为'L'        
		mov r7,#'L'
		str r7,[r2]   
        ldr r0,=LIGHT_BLUE      //暗灯
		ldr r1,=LIGHT_OFF
		bl  gpio_set  

main_exit:
	b main_loop                 //继续循环
//（2）======主循环部分（结尾）========================================
.end         //整个程序结束标志（结尾）
