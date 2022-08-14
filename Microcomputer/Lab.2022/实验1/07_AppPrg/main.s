//=====================================================================
//文件名称：main.s
//功能概要：汇编编程调用GPIO构件控制小灯闪烁（利用printf输出提示信息）
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//版本更新：20180810-20201128
//=====================================================================
.include "include.inc"    //头文件中主要定义了程序中需要使用到的一些常量
//（0）数据段与代码段的定义
//（0.1）定义数据存储data段开始，实际数据存储在RAM中
.section .data
//（0.1.1）定义需要输出的字符串，标号即为字符串首地址,\0为字符串结束标志
hello_information:           //字符串标号
    .ascii "-------------------------------------------------------\n"
    .ascii " 用汇编点亮的三色发光二极管。\n"
    .ascii "------------------------------------------------------\n\0"
light_show_red_on:
	.asciz "LIGHT_RED:ON--\n"    //红灯亮状态提示
light_show_green_on:
	.asciz "LIGHT_GREEN:ON--\n"    //绿灯亮状态提示
light_show_blue_on:
	.asciz "LIGHT_BLUE:ON--\n"    //蓝灯亮状态提示
light_show_off:
	.asciz "LIGHT:OFF--\n"  	 //灯暗状态提示
light_show_count:
	.asciz "闪烁次数mLightCount=%d\n"  //闪烁次数提示
light_show_type:
	.asciz "闪烁类型mLightType=%d\n"  //闪烁次数提示
//（0.1.2）定义变量
.align 4               //.word格式四字节对齐
mMainLoopCount:		   //定义主循环次数变量，数据格式为字，初始值为0
	.word 0
mFlag:				   //定义灯的状态标志，'L'为亮，'A'为暗初始值为亮
	.byte 'L'
.align 4
mLightCount:		//定义灯的闪烁次数，数据格式为字，初始值为0
    .word 0
.align 4
mLightType:			//定义灯的类型，数据格式为字，初始值为0，大于7时重置为0
    .word 0
    
.equ MainLoopNUM,6122338  //主循环次数设定值（常量）

//（0.2）定义代码存储text段开始，实际代码存储在Flash中
.section   .text
.syntax unified        //指示下方指令为ARM和thumb通用格式
.thumb                 //Thumb指令集
.type main function    //声明main为函数类型
.global main           //将main定义成全局函数，便于芯片初始化之后调用
.align 2               //指令和数据采用2字节对齐，兼容Thumb指令集

//--------------------------------------------------------------------                        
//main.c使用的内部函数声明处

//--------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程，参见书稿）
main:
//（1）======启动部分（开头）主循环前的初始化工作======================
//（1.1）声明main函数使用的局部变量

//（1.2）【不变】关总中断
	//在主循环前的初始化需要先关中断的原因：
	//若设备的初始化过程中出现了中断事件，则初始化工作会被打断，
	//然而中断处理需要使用到这些设备，从而会导致一些列的问题。
	cpsid i   
//（1.3）给主函数使用的局部变量赋初值
	
//（1.4）给全局变量赋初值
	
//（1.5）用户外设模块初始化
	//初始化红灯, r0、r1、r2是gpio_init的入口参数（使用寄存器传递）
	ldr r0,=LIGHT_RED     //r0指明端口和引脚(端口号|(引脚号))（用=,因常量>=256,需用ldr）【立即数寻址】
	mov r1,#GPIO_OUTPUT    //r1指明引脚方向为输出
	mov r2,#LIGHT_OFF      //r2指明引脚的初始状态为暗
	bl  gpio_init          //调用gpio初始化函数（gpio.s）
	//汇编语言中函数调用的参数传递是通过通用寄存器（R0-R12，常用低位寄存器R0-R7）完成的
	//初始化绿灯, r0、r1、r2是gpio_init的入口参数（使用寄存器传递）
	ldr r0,=LIGHT_GREEN     //r0指明端口和引脚(端口号|(引脚号))（用=,因常量>=256,需用ldr）【立即数寻址】
	mov r1,#GPIO_OUTPUT    //r1指明引脚方向为输出
	mov r2,#LIGHT_OFF      //r2指明引脚的初始状态为暗
	bl  gpio_init          //调用gpio初始化函数（gpio.s）
	//初始化蓝灯, r0、r1、r2是gpio_init的入口参数（使用寄存器传递）
	ldr r0,=LIGHT_BLUE     //r0指明端口和引脚(端口号|(引脚号))（用=,因常量>=256,需用ldr）【立即数寻址】
	mov r1,#GPIO_OUTPUT    //r1指明引脚方向为输出
	mov r2,#LIGHT_OFF      //r2指明引脚的初始状态为暗
	bl  gpio_init          //调用gpio初始化函数（gpio.s）

