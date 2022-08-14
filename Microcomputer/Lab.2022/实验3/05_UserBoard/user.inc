//======================================================================
//文件名称：user.inc
//功能概要：包含工程中用到的头文件
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//版本更新：2019-09-01 V1.0
//======================================================================
.include "gpio.inc"

//指示灯端口及引脚定义
.equ LIGHT_RED,(PTB_NUM|7)    	//红色RUN灯使用的端口/引脚
.equ LIGHT_GREEN,(PTB_NUM|8)  	//绿色RUN灯使用的端口/引脚
.equ LIGHT_BLUE,(PTB_NUM|9)    	//蓝色RUN灯使用的端口/引脚

//灯状态宏定义（灯亮、灯暗对应的物理电平由硬件接法决定）
.equ LIGHT_ON,0     			//灯亮
.equ LIGHT_OFF,1    			//灯暗

//串口宏定义
.equ UARTA, 2                 //TX引脚： GEC_10；RX引脚： GEC_8(板上标识uart0)
.equ UARTB, 1					//未引出（请勿使用）
.equ UARTC, 3                   //TX引脚： GEC_14；RX引脚： GEC_13(板上标识uart2),用于程序更新User中无法使能接收中断

.equ UART_User,   UARTA         //TX引脚：GEC_10；RX引脚：GEC_8
.equ UART_printf, UARTC         //UARTC重定义为UART_printf

//宏定义相关数据
.equ DELAY_NUM,1000000  		//延时数（约1秒），控制小灯闪烁频率
.equ UART_BAUD,115200           //串口波特率

//myprintf重定义
.equ printf, myprintf

