//==========================================================================
//文件名称：systick.inc
//功能概要：systick 构件头文件
//版权所有：苏州大学嵌入式与物联网研究中心(sumcu.suda.edu.cn)
//更新记录：2019-10-23   V1.0
//==========================================================================
//寄存器地址宏定义
.equ SysTick_CTRL,0xE000E010
.equ SysTick_LOAD,0xE000E014
.equ SysTick_VAL,0xE000E018
//操作寄存器所需要的常量
.equ SysTick_CTRL_ENABLE_Msk,1
.equ SysTick_CTRL_TICKINT_Msk,(1<<1)
.equ SysTick_CTRL_CLKSOURCE_Msk,(1<<2)
//其他常量
.equ SysTick_IRQn,(-1)                //systickIRQ中断号
.equ MCU_SYSTEM_CLK_KHZ,48000          //使用到的时钟频率
.equ __NVIC_PRIO_BITS,4               //中断优先级位数
.equ INTERVAL_TIME_MAX,5592           //最大中断时间间隔
