//=======================================================================================
//�ļ����ƣ�main.s
//���ܸ�Ҫ����λ��ͨ�����ڵ����������ָ����֣�������ɫLED��
//��Ȩ���У����
//�汾���£�20220621
//=======================================================================================
.include "include.inc"    //ͷ�ļ�����Ҫ�����˳�������Ҫʹ�õ���һЩ����
//��0�����ݶ������εĶ���
//��0.1���������ݴ洢data�ο�ʼ��ʵ�����ݴ洢��RAM��
.section .data
//��0.1.1��������Ҫ������ַ�������ż�Ϊ�ַ����׵�ַ,\0Ϊ�ַ���xfgi������־
instruction:
	.ascii "----------------------------------------------------------------------\n"
    .ascii "���«��ʾ��\n"
    .ascii "��ʵ����Ҫʵ�ֵĹ����ǣ���λ��ͨ�����ڵ����������ָ����֣�������ɫLED��\n"
    .ascii "  1=�������  2=��������  3=���̵���  4=�������\n"
    .ascii "  5=���ϵ���  6=���Ƶ���  7=���׵���  0=�����е���\n"
    .ascii "----------------------------------------------------------------------\n\0"
print_command_string:
	.string "Command #%d: %d\r\n"		//��ӡָ����Ϣ
success_command_string:
	.string "Command executed!\r\n"		//���ڷ��ص���Ϣ���ɹ�ִ�У�
unknown_command_string:
	.string "Unknown command!\r\n"		//���ڷ��ص���Ϣ��δָ֪�
.global print_command_string
.global success_command_string
.global unknown_command_string
//����״̬����ַ���
light_red_on_string:
	.string "[RED LED ON] "
.global light_red_on_string
light_blue_on_string:
	.string "[BLUE LED ON] "
.global light_blue_on_string
light_green_on_string:
	.string "[GREEN LED ON] "
.global light_green_on_string
light_cyan_on_string:
	.string "[CYAN LED ON] "
.global light_cyan_on_string
light_purple_on_string:
	.string "[PURPLE LED ON] "
.global light_purple_on_string
light_yellow_on_string:
	.string "[YELLOW LED ON] "
.global light_yellow_on_string
light_white_on_string:
	.string "[WHITE LED ON] "
.global light_white_on_string
light_off_string:
	.string "[LED OFF] "
.global light_off_string

//�����ַ���
handshake_check_str:
	.string "auart?"
.global handshake_check_str
handshake_send_str:
	.string "I am an uart"
.global handshake_send_str

//��0.1.2���������
.align 4               //.word��ʽ���ֽڶ���
mMainLoopCount:		   //������ѭ���������������ݸ�ʽΪ�֣���ʼֵΪ0
	.word 0
.global mMainLoopCount
.align 4               //.word��ʽ���ֽڶ���
mLightCommand:			//����ƿ�������
	.word 0
.global mLightCommand

.equ MainLoopNUM,10000000  //��ѭ�������趨ֵ��������

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
//  ��ʼ��LED��, r0��r1��r2��gpio_init����ڲ���
	ldr r0,=LIGHT_BLUE     //r0ָ���˿ں����ţ���=������Ϊ����>=256����Ҫ��ldrָ�
	mov r1,#GPIO_OUTPUT    //r1ָ�����ŷ���Ϊ���
	mov r2,#LIGHT_ON       //r2ָ�����ŵĳ�ʼ״̬Ϊ��
	bl  gpio_init          //����gpio��ʼ������
	ldr r0,=LIGHT_RED     //r0ָ���˿ں����ţ���=������Ϊ����>=256����Ҫ��ldrָ�
	mov r1,#GPIO_OUTPUT    //r1ָ�����ŷ���Ϊ���
	mov r2,#LIGHT_ON       //r2ָ�����ŵĳ�ʼ״̬Ϊ��
	bl  gpio_init          //����gpio��ʼ������
	ldr r0,=LIGHT_GREEN     //r0ָ���˿ں����ţ���=������Ϊ����>=256����Ҫ��ldrָ�
	mov r1,#GPIO_OUTPUT    //r1ָ�����ŷ���Ϊ���
	mov r2,#LIGHT_ON       //r2ָ�����ŵĳ�ʼ״̬Ϊ��
	bl  gpio_init          //����gpio��ʼ������
//  ��ʼ������UARTA
	mov r0,#UARTA               //r0=���´���
    ldr r1,=UART_BAUD
    bl  uart_init
//��1.6��ʹ��ģ���ж�
	mov r0,#UARTA               //r0ָ�����ں�
    bl  uart_enable_re_int     //���ô����ж�ʹ�ܺ���
//��1.7�������䡿�����ж�
	cpsie  i  
	ldr r0,=instruction
	bl printf
	
	//bl .   //�ڴ˴�׮(.��ʾ��ǰ��ַ)����ⷢ�������Ϊ���������ˣ�
	
//��1��======�������֣���β��==========================================

//��2��======��ѭ�����֣���ͷ��========================================
main_loop:                      //��ѭ����ǩ����ͷ��
	b main_loop                 //��ѭ��
//��2��======��ѭ�����֣���β��========================================

.end         //�������������־����β��
