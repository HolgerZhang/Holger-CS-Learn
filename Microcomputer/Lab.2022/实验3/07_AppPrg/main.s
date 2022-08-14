//=======================================================================================
//�ļ����ƣ�main.s
//���ܸ�Ҫ��Flash����������֤���飨����printf�����ʾ��Ϣ��
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn)
//�汾���£�20180810-20201129
//=======================================================================================
.include "include.inc"    //ͷ�ļ�����Ҫ�����˳�������Ҫʹ�õ���һЩ����
//��0�����ݶ������εĶ���
//��0.1���������ݴ洢data�ο�ʼ��ʵ�����ݴ洢��RAM��
.section .data
//��0.1.1��������Ҫ������ַ�������ż�Ϊ�ַ����׵�ַ,\0Ϊ�ַ���xfgi������־
hello_information:           //�ַ������
    .ascii "----------------------------------------------------------------------\n"
    .ascii "���«��ʾ��\n"
    .ascii "           Flash����������֤����                                       \n"
    .ascii "     Flash�����й̶����߳���������Ƶ���߳���������Flash����           \n"
    .ascii "     ���ԣ�Flash����ֻ��оƬ�ϵ磬�������ص�ʱ�����һ��                \n"        
    .ascii "----------------------------------------------------------------------\n\0"
data_format:
    .ascii "%d\n\0"                 //printfʹ�õ����ݸ�ʽ���Ʒ�
	
	
//------------------------------------flash���������ʾ--------------------------------
type_str:
    .string "Flash���������ʾ��64����ǰ32�ֽ�����Ϊ�� %s"

str_1:            			           //�ַ�����ǩ
    .string "Assembly call c's printf!\r\n"  //ʹ��˵����01_Doc���ĵ�
str_2:            			           //�ַ�����ǩ
    .string "Assembly call c's UARTA!\r\n"   //ʹ��˵����01_Doc���ĵ�

flash_str1:
    .string "Flash���������ʾ������������Ϊ��!\r\n"             //flash�пս����ʾ��䣬
flash_str2:
	.string "Flash���������ʾ�����������ݲ�Ϊ��!!!!!\r\n"    //flash�пս����ʾ��䣬
flash_str3:
    .string "Flash���������ʾ���������ݲ����ɹ�!\r\n"             //flash���������ʾ��䣬
flash_str4:
	.string "Flash���������ʾ���������ݲ������ɹ�!!!!!\r\n"    //flash���������ʾ��䣬
flash_str5:
    .string "Flash���������ʾ����������д��ɹ�!\r\n"             //flashд������ʾ��䣬
flash_str6:
	.string "Flash���������ʾ����������д�벻�ɹ�!!!!!\r\n"    //flashд������ʾ��䣬
.global flash_str1
.global flash_str2
.global flash_str3
.global flash_str4
.global flash_str5
.global flash_str6

unknown_info_str:
	.string "δ֪�Ĳ�����\r\n"
.global unknown_info_str

info_str1:
	.string "Flash������ʾ���ж�64���������Ƿ�Ϊ�գ�\r\n"    //Flash�пս����ʾ��䣬
info_str2:
	.string "Flash������ʾ������64������Ȼ�����ж�64�����Ƿ�Ϊ�գ����߳������Ƿ�ɹ���\r\n"    //flash�пս����ʾ��䣬
info_str3:
	.string "Flash������ʾ����64����ָ����ַд�����ݣ��ٶ���д������ݣ������޴���!\r\n"    //flash�пս����ʾ��䣬

flash_Content:
	.string "Welcome to Soochow University!\r\n"    //����Ҫд��Flash������

flash_ContentDetail:
	.string "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n"   //�洢��Flash�ж���������
.global flash_ContentDetail
	
//dataRecvBuff:	//���յ������ݲ���
//	.ascii "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
//.global dataRecvBuff

handshake_check_str:
	.string "auart?"
.global handshake_check_str

handshake_send_str:
	.string "I am an uart"
.global handshake_send_str

.equ addr,0x8020000	   //64�����׵�ַ

number:
  .word  0x800

	
	
//��0.1.2���������
.align 4               //.word��ʽ���ֽڶ���
mMainLoopCount:		   //������ѭ����������
	.word 0
mFlag:				   //����Ƶ�״̬��־,1Ϊ����0Ϊ��
	.byte 'A'	
.align 4
mLightCount:
    .word 0

.equ MainLoopNUM,556677  //��ѭ�������趨ֵ��������

//��0.2���������洢text�ο�ʼ��ʵ�ʴ���洢��Flash��
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
	//��ʼ������, r0��r1��r2��gpio_init����ڲ���
	ldr r0,=LIGHT_BLUE     //r0ָ���˿ں����ţ���=������Ϊ����>=256����Ҫ��ldrָ�
	mov r1,#GPIO_OUTPUT    //r1ָ�����ŷ���Ϊ���
	mov r2,#LIGHT_ON       //r2ָ�����ŵĳ�ʼ״̬Ϊ��
	bl  gpio_init          //����gpio��ʼ������
    //Flash��ʼ��
    bl  flash_init
    //��ʼ������UARTA
	mov r0, #UARTA
    ldr r1, =UART_BAUD
	bl  uart_init

//��1.6��ʹ��ģ���ж�
	mov r0, #UARTA			//r0ָ�����ں�
    bl  uart_enable_re_int	//���ô����ж�ʹ�ܺ���
//��1.7�������䡿�����ж�
	cpsie  i  

	ldr r0,=hello_information   //r0=����ʾ�ַ���
	bl  printf		            //����printf��ʾ�ַ���

//��1.8����Flash�Ĳ���
	//�ж�64�����Ƿ�Ϊ��
	//�����ʾ��Ϣ��Flash������ʾ���ж�64���������Ƿ�Ϊ�գ���
	mov r0, #UART_User		//�򴮿ڷ�����Ϣ
	ldr r1, =info_str1
	bl  uart_send_string
	ldr r0, =info_str1		//ʹ��printf���
	bl  printf
	//�ж�64�����Ƿ�Ϊ��
	ldr r0, =addr
	ldr r1, =number
	ldr r1, [r1]
	bl  flash_isempty		//flash_isempty(addr, number)
	cmp r0, #1				//��Ϊ�գ�r0=1����ת��
	beq flash_empty
	//��Ϊ�գ�������������
	//�����Ϊ����ʾ��Ϣ
	mov r0, #UART_User		//�򴮿ڷ�����Ϣ
	ldr r1, =flash_str2
	bl  uart_send_string
	ldr r0, =flash_str2		//ʹ��printf���
	bl  printf
	//�����������ݵ�flash_ContentDetail
	ldr r0, =flash_ContentDetail
	ldr r1, =addr
	mov r2, #0x20
	bl flash_read_physical	//flash_read_physical(&flash_ContentDetail, addr, 0x20)
	//�����������
	mov r0, #UART_User		//�򴮿ڷ�����Ϣ
	ldr r1, =flash_ContentDetail
	bl  uart_send_string
	ldr r0, =type_str		//ʹ��printf���
	ldr r1, =flash_ContentDetail
	bl  printf
	//���������������ݣ����п�
	//����������пյ���ʾ��Ϣ
	mov r0, #UART_User		//�򴮿ڷ�����Ϣ
	ldr r1, =info_str2
	bl  uart_send_string
	ldr r0, =info_str2		//ʹ��printf���
	bl  printf
	//����������������
	mov r0, #64
	bl flash_erase			//flash_erase(64)
	//�п�
	ldr r0, =addr
	ldr r1, =number
	ldr r1, [r1]
	bl flash_isempty		//flash_isempty(addr, number)
	cmp r0, #1				//��Ϊ�գ�r0=1����ת�����ɹ�������
	beq flash_empty
	//�Բ�Ϊ�ա�����ʧ�ܡ��������ʾ��Ϣ������
	mov r0, #UART_User		//�򴮿ڷ�����Ϣ
	ldr r1, =flash_str2
	bl  uart_send_string
	ldr r0, =flash_str2		//ʹ��printf���
	bl  printf
	bl  main_loop			//������Flash�Ĳ���
flash_empty:     //Ϊ�գ�д������
	//�������Ϊ�յ���ʾ��Ϣ
	mov r0, #UART_User		//�򴮿ڷ�����Ϣ
	ldr r1, =flash_str1
	bl  uart_send_string
	ldr r0, =flash_str1		//ʹ��printf���
	bl  printf
	//�������Ϊ�յ���ʾ��Ϣ
	mov r0, #UART_User		//�򴮿ڷ�����Ϣ
	ldr r1, =info_str3
	bl  uart_send_string
	ldr r0, =info_str3		//ʹ��printf���
	bl  printf
	//��64����д������
//	ldr r0, =addr
//	mov r1, #0x20
//	ldr r2, =flash_Content
//	bl flash_write_physical	//flash_write_physical(addr, 0x20, &flash_Content)
	//flash_write(64, 0, 32, &flash_Content);
	mov r0, #64
	mov r1, #0
	mov r2, #32
	ldr r3, =flash_Content
	bl flash_write
	//��ȡ64��������
	ldr r0, =flash_ContentDetail
	ldr r1, =addr
	mov r2, #0x20
	bl flash_read_physical	//flash_read_physical(&flash_ContentDetail, addr, 0x20)
	//�����������
	mov r0, #UART_User		//�򴮿ڷ�����Ϣ
	ldr r1, =flash_ContentDetail
	bl  uart_send_string
	ldr r0, =type_str		//ʹ��printf���
	ldr r1, =flash_ContentDetail
	bl  printf	
//��1��======�������֣���β��==========================================

//��2��======��ѭ�����֣���ͷ��========================================
main_loop:                      //��ѭ����ǩ����ͷ��
//��2.1����ѭ����������mMainLoopCount+1
		ldr r2,=mMainLoopCount     //r2��mMainLoopCount�ĵ�ַ
		ldr r1, [r2]
		add r1,#1
		str r1,[r2]	
//��2.2��δ�ﵽ��ѭ�������趨ֵ������ѭ��
        ldr r2,=MainLoopNUM
		cmp r1,r2
		blO  main_loop     //δ�ﵽ������ѭ��
//��2.3���ﵽ��ѭ�������趨ֵ��ִ��������䣬���еƵ���������
//��2.3.1�����ѭ����������
		ldr r2,=mMainLoopCount     //r2��mMainLoopCount�ĵ�ַ
		mov r1,#0
		str r1,[r2]	
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

		ldr r2,=mFlag           //�Ƶ�״̬��־��Ϊ'A'
		mov r7,#'A'
		str r7,[r2]             
		ldr r0,=LIGHT_BLUE      //����
		ldr r1,=LIGHT_ON
		bl  gpio_set          

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

main_exit:
	b main_loop                 //����ѭ��
//��2��======��ѭ�����֣���β��========================================
.end         //�������������־����β��
