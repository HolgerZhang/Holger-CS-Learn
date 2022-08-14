//=====================================================================
//�ļ����ƣ�main.s
//���ܸ�Ҫ������̵���SysTick����С����˸������printf�����ʾ��Ϣ��
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn)
//�汾���£�20180810-20201130
//=====================================================================
.include "include.inc"    //ͷ�ļ�����Ҫ�����˳�������Ҫʹ�õ���һЩ����
.include "systick.inc"
//��0�����ݶ������εĶ���
//��0.1��ȫ�ֱ�������
.global gcount  //50�μ�����Ԫ
.global hour    //ʱ
.global minute  //��
.global second  //��
.global data_format
.global new_hour    //��ʱ
.global new_minute  //�·�
.global new_second  //����
.global received_data
.global recv_state
.global last_second
//��0.2���������ݴ洢data�ο�ʼ��ʵ�����ݴ洢��RAM��
.section .data
//��0.2.1��������Ҫ������ַ�������ż�Ϊ�ַ����׵�ַ,\0Ϊ�ַ���������־
time_data_format:
    .ascii "%d\0"                   //��ʱ����ʹ�õ����ݸ�ʽ���Ʒ�
time_show0:
    .ascii "0\0"	                //�ַ��㣬���ڽ�ʱ���벹����λ
time_show1:
    .ascii ":\0"                    //����ʱ����ķָ�
time_show2:
    .ascii "\n\0"                   //���ڻ���
data_format:
    .ascii "%d\n\0"                 //printfʹ�õ����ݸ�ʽ���Ʒ�
light_show1:
	.ascii "LIGHT_BLUE:ON--\n\0"    //����״̬��ʾ   
light_show2:
	.ascii "LIGHT_BLUE:OFF--\n\0"   //�ư�״̬��ʾ
light_show3:
	.ascii "�Ƶ���˸����mLightCount=\0"    //����״̬��ʾ  
debug_recv_state_received_data_show:
	.string "recv_state: %d, received_data: %d\n"

//��0.2.2���������
.align 4               //.word��ʽ���ֽڶ���
mMainLoopCount:		   //������ѭ����������
	.word 0
mFlag:				   //����Ƶ�״̬��־,1Ϊ����0Ϊ��
	.byte 'A'	
.align 4
mLightCount:
    .word 0
gcount:      //50�μ�����Ԫ
    .word 0
hour:        //ʱ
    .word 12
minute:      //��
    .word 0
second:      //��
    .word 0
last_second:  //��һ�μ�¼����
    .word 0
received_data:  //���ڽ��ܵ�������
	.word 0
recv_state:		//����״̬
	.word 8
new_hour:        //�µ�ʱ
    .word 12
new_minute:      //�µķ�
    .word 0
new_second:      //�µ���
    .word 0

//��0.3���������洢text�ο�ʼ��ʵ�ʴ���洢��Flash��
.section   .text
.syntax unified           		  //ָʾ�·�ָ��ΪARM��thumbͨ�ø�ʽ
.thumb                    		  //Thumbָ�
.type main function               //����mainΪ��������                     
.global main               	      //��main�����ȫ�ֺ���������оƬ��ʼ��֮�����
.align 2                          //ָ������ݲ���2�ֽڶ��룬����Thumbָ�

//----------------------------------------------------------------------                        
//����ʹ�õ����ڲ�����
//main.cʹ�õ��ڲ�����������

//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̣��μ���壩
main:
//��1��======�������֣���ͷ����ѭ��ǰ�ĳ�ʼ������==========================================
//��1.1������main����ʹ�õľֲ�����

//��1.2�������䡿�����ж�
	cpsid i   
//��1.3����������ʹ�õľֲ���������ֵ
	
//��1.4����ȫ�ֱ�������ֵ
	
//��1.5���û�����ģ���ʼ��
//  ��ʼ������, r0��r1��r2��gpio_init����ڲ���
	ldr r0,=LIGHT_BLUE     //r0ָ���˿ں����ţ���=������Ϊ����>=256����Ҫ��ldrָ�
	mov r1,#GPIO_OUTPUT    //r1ָ�����ŷ���Ϊ���
	mov r2,#LIGHT_ON       //r2ָ�����ŵĳ�ʼ״̬Ϊ��
	bl  gpio_init          //����gpio��ʼ������
//  systick��ʱ����ʼ��
	mov r0,#20
	bl systick_init//ÿ20�����ж�һ��
//  ��ʼ������UARTA
	mov r0,#UARTA               //r0=���´���
	ldr r1,=UART_BAUD
	bl  uart_init
//��1.6��ʹ��ģ���ж�
	mov r0,#UARTA               //r0ָ�����ں�
	bl  uart_enable_re_int     //���ô����ж�ʹ�ܺ���

//��1.7�������䡿�����ж�
	cpsie  i  
	
	//bl .   //�ڴ˴�׮(.��ʾ��ǰ��ַ)����ⷢ�������Ϊ���������ˣ�
	
//��1��======�������֣���β��==========================================

//��2��======��ѭ�����֣���ͷ��========================================
main_loop:                      //��ѭ����ǩ����ͷ��
        ldr r0,=second
        ldr r0,[r0]               //��ȡ����
        ldr r1,=last_second        
        ldr r1,[r1]               //��ȡ��һ�μ�¼����
        cmp r0,r1               //�ж��Ƿ����µ�һ��
        beq main_loop           //��δ���µ�һ�룬����ѭ��
        ldr r1,=last_second        
        str r0,[r1]               //���򣬸��¼�¼����        
        
		//����������ʱ���򴮿ڷ�������ʱ��
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
        
        //���ʱ��
        ldr r2,[r2]
        ldr r1,=hour
        ldr r1,[r1]
        cmp r1,#10             //��ȡСʱ�����ж�λ��
        bcs hour_two_bits
        ldr r0,=time_show0      //��Ϊһλ������һ��0
        bl  printf
        
hour_two_bits:
        ldr r0,=time_data_format
        ldr r1,=hour
        ldr r1,[r1]
        bl  printf              //���Сʱ��
        
        ldr r0,=time_show1
        bl  printf              //�����
        
        ldr r1,=minute
        ldr r1,[r1]
        cmp r1,#10
        bcs minute_two_bits     //��ȡ�������ж�λ��
        ldr r0,=time_show0      //��Ϊһλ������һ��0
        bl  printf
        
minute_two_bits:    
        ldr r0,=time_data_format
        ldr r1,=minute
        ldr r1,[r1]
        bl  printf	           //���������
        
        ldr r0,=time_show1
        bl  printf              //�����
        
        ldr r1,=second
        ldr r1,[r1]
        cmp r1,#10
        bcs second_two_bits     //��ȡ�����ж�λ��
        ldr r0,=time_show0
        bl  printf             //��Ϊһλ������һ��0
        
second_two_bits: 
        ldr r0,=time_data_format
        ldr r1,=second
        ldr r1,[r1]
        bl  printf	          //���������
        
        ldr r0,=time_show2
        bl  printf            //������з�
//��2.3.2�����״̬��־mFlagΪ'L'���Ƶ���˸����+1����ʾ���ı��״̬����־	
		//�жϵƵ�״̬��־
		ldr r2,=mFlag		   
		ldr r6,[r2]
		cmp r6,#'L'			
		bne main_light_off	   //mFlag������'L'ת
		//mFlag����'L'���
		ldr r3,=mLightCount	   //�Ƶ���˸����mLightCount+1
		ldr r1,[r3]
		add r1,#1				
		str r1,[r3]
		ldr r0,=light_show3   //��ʾ���Ƶ���˸����mLightCount=��
		bl  printf				
		ldr r0,=data_format    //��ʾ�Ƶ���˸����ֵ
		ldr r2,=mLightCount
		ldr r1,[r2]
		bl  printf	
		ldr r2,=mFlag           //�Ƶ�״̬��־��Ϊ'A'
		mov r7,#'A'
		str r7,[r2]             
		ldr r0,=LIGHT_BLUE      //����
		ldr r1,=LIGHT_ON
		bl  gpio_set          
		ldr r0, =light_show1    //��ʾ������ʾ
		bl  printf	
		//mFlag����'L'���������ϣ�ת
		b main_exit  
//��2.3.3�����״̬��־mFlagΪ'A'���ı��״̬����־
main_light_off:
        ldr r2,=mFlag		   //�Ƶ�״̬��־��Ϊ'L'        
		mov r7,#'L'
		str r7,[r2]   
        ldr r0,=LIGHT_BLUE      //����
		ldr r1,=LIGHT_OFF
		bl  gpio_set  
        ldr r0, =light_show2    //��ʾ�ư���ʾ
		bl  printf	
main_exit:
	b main_loop                 //����ѭ��
//��2��======��ѭ�����֣���β��========================================
.end         //�������������־����β��