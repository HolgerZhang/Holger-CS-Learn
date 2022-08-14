//======================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn) ���
//���¼�¼��20220622
//======================================================================
.include "include.inc"

//start ������������
.global USART2_IRQHandler
.type  USART2_IRQHandler, function

.section   .text
.syntax unified           	
.thumb                   
.global SysTick_Handler
.type  SysTick_Handler, function
.align 2   


//end  ������������

//========================�жϺ�����������===================================
.section .text
//======================================================================
//�������ƣ�UARTA_Handler��UARTA�����жϴ������
//�����������յ�һ���ֽڴ���
//�����ܣ�����PC���·���ʱ��
//======================================================================
USART2_IRQHandler:
	//��1�������жϣ����ұ����ֳ�
	cpsid  i          //�ؿ������ж�
	push {r0-r7,lr}      //r7,lr��ջ������r7��������ռ��ã�lr��Ϊ�����ж�ǰpc��ֵ��
	//uint_8 flag
	sub sp,#4         //ͨ���ƶ�spָ���ȡ��ַ
	mov r7,sp         //����ȡ���ĵ�ַ����r7
	//��2�������ֽ�
	mov r1,r7         //r1=r7 ��Ϊ����һ���ֽڵĵ�ַ
	mov r0,#UARTA		//r0ָ�����ں�
	bl  uart_re1      //���ý���һ���ֽ��Ӻ���
	ldr r1,=received_data
	str r0,[r1]		//������յ�������
	//��״̬����  
	ldr r3,=recv_state
	ldr r2,[r3]
	cmp r2,#0         //State 0: num->1, other->8
	beq USART2_IRQHandler_state0
	cmp r2,#1         //State 1: num->2, other->8
	beq USART2_IRQHandler_state1
	cmp r2,#2         //State 2: ':'->3, other->8
	beq USART2_IRQHandler_state2
	cmp r2,#3         //State 3: num->4, other->8
	beq USART2_IRQHandler_state3
	cmp r2,#4         //State 4: num->5, other->8
	beq USART2_IRQHandler_state4
	cmp r2,#5         //State 5: ':'->6, other->8
	beq USART2_IRQHandler_state5
	cmp r2,#6         //State 6: num->7, other->8
	beq USART2_IRQHandler_state6
	cmp r2,#7         //State 7: num->10, other->8
	beq USART2_IRQHandler_state7
	cmp r2,#8         //State 8:[Start] $->9, other->8
	beq USART2_IRQHandler_state8
	cmp r2,#9         //State 9: $->0, other->8
	beq USART2_IRQHandler_state9
	cmp r2,#10         //State 10: #->11, other->8
	beq USART2_IRQHandler_state10
	cmp r2,#11         //State 11: #->set_new_time->8, other->8
	beq USART2_IRQHandler_state11
	bl  USART2_IRQHandler_exit
//Hour
USART2_IRQHandler_state0:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state0_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state0_other
	//�յ��ַ�0-9
	sub r0,r0,#'0'		//תΪ����0-9
	ldr r1,=new_hour	//����new_hour
	str r0,[r1]
	mov r0,#1			//ת1
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state0_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state1:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state1_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state1_other
	//�յ��ַ�0-9
	sub r0,r0,#'0'		//תΪ����0-9
	ldr r3,=new_hour	//new_hour=new_hour*10+r0
	ldr r1,[r3]
	mov r2,#10
	mul r1,r2,r1
	add r0,r0,r1
	str r0,[r3]
	mov r0,#2			//ת2
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state1_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state2:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#':'
	bne USART2_IRQHandler_state2_other
	//�յ�ð��
	mov r0,#3			//ת3
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state2_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
//Minute
USART2_IRQHandler_state3:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state3_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state3_other
	//�յ��ַ�0-9
	sub r0,r0,#'0'		//תΪ����0-9
	ldr r1,=new_minute	//����new_minute
	str r0,[r1]
	mov r0,#4			//ת4
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state3_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state4:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state4_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state4_other
	//�յ��ַ�0-9
	sub r0,r0,#'0'		//תΪ����0-9
	ldr r3,=new_minute	//new_minute=new_minute*10+r0
	ldr r1,[r3]
	mov r2,#10
	mul r1,r2,r1
	add r0,r0,r1
	str r0,[r3]
	mov r0,#5			//ת5
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state4_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state5:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#':'
	bne USART2_IRQHandler_state5_other
	//�յ�ð��
	mov r0,#6			//ת6
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state5_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
//Second
USART2_IRQHandler_state6:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state6_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state6_other
	//�յ��ַ�0-9
	sub r0,r0,#'0'		//תΪ����0-9
	ldr r1,=new_second	//new_second
	str r0,[r1]
	mov r0,#7			//ת7
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state6_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state7:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'0'
	blo USART2_IRQHandler_state7_other
	cmp r0,#'9'
	bhi USART2_IRQHandler_state7_other
	//�յ��ַ�0-9
	sub r0,r0,#'0'		//תΪ����0-9
	ldr r3,=new_second	//new_second=new_second*10+r0
	ldr r1,[r3]
	mov r2,#10
	mul r1,r2,r1
	add r0,r0,r1
	str r0,[r3]
	mov r0,#10			//ת10
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state7_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state8:
	//���ý��յ���ʱ��
	mov r0,#0
	ldr r1,=new_hour
	str r0,[r1]
	ldr r1,=new_minute
	str r0,[r1]
	ldr r1,=new_second
	str r0,[r1]
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	cmp r0,#'$'
	bne USART2_IRQHandler_state8_other
	//�յ�$
	mov r0,#9			//ת9
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state8_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state9:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	//�յ�$
	cmp r0,#'$'
	bne USART2_IRQHandler_state9_other
	mov r0,#0			//ת0
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state9_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state10:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	//�յ�#
	cmp r0,#'#'
	bne USART2_IRQHandler_state10_other
	mov r0,#11			//ת11
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state10_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	bl  USART2_IRQHandler_exit
USART2_IRQHandler_state11:
	//�����յ����ֽ�
	ldr r0,=received_data
	ldr r0,[r0]
	//�յ�#
	cmp r0,#'#'
	bne USART2_IRQHandler_state11_other
	//set_time:
	ldr r0,=new_hour
	ldr r0,[r0]
	cmp r0,#23		//��Сʱ>23
	bhi USART2_IRQHandler_state11_other
	ldr r1,=new_minute
	ldr r1,[r1]
	cmp r1,#59		//�·���>59
	bhi USART2_IRQHandler_state11_other
	ldr r2,=new_second
	ldr r2,[r2]
	cmp r2,#59		//������>59
	bhi USART2_IRQHandler_state11_other
	//ֻ����ȷʱ���ʽ�Ŵ���
	ldr r3,=hour
	str r0,[r3]
	ldr r3,=minute
	str r1,[r3]
	ldr r3,=second
	str r2,[r3]
	mov r0,#60
	ldr r1,=last_second
	str r0,[r1]
	ldr r1,=gcount
	mov r0,#0
	str r0,[r1]
USART2_IRQHandler_state11_other:
	mov r0,#8			//ת8
	ldr r1,=recv_state
	str r0,[r1]
	//��4��������Σ����һָ��ֳ�
USART2_IRQHandler_exit:
	cpsie   i         //��������ж�
	add r7,#4         //��ԭr7
	mov sp,r7         //��ԭsp
	pop {r0-r7,pc}       //r7,pc��ջ����ԭr7��ֵ��pc��lr,�������ж�ǰ�������ִ��



//===================================================================
//�������ƣ�SysTick_Handler
//����˵������
//�������أ���
//���ܸ�Ҫ��SysTick��ʱ���жϷ�������
//===================================================================
SysTick_Handler:
	push {r0,r1,r2,lr}
	ldr r0,=gcount
	ldr r1,[r0]
	cmp r1,#50
	bcs SysTick_Handler_1s
	add r1,#1
	str r1,[r0]
	b   SysTick_Handler_Exit
SysTick_Handler_1s:
    mov r1,#0
    str r1,[r0]
    b   add_sec
SysTick_Handler_Exit:
    pop {r0,r1,r2,pc} 
     
    
add_sec:
    ldr r0,=second
    ldr r1,[r0]
    cmp r1,#59
    bcs sec60  //��>=59
    add r1,#1
    str r1,[r0]//��<59
    b   add_sec_exit
sec60:         //��>=59
    mov r1,#0
    str r1,[r0]
    ldr r0,=minute
    ldr r1,[r0]
    cmp r1,#59
    bcs min60  //��>=59
    add r1,#1
    str r1,[r0]//��<59
    b   add_sec_exit
min60:         //��>=59
    mov r1,#0
    str r1,[r0]
    ldr r0,=hour
    ldr r1,[r0]
    cmp r1,#23
    bcs hour23  //ʱ>=23
    add r1,#1
    str r1,[r0]//ʱ<23
    b   add_sec_exit
hour23:
    mov r1,#0
    str r1,[r0]
add_sec_exit: 
    b   SysTick_Handler_Exit
    
    