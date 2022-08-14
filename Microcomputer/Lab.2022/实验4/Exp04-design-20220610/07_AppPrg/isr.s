//======================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn)
//���¼�¼��20220610
//======================================================================
.include "include.inc"
.align 2
//start ������������
.type  USART2_IRQHandler, function
.global USART2_IRQHandler
//end  ������������

/*
�Զ�����
   1 -p- 2 -e- 3 -n- 0(openLED)
  /o
0
 c\ 
   5 -l- 6 -o- 7 -s- 8 -e- 0(closeLED)
*/

//========================�жϺ�����������===================================
.section .text
//======================================================================
//�������ƣ�UARTA_Handler��UARTA�����жϴ������
//�����������յ�һ���ֽڴ���
//�����ܣ��ط����յ����ֽ�
//======================================================================
USART2_IRQHandler:
//��1�������жϣ����ұ����ֳ�
	cpsid  i          //�ؿ������ж�
	push {r7,lr}      //r7,lr��ջ������r7��������ռ��ã�lr��Ϊ�����ж�ǰpc��ֵ��
	//uint_8 flag
	sub sp,#4         //ͨ���ƶ�spָ���ȡ��ַ
	mov r7,sp         //����ȡ���ĵ�ַ����r7
//��2�������ֽ�
	mov r1,r7         //r1=r7 ��Ϊ����һ���ֽڵĵ�ַ
	mov r0,#UARTA		//r0ָ�����ں�
	bl  uart_re1      //���ý���һ���ֽ��Ӻ���
	//������ܵ�����Ϣ  
	ldr r3,=recv_state
	ldr r2,[r3]
	cmp r2,#0         //State 0: o->1, c->5, other->0
	beq state0
	cmp r2,#1         //State 1: open, p->2, other->0
	beq state1
	cmp r2,#2         //State 2: open, e->3, other->0
	beq state2
	cmp r2,#3         //State 3: open, n->openLED->0
	beq state3
	cmp r2,#5         //State 5: close, l->6, other->0
	beq state5
	cmp r2,#6         //State 5: close, o->7, other->0
	beq state6
	cmp r2,#7         //State 6: close, s->8, other->0
	beq state7
	cmp r2,#8         //State 7: close, e->closeLED->0
	beq state8
state0:
	cmp r0,#'o'		//o->1
	bne state0_c
	mov r2,#1
	str r2,[r3]
	bl USART2_IRQHandler_exit
state0_c:
	cmp r0,#'c'		//c->5
	bne state0_other
	mov r2,#5
	str r2,[r3]
	bl USART2_IRQHandler_exit
state0_other:
	mov r2,#0		//other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state1:
	cmp r0,#'p'       //p->2
	bne state1_other
	mov r2,#2
	str r2,[r3]
	bl USART2_IRQHandler_exit
state1_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state2:
	cmp r0,#'e'       //e->3
	bne state2_other
	mov r2,#3
	str r2,[r3]
	bl USART2_IRQHandler_exit
state2_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state3:
	cmp r0,#'n'       //n->openLED
	bne state3_other
	//LED ON
	bl led_on_caller
state3_other:
	mov r2,#0         //all->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state5:
	cmp r0,#'l'       //l->6
	bne state5_other
	mov r2,#6
	str r2,[r3]
	bl USART2_IRQHandler_exit
state5_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state6:
	cmp r0,#'o'       //o->7
	bne state6_other
	mov r2,#7
	str r2,[r3]
	bl USART2_IRQHandler_exit
state6_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state7:
	cmp r0,#'s'       //s->8
	bne state7_other
	mov r2,#8
	str r2,[r3]
	bl USART2_IRQHandler_exit
state7_other:
	mov r2,#0         //other->0
	str r2,[r3]
	bl USART2_IRQHandler_exit
state8:
	cmp r0,#'e'       //e->closeLED
	bne state8_other
	//LED OFF
	bl led_off_caller
state8_other:
	mov r2,#0         //all->0
	str r2,[r3] 
USART2_IRQHandler_exit:
//��3�������ֽ�
//	mov r1,r0			//r1��Ŵ��ڽ��յ������ݣ���Ϊuart_send1����ڲ���
//	mov r0,#UARTA		//r0ָ�����ں�
//	bl  uart_send1    //��ԭ���ڻط�
//��4��������Σ����һָ��ֳ�
	cpsie   i         //��������ж�
	add r7,#4         //��ԭr7
	mov sp,r7         //��ԭsp
	pop {r7,pc}       //r7,pc��ջ����ԭr7��ֵ��pc��lr,�������ж�ǰ�������ִ��

led_on_caller:
	push {r0-r7,lr}
	ldr r0,=LIGHT_BLUE	//����
	ldr r1,=LIGHT_ON
	bl  gpio_set
	mov r0,#UARTA		//Light on
	ldr r1,=light_on_string
	bl uart_send_string
	pop {r0-r7,pc}

led_off_caller:
	push {r0-r7,lr}
	ldr r0,=LIGHT_BLUE	//����
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	mov r0,#UARTA		//Light off
	ldr r1,=light_off_string
	bl uart_send_string
	pop {r0-r7,pc}