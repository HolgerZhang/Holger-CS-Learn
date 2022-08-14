//=======================================================================================
//文件名称：selectionSort.s
//功能概要：STM32L432RC 选择排序（汇编）程序文件
//版权所有：张昊
//版本更新：2022-05-01 V1.0
//=======================================================================================

//start 函数定义区域
.type selectionSort_down function               //声明为函数类型
.global selectionSort_down              	      //定义成全局函数，便于芯片初始化之后调用
.type selectionSort_up function               //声明为函数类型
.global selectionSort_up              	      //定义成全局函数，便于芯片初始化之后调用
//end  函数定义区域

//-----------------------以下为内部函数存放处---------------------------------
.section .text
//======================================================================
//函数名称：swap
//函数返回：无
//参数说明：r0，r1:要交换的两个数据的地址
//功能概要：将两个地址的数据交换
//======================================================================
swap:
//（1）保存现场
      push {r0-r7,lr}               //保存现场，pc(lr)入栈
//（2）交换
      ldrb r2,[r0]				  //r2=*r0
      ldrb r3,[r1]				  //r3=*r1
      strb r2,[r1]				  //*r1=r2
      strb r3,[r0]			      //*r0=r3
//（3）恢复现场
      pop {r0-r7,pc}             //恢复现场，lr出栈到pc


//======================================================================
//函数名称：selectionSort_up
//函数返回：无
//参数说明：r0:用于存储数据的首地址，r1:数组的长度
//功能概要：将一数组采用选择排序的方式进行升序排列，且为原地排序
//======================================================================
selectionSort_up:
    push {r0-r7,lr}               //保存现场，pc(lr)入栈
    //外层循环开始：每轮循环把待排序区的最小元素与待排序区的首元素交换
    mov r2, #0			//r2=0 外层循环变量
    sub r7, r1, #1		//循环终止于r7=r1-1
up_loop_outer:
    cmp r2, r7			//若r2>=r7，结束循环
    bge up_loop_outer_after
    //否则继续循环
    mov r4, r2			//最小元素的下标r4=r2
    //内层循环开始：找到最小的元素，下标存到r4
    add r3, r2, #1		//r3=r2+1 内层循环变量
up_loop_inner:
    cmp r3, r1			//若r3>=r6，结束循环
    bge up_loop_inner_after
    //否则继续循环
    ldrb r5, [r0, r3]	//r5=r0[r3]
    ldrb r6, [r0, r4]	//r6=r0[r4]  (最小元素)
    cmp r5, r6
    //若r5>=r6，即r6=r0[r4]仍然是更小的元素，不修改
    bge up_not_change
    //若r5<r6，即r5=r0[r3]是更小的元素，修改最小元素的下标r4=r3
    mov r4, r3
up_not_change:
    add r3, r3, #1		//r3++
    b up_loop_inner		//继续循环
up_loop_inner_after:
    //内层循环结束
    //交换最小元素r0[r4]和待排序区首元素r0[r2]
    add r5, r0, r4		//r5=&r0[r4]
    add r6, r0, r2		//r6=&r0[r2]
    push {r0,r1}		//保护r0和r1
    mov r0, r5			//传递参数
    mov r1, r6
    bl swap				//调用交换函数
    pop {r0,r1}			//恢复r0和r1
    add r2, r2, #1		//r2++
    b up_loop_outer		//继续循环
up_loop_outer_after:
    //外层循环结束
    pop {r0-r7,pc}             //恢复现场，lr出栈到pc



//======================================================================
//函数名称：selectionSort_down
//函数返回：无
//参数说明：r0:用于存储数据的首地址，r1:数组的长度
//功能概要：将一数组采用选择排序的方式进行降序排列，且为原地排序
//======================================================================
selectionSort_down:
    push {r0-r7,lr}               //保存现场，pc(lr)入栈
    //外层循环开始：每轮循环把待排序区的最大元素与待排序区的首元素交换
    mov r2, #0			//r2=0 外层循环变量
    sub r7, r1, #1		//循环终止于r7=r1-1
down_loop_outer:
    cmp r2, r7			//若r2>=r7，结束循环
    bge down_loop_outer_after
    //否则继续循环
    mov r4, r2			//最大元素的下标r4=r2
    //内层循环开始：找到最大的元素，下标存到r4
    add r3, r2, #1		//r3=r2+1 内层循环变量
down_loop_inner:
    cmp r3, r1			//若r3>=r6，结束循环
    bge down_loop_inner_after
    //否则继续循环
    ldrb r5, [r0, r3]	//r5=r0[r3]
    ldrb r6, [r0, r4]	//r6=r0[r4]  (最大元素)
    cmp r5, r6
    //若r5<=r6，即r6=r0[r4]仍然是更大的元素，不修改
    bls down_not_change	//修改这里！
    //若r5>r6，即r5=r0[r3]是更大的元素，修改最大元素的下标r4=r3
    mov r4, r3
down_not_change:
    add r3, r3, #1		//r3++
    b down_loop_inner		//继续循环
down_loop_inner_after:
    //内层循环结束
    //交换最大元素r0[r4]和待排序区首元素r0[r2]
    add r5, r0, r4		//r5=&r0[r4]
    add r6, r0, r2		//r6=&r0[r2]
    push {r0,r1}		//保护r0和r1
    mov r0, r5			//传递参数
    mov r1, r6
    bl swap				//调用交换函数
    pop {r0,r1}			//恢复r0和r1
    add r2, r2, #1		//r2++
    b down_loop_outer		//继续循环
down_loop_outer_after:
    //外层循环结束
    pop {r0-r7,pc}             //恢复现场，lr出栈到pc