//（1.6）使能模块中断
    
//（1.7）【不变】开总中断（初始化结束）
	cpsie  i  
	//显示hello_information定义的字符串
	ldr r0,=hello_information   //待显示字符串首地址
	bl  printf		            //调用printf显示字符串
	
	//bl .   //在此打桩(.表示当前地址)，理解发光二极管为何亮起来了？
	//嵌入式系统的两种调试方式：
	//1、使用仿真器调试，需要特定的编程软件以及仿真器（设备），实验板引出相关引脚/SWD
	//2、使用串口获取下位机的程序运行状态，设置断点（死循环），使程序停在某一位置，观察输出是否正确
	//   注意调试完毕要删除打桩的位置
	
//（1）======启动部分（结尾）=======================================

//（2）======主循环部分（开头）=====================================
	main_loop:                      //主循环标签（开头）
//（2.1）主循环次数变量mMainLoopCount+1
		ldr r2,=mMainLoopCount   //r2←mMainLoopCount的地址（mMainLoopCount是地址）
		ldr r1, [r2]             //将r2保存的地址中存储的值存到r1中
		add r1,#1                //r1=r1+1
		str r1,[r2]	            //将r1中的值存到r2保存的地址中去
//（2.2）未达到主循环次数设定值，继续循环
        ldr r2,=MainLoopNUM   //从MainLoopNUM所在的地址中取数据至r2（MainLoopNUM是常量）
		cmp r1,r2             //比较r1和r2
		blO  main_loop       //未达到，继续循环（lo：无符号数小于）
		//bne  main_loop     //未达到，继续循环（ne：不等于）
// 2.1和2.2实现的功能是：反复空循环执行MainLoopNUM次才继续执行，起延时作用，从而达到灯亮灭交替的效果
// 等价于高级语言中的： for (mMainLoopCount=0; mMainLoopCount<MainLoopNUM; mMainLoopCount++);
//（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理
//（2.3.1）清除循环次数变量 mMainLoopCount=0
		ldr r2,=mMainLoopCount     //r2←mMainLoopCount的地址
		mov r1,#0                  //若达到循环次数，将循环变量的值清零
		str r1,[r2]	               //将r1中的值存到r2所在的内存地址中
