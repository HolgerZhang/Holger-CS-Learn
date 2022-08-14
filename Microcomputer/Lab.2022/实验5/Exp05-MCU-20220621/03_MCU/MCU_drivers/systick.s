//==========================================================================
//文件名称：systick.s
//功能概要：systick 构件源文件
//版权所有：苏州大学嵌入式与物联网研究中心(sumcu.suda.edu.cn)
//更新记录：2019-10-23   V1.0
//==========================================================================
.include "systick.inc"
//===========================================================================
//函数名称：systick_init
//函数返回：无
//参数说明：int_ms:中断的时间间隔。单位ms 推荐选用5,10,......
//功能概要：初始化SysTick模块，设置中断的时间间隔
//说    明：内核时钟频率MCU_SYSTEM_CLK_KHZ宏定义在mcu.h中
//systick以ms为单位，349（2^24/48000，向下取整），合理范围1~349。
//===========================================================================
.type systick_init function          //声明systick_init为函数类型                     
.global systick_init                 //将systick_init定义成全局函数，便于芯片初始化之后调用
systick_init:
    push {r0,r1,r2,lr}
    ldr r2,=SysTick_CTRL     //设置前先关闭systick。CTRL控制及状态寄存器
    mov r1,#0
    str r1,[r2]
    ldr r2,=SysTick_VAL      //清除计数器。VAL 计数器
    str r1,[r2]
//对传参做防错处理
    cmp r0,#1                
    bcs systick_init_label1  
    mov r0,#10              //传参小于1，赋值为10
systick_init_label1:
	ldr r1,=INTERVAL_TIME_MAX
    cmp r1,r0
    bcs systick_init_label2
	mov r0,#10              //传参大于最大值，赋值为10
systick_init_label2:
    ldr r1,=MCU_SYSTEM_CLK_KHZ
    mul r1,r1,r0
    ldr r2,=SysTick_LOAD
    str r1,[r2]            //重载寄存器赋值
    ldr r1,=SysTick_CTRL
    ldr r2,[r1]
    ldr r0,=SysTick_CTRL_CLKSOURCE_Msk
    orr r2,r2,r0
    str r2,[r1]            //控制及状态寄存器赋值
//设定 SysTick优先级为3(SHPR3寄存器的最高字节=0xC0)
    ldr r0,=SysTick_IRQn 
    mov r1,#1
    ldr r2,=__NVIC_PRIO_BITS
    lsl r1,r2              //左移操作
    sub r1,#1
//    ldr r2,=set_irq_priority//调用设置优先级函数
//   blx r2
//允许中断,使能该模块,开始计数
    ldr r0,=SysTick_CTRL_ENABLE_Msk
    ldr r1,=SysTick_CTRL_TICKINT_Msk
    orr r0,r0,r1           //或操作
    ldr r1,=SysTick_CTRL
    ldr r2,[r1]
    orr r0,r0,r2
    str r0,[r1]            //控制及状态寄存器赋值
    pop {r0,r1,r2,pc}
