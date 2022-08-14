//=====================================================================
//文件名称：main.s
//功能概要：汇编编程调用SysTick控制小灯闪烁（利用printf输出提示信息）
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//版本更新：20180810-20201130
//=====================================================================
.include "include.inc"    //头文件中主要定义了程序中需要使用到的一些常量
.include "systick.inc"
//（0）数据段与代码段的定义
//（0.1）全局变量声明
.global gcount  //50次计数单元
.global hour    //时
.global minute  //分
.global second  //秒
.global data_format
.global new_hour    //新时
.global new_minute  //新分
.global new_second  //新秒
.global received_data
.global recv_state
.global last_second
//（0.2）定义数据存储data段开始，实际数据存储在RAM中
.section .data
//（0.2.1）定义需要输出的字符串，标号即为字符串首地址,\0为字符串结束标志
time_data_format:
    .ascii "%d\0"                   //输时分秒使用的数据格式控制符
time_show0:
    .ascii "0\0"	                //字符零，用于将时分秒补足两位
time_show1:
    .ascii ":\0"                    //用于时分秒的分隔
time_show2:
    .ascii "\n\0"                   //用于换行
data_format:
    .ascii "%d\n\0"                 //printf使用的数据格式控制符
light_show1:
	.ascii "LIGHT_BLUE:ON--\n\0"    //灯亮状态提示   
light_show2:
	.ascii "LIGHT_BLUE:OFF--\n\0"   //灯暗状态提示
light_show3:
	.ascii "灯的闪烁次数mLightCount=\0"    //灯亮状态提示  
debug_recv_state_received_data_show:
	.string "recv_state: %d, received_data: %d\n"

//（0.2.2）定义变量
.align 4               //.word格式四字节对齐
mMainLoopCount:		   //定义主循环次数变量
	.word 0
mFlag:				   //定义灯的状态标志,1为亮，0为暗
	.byte 'A'	
.align 4
mLightCount:
    .word 0
gcount:      //50次计数单元
    .word 0
hour:        //时
    .word 12
minute:      //分
    .word 0
second:      //秒
    .word 0
last_second:  //上一次记录的秒
    .word 0
received_data:  //串口接受到的数据
	.word 0
recv_state:		//接收状态
	.word 8
new_hour:        //新的时
    .word 12
new_minute:      //新的分
    .word 0
new_second:      //新的秒
    .word 0

//（0.3）定义代码存储text段开始，实际代码存储在Flash中
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
//  systick定时器初始化
	mov r0,#20
	bl systick_init//每20毫秒中断一次
//  初始化串口UARTA
	mov r0,#UARTA               //r0=更新串口
	ldr r1,=UART_BAUD
	bl  uart_init
//（1.6）使能模块中断
	mov r0,#UARTA               //r0指明串口号
	bl  uart_enable_re_int     //调用串口中断使能函数

//（1.7）【不变】开总中断
	cpsie  i  
	
	//bl .   //在此打桩(.表示当前地址)，理解发光二极管为何亮起来了？
	
//（1）======启动部分（结尾）==========================================

//（2）======主循环部分（开头）========================================
main_loop:                      //主循环标签（开头）
        ldr r0,=second
        ldr r0,[r0]               //读取秒数
        ldr r1,=last_second        
        ldr r1,[r1]               //读取上一次记录的秒
        cmp r0,r1               //判断是否是新的一秒
        beq main_loop           //若未到新的一秒，继续循环
        ldr r1,=last_second        
        str r0,[r1]               //否则，更新记录的秒        
        
		//当秒数更新时，向串口发送最新时间
		ldr r2,=hour
		ldr r1,[r2]
		mov r0,#UARTA
		bl  uart_send1
		ldr r2,=minute
		ldr r1,[r2]
		mov r0,#UARTA
		bl  uart_send1
		ldr r2,=second
		ldr r1,[r2]
		mov r0,#UARTA
		bl  uart_send1
        
        //输出时间
        ldr r2,[r2]
        ldr r1,=hour
        ldr r1,[r1]
        cmp r1,#10             //读取小时数，判断位数
        bcs hour_two_bits
        ldr r0,=time_show0      //若为一位，补足一个0
        bl  printf
        
hour_two_bits:
        ldr r0,=time_data_format
        ldr r1,=hour
        ldr r1,[r1]
        bl  printf              //输出小时数
        
        ldr r0,=time_show1
        bl  printf              //输出：
        
        ldr r1,=minute
        ldr r1,[r1]
        cmp r1,#10
        bcs minute_two_bits     //读取分钟数判断位数
        ldr r0,=time_show0      //若为一位，补足一个0
        bl  printf
        
minute_two_bits:    
        ldr r0,=time_data_format
        ldr r1,=minute
        ldr r1,[r1]
        bl  printf	           //输出分钟数
        
        ldr r0,=time_show1
        bl  printf              //输出：
        
        ldr r1,=second
        ldr r1,[r1]
        cmp r1,#10
        bcs second_two_bits     //读取秒数判断位数
        ldr r0,=time_show0
        bl  printf             //若为一位，补足一个0
        
second_two_bits: 
        ldr r0,=time_data_format
        ldr r1,=second
        ldr r1,[r1]
        bl  printf	          //输出分钟数
        
        ldr r0,=time_show2
        bl  printf            //输出换行符
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
		ldr r0,=light_show3   //显示“灯的闪烁次数mLightCount=”
		bl  printf				
		ldr r0,=data_format    //显示灯的闪烁次数值
		ldr r2,=mLightCount
		ldr r1,[r2]
		bl  printf	
		ldr r2,=mFlag           //灯的状态标志改为'A'
		mov r7,#'A'
		str r7,[r2]             
		ldr r0,=LIGHT_BLUE      //亮灯
		ldr r1,=LIGHT_ON
		bl  gpio_set          
		ldr r0, =light_show1    //显示灯亮提示
		bl  printf	
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
        ldr r0, =light_show2    //显示灯暗提示
		bl  printf	
main_exit:
	b main_loop                 //继续循环
//（2）======主循环部分（结尾）========================================
.end         //整个程序结束标志（结尾）