//（2.3.2）如灯状态标志mFlag为'L'，灯的闪烁次数+1并显示，改变灯状态及标志，根据灯的类型亮相应的灯，修改灯的类型
		//判断灯的状态标志
		ldr r2,=mFlag		   
		ldr r6,[r2]
		cmp r6,#'L'			
		bne main_light_off	   //mFlag不等于'L'转关灯
		//mFlag等于'L'情况：开灯
		ldr r3,=mLightCount	   //灯的闪烁次数mLightCount+1
		ldr r1,[r3]
		add r1,#1				
		str r1,[r3]
		ldr r0,=light_show_count  //显示灯的闪烁次数值
		ldr r2,=mLightCount
		ldr r1,[r2]
		bl  printf	
		ldr r2,=mFlag           //灯的状态标志改为'A'（下一步是灭灯）
		mov r7,#'A'
		str r7,[r2]             
		//根据mLightType亮不同颜色的灯
		ldr r0,=light_show_type  //显示灯的类型mLightType
		ldr r2,=mLightType
		ldr r1,[r2]
		bl  printf
		ldr r2,=mLightType		//读取灯的类型mLightType
		ldr r1,[r2]
		cmp r1,#0
		bne case_type_1			//不等于0转判断1
		//等于0的情况:红灯
		ldr r0,=LIGHT_RED      //亮红灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_red_on    //显示红灯亮提示
		bl  printf
		b end_case_type			//break
	case_type_1:
		ldr r2,=mLightType		//读取灯的类型mLightType
		ldr r1,[r2]
		cmp r1,#1
		bne case_type_2			//不等于1转判断2
		//等于1的情况:绿灯
		ldr r0,=LIGHT_GREEN      //亮绿灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_green_on    //显示绿灯亮提示
		bl  printf
		b end_case_type			//break
	case_type_2:
		ldr r2,=mLightType		//读取灯的类型mLightType
		ldr r1,[r2]
		cmp r1,#2
		bne case_type_3			//不等于2转判断3
		//等于2的情况:蓝灯
		ldr r0,=LIGHT_BLUE      //亮蓝灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_blue_on    //显示蓝灯亮提示
		bl  printf
		b end_case_type			//break
	case_type_3:
		ldr r2,=mLightType		//读取灯的类型mLightType
		ldr r1,[r2]
		cmp r1,#3
		bne case_type_4			//不等于3转判断4
		//等于3的情况:红灯+绿灯=黄
		ldr r0,=LIGHT_RED      //亮红灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_red_on    //显示红灯亮提示
		bl  printf
		ldr r0,=LIGHT_GREEN      //亮绿灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_green_on    //显示绿灯亮提示
		bl  printf
		b end_case_type			//break
	case_type_4:
		ldr r2,=mLightType		//读取灯的类型mLightType
		ldr r1,[r2]
		cmp r1,#4
		bne case_type_5			//不等于4转判断5
		//等于4的情况:红灯+蓝灯=紫
		ldr r0,=LIGHT_RED      //亮红灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_red_on    //显示红灯亮提示
		bl  printf
		ldr r0,=LIGHT_BLUE      //亮蓝灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_blue_on    //显示蓝灯亮提示
		bl  printf
		b end_case_type			//break
	case_type_5:
		ldr r2,=mLightType		//读取灯的类型mLightType
		ldr r1,[r2]
		cmp r1,#5
		bne case_type_6			//不等于5转6
		//等于5的情况:绿灯+蓝灯=青
		ldr r0,=LIGHT_GREEN      //亮绿灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_green_on    //显示绿灯亮提示
		bl  printf
		ldr r0,=LIGHT_BLUE      //亮蓝灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_blue_on    //显示蓝灯亮提示
		bl  printf
		b end_case_type			//break
	case_type_6:
		//等于6的情况:红灯+绿灯+蓝灯=白
		ldr r0,=LIGHT_RED      //亮红灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_red_on    //显示红灯亮提示
		bl  printf
		ldr r0,=LIGHT_GREEN      //亮绿灯
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_green_on    //显示绿灯亮提示
		bl  printf
		ldr r0,=LIGHT_BLUE      //亮蓝灯
		ldr r1,=LIGHT_ON
		bl  gpio_set          
		ldr r0, =light_show_blue_on    //显示蓝灯亮提示
		bl  printf	
	end_case_type:
		//修改灯的类型mLightType+1，若mLightType>=7，mLightType=0
		ldr r3,=mLightType		//灯的类型mLightType
		ldr r1,[r3]
		add r1,#1				//mLightType++
		cmp r1,#7
		blo type_not_to_zero    //若mLightType>=7，mLightType=0
		mov r1,#0
	type_not_to_zero:  				//若mLightType<7，mLightType++后不改变
		str r1,[r3]
		//mFlag等于'L'情况处理完毕，转
		b main_exit  
//（2.3.3）如灯状态标志mFlag为'A'，改变灯状态及标志，灭所有的灯
	main_light_off:
        ldr r2,=mFlag		   //灯的状态标志改为'L'（下一步是亮灯）
		mov r7,#'L'
		str r7,[r2]   
		ldr r0,=LIGHT_RED      //灭红灯
		ldr r1,=LIGHT_OFF
		bl  gpio_set
		ldr r0,=LIGHT_GREEN      //灭绿灯
		ldr r1,=LIGHT_OFF
		bl  gpio_set
		ldr r0,=LIGHT_BLUE      //灭蓝灯
		ldr r1,=LIGHT_OFF
		bl  gpio_set
		ldr r0, =light_show_off    //显示灯灭提示
		bl  printf	
	main_exit:
		b main_loop                 //继续循环
//（2）======主循环部分（结尾）=====================================
.end     //整个程序结束标志（结尾）
