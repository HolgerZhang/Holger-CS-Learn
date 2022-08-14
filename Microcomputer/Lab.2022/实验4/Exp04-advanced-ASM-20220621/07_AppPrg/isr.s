//======================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn)
//���¼�¼��20220621
//======================================================================
.include "include.inc"
.align 2
//start ������������
.type  USART2_IRQHandler, function
.global USART2_IRQHandler
//end  ������������

//========================�жϺ�����������===================================
.section .text
//======================================================================
//�������ƣ�UARTA_Handler��UARTA�����жϴ������
//�����������յ�һ���ֽڴ���
//�����ܣ��ط����յ����ֽ�
//======================================================================
USART2_IRQHandler:
	//�����жϣ����ұ����ֳ�
	cpsid  i          //�ؿ������ж�
	push  {r0-r7,lr}   //r7,lr��ջ������r7��������ռ��ã�lr��Ϊ�����ж�ǰpc��ֵ��
	//uint_8 flag
	sub sp,#4         //ͨ���ƶ�spָ���ȡ��ַ
	mov r7,sp         //����ȡ���ĵ�ַ����r7
	//�����ֽ�
	mov r1,r7         //r1=r7 ��Ϊ����һ���ֽڵĵ�ַ
 	mov r0,#UART_User		//���ں�
 	bl  uart_re1      	//���ý���һ���ֽ��Ӻ���
 	ldr r1,=0x20003000  //���յ����ݲ��ֵĴ����ַgcRecvBuf
	bl  emuart_frame  //����֡��������,r0=���ݲ��ֳ���
	cmp r0,#0			//���ɹ�����֡��ʽ����תЭ�����
	bne USART2_IRQHandler_success_revc
	//����ֱ���˳�
	bl  USART2_IRQHandler_exit    //break
USART2_IRQHandler_success_revc:
	//����Э��: (byte)11, (byte)'a', (byte)'u', (byte)'a', (byte)'r', (byte)'t', (byte)'?'
	ldr r0,=0x20003000
	ldrb r0,[r0]		//��ȡ���ݲ��ֵ�һλ->r0
	cmp r0,#11		//�ж�����Э��
	bne USART2_IRQHandler_next
	ldr r0,=handshake_check_str	//string1
	ldr r1,=0x20003000
	add r1,#1			//string2
	mov r2,#6			//�ַ�������
	bl cmp_string
	cmp r0,#0
	bne USART2_IRQHandler_next	//��������Э��
	//����λ�����֣�ȷ��ͨ�Ź�ϵ
	mov r0,#UARTA
	ldr r1,=handshake_send_str
	bl  uart_send_string
	//�����ƣ�Լ1s��Ϩ��
	bl Light_Connected
	bl USART2_IRQHandler_exit    //break
USART2_IRQHandler_next:
	ldr r0,=0x20003000
	ldrb r0,[r0]		//��ȡ���ݲ��ֵ�һλ��ָ�->r0
 	cmp r0,#7			//����7��ָ����Ч
 	bhi USART2_IRQHandler_exit
	ldr r1,=mLightCommand
	str r0,[r1]			//ָ�����mLightCommand����
	//����Light_Control
	bl  Light_Control
	ldr r1,=success_command_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
USART2_IRQHandler_exit:
	//������Σ����һָ��ֳ�
	cpsie   i         //��������ж�
	add r7,#4         //��ԭr7
	mov sp,r7         //��ԭsp
	pop {r0-r7,pc}    //r7,pc��ջ����ԭr7��ֵ��pc��lr,�������ж�ǰ�������ִ��
      
      
//========================�ڲ�����===================================
//======================================================================
//�������ƣ�cmp_string
//����������r0-string1��r1-string2��r2-�ַ�������
//�������أ�0-��ͬ��1-��ͬ
//�������ܣ��Ƚ����ַ����Ƿ���ͬ
//======================================================================
cmp_string:
	push {r1-r7,lr}
	mov r3,#0	//��������
	mov r7,#0	//result, 0=eq, 1=neq
cmp_string_loop:
	cmp r3,r2	//��r3>=r2������ѭ��
	bge cmp_string_exit
	ldrb r4,[r0,r3]	//r4=r0[r3]
	ldrb r5,[r1,r3]	//r4=r1[r3]
	add r3,#1	//r3++
	cmp r4,r5	//����ȣ�����ѭ��
	beq cmp_string_loop
	mov r7,#1	//����ȣ�r6=1������ѭ��
cmp_string_exit:
	mov r0,r7
	pop {r1-r7,pc}


//======================================================================
//�������ƣ�Light_Control
//����˵������
//����ֵ˵������
//�����ܣ����ݵ�ָ�mLightCommand������LED�ƽ��в���
//  1=�������  2=��������  3=���̵���  4=�������(��,��)
//  5=���ϵ���(��,��)  6=���Ƶ���(��,��)  7=���׵���(��,��,��)  0=�����е���
//======================================================================
Light_Control:
	push {r0-r7,lr}
	//���ȹص����еĵ�
	ldr r0,=LIGHT_RED //����
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_GREEN //���̵�
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_BLUE //������
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	//��ȡ��ָ�����r0
	ldr r0,=mLightCommand
	ldr r0,[r0]
	//�ж�r0�ǲ���0
	cmp r0,#0
	bne Light_Control_case_1	//��Ϊ0���жϲ�����
	//��Ϊ0ֱ�ӽ���
	ldr r1,=light_off_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
	bl  Light_Control_exit
Light_Control_case_1:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#1
	bne Light_Control_case_2			//������1ת�ж�2
	//����1�����:RED
	ldr r0,=LIGHT_RED
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_red_on_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
	b Light_Control_exit			//break
Light_Control_case_2:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#2
	bne Light_Control_case_3			//������2ת�ж�3
	//����2�����:BLUE
	ldr r0,=LIGHT_BLUE
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_blue_on_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
	b Light_Control_exit			//break
Light_Control_case_3:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#3
	bne Light_Control_case_4			//������3ת�ж�4
	//����5�����:GREEN
	ldr r0,=LIGHT_GREEN
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_green_on_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
	b Light_Control_exit			//break
Light_Control_case_4:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#4
	bne Light_Control_case_5			//������4ת�ж�5
	//����4�����:BLUE+GREEN
	ldr r0,=LIGHT_BLUE
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_GREEN
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_cyan_on_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
	b Light_Control_exit			//break
Light_Control_case_5:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#5
	bne Light_Control_case_6			//������5ת�ж�6
	//����5�����:RED+BLUE
	ldr r0,=LIGHT_RED
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_BLUE
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_purple_on_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
	b Light_Control_exit			//break
Light_Control_case_6:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#6
	bne Light_Control_case_7			//������6ת�ж�7
	//����6�����:RED+GREEN
	ldr r0,=LIGHT_RED
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_GREEN
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_yellow_on_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
	b Light_Control_exit			//break
Light_Control_case_7:
	ldr r0,=mLightCommand
	ldr r0,[r0]
	cmp r0,#7
	bne Light_Control_exit			//������1ת�ж�2
	//����7�����:RED+BLUE+GREEN
	ldr r0,=LIGHT_RED
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_BLUE
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r0,=LIGHT_GREEN
	ldr r1,=LIGHT_ON
	bl  gpio_set
	ldr r1,=light_white_on_string		//r1ָ���ַ���
 	mov r0,#UART_User        //���ں�
	bl  uart_send_string    //��ԭ���ڻط�
Light_Control_exit:	
	pop  {r0-r7,pc}


//======================================================================
//�������ƣ�Light_Connected
//����˵������
//����ֵ˵������
//�����ܣ��������ƣ����ӳɹ������
//======================================================================
Light_Connected:
	push {r0-r7,lr}
	//���ȹص����еĵ�
	ldr r0,=LIGHT_RED //����
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_GREEN //���̵�
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_BLUE //������
	ldr r1,=LIGHT_OFF
	bl  gpio_set
	ldr r0,=LIGHT_BLUE //������
	ldr r1,=LIGHT_ON
	bl  gpio_set
Light_Connected_exit:	
	pop  {r0-r7,pc}
