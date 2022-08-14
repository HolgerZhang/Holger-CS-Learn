//=====================================================================
//�ļ����ƣ�main.s
//���ܸ�Ҫ������̵���GPIO��������С����˸������printf�����ʾ��Ϣ��
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn)
//�汾���£�20180810-20201128
//=====================================================================
.include "include.inc"    //ͷ�ļ�����Ҫ�����˳�������Ҫʹ�õ���һЩ����
//��0�����ݶ������εĶ���
//��0.1���������ݴ洢data�ο�ʼ��ʵ�����ݴ洢��RAM��
.section .data
//��0.1.1��������Ҫ������ַ�������ż�Ϊ�ַ����׵�ַ,\0Ϊ�ַ���������־
hello_information:           //�ַ������
    .ascii "-------------------------------------------------------\n"
    .ascii " �û���������ɫ��������ܡ�\n"
    .ascii "------------------------------------------------------\n\0"
light_show_red_on:
	.asciz "LIGHT_RED:ON--\n"    //�����״̬��ʾ
light_show_green_on:
	.asciz "LIGHT_GREEN:ON--\n"    //�̵���״̬��ʾ
light_show_blue_on:
	.asciz "LIGHT_BLUE:ON--\n"    //������״̬��ʾ
light_show_off:
	.asciz "LIGHT:OFF--\n"  	 //�ư�״̬��ʾ
light_show_count:
	.asciz "��˸����mLightCount=%d\n"  //��˸������ʾ
light_show_type:
	.asciz "��˸����mLightType=%d\n"  //��˸������ʾ
//��0.1.2���������
.align 4               //.word��ʽ���ֽڶ���
mMainLoopCount:		   //������ѭ���������������ݸ�ʽΪ�֣���ʼֵΪ0
	.word 0
mFlag:				   //����Ƶ�״̬��־��'L'Ϊ����'A'Ϊ����ʼֵΪ��
	.byte 'L'
.align 4
mLightCount:		//����Ƶ���˸���������ݸ�ʽΪ�֣���ʼֵΪ0
    .word 0
.align 4
mLightType:			//����Ƶ����ͣ����ݸ�ʽΪ�֣���ʼֵΪ0������7ʱ����Ϊ0
    .word 0
    
.equ MainLoopNUM,6122338  //��ѭ�������趨ֵ��������

//��0.2���������洢text�ο�ʼ��ʵ�ʴ���洢��Flash��
.section   .text
.syntax unified        //ָʾ�·�ָ��ΪARM��thumbͨ�ø�ʽ
.thumb                 //Thumbָ�
.type main function    //����mainΪ��������
.global main           //��main�����ȫ�ֺ���������оƬ��ʼ��֮�����
.align 2               //ָ������ݲ���2�ֽڶ��룬����Thumbָ�

//--------------------------------------------------------------------                        
//main.cʹ�õ��ڲ�����������

//--------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̣��μ���壩
main:
//��1��======�������֣���ͷ����ѭ��ǰ�ĳ�ʼ������======================
//��1.1������main����ʹ�õľֲ�����

//��1.2�������䡿�����ж�
	//����ѭ��ǰ�ĳ�ʼ����Ҫ�ȹ��жϵ�ԭ��
	//���豸�ĳ�ʼ�������г������ж��¼������ʼ�������ᱻ��ϣ�
	//Ȼ���жϴ�����Ҫʹ�õ���Щ�豸���Ӷ��ᵼ��һЩ�е����⡣
	cpsid i   
//��1.3����������ʹ�õľֲ���������ֵ
	
//��1.4����ȫ�ֱ�������ֵ
	
//��1.5���û�����ģ���ʼ��
	//��ʼ�����, r0��r1��r2��gpio_init����ڲ�����ʹ�üĴ������ݣ�
	ldr r0,=LIGHT_RED     //r0ָ���˿ں�����(�˿ں�|(���ź�))����=,����>=256,����ldr����������Ѱַ��
	mov r1,#GPIO_OUTPUT    //r1ָ�����ŷ���Ϊ���
	mov r2,#LIGHT_OFF      //r2ָ�����ŵĳ�ʼ״̬Ϊ��
	bl  gpio_init          //����gpio��ʼ��������gpio.s��
	//��������к������õĲ���������ͨ��ͨ�üĴ�����R0-R12�����õ�λ�Ĵ���R0-R7����ɵ�
	//��ʼ���̵�, r0��r1��r2��gpio_init����ڲ�����ʹ�üĴ������ݣ�
	ldr r0,=LIGHT_GREEN     //r0ָ���˿ں�����(�˿ں�|(���ź�))����=,����>=256,����ldr����������Ѱַ��
	mov r1,#GPIO_OUTPUT    //r1ָ�����ŷ���Ϊ���
	mov r2,#LIGHT_OFF      //r2ָ�����ŵĳ�ʼ״̬Ϊ��
	bl  gpio_init          //����gpio��ʼ��������gpio.s��
	//��ʼ������, r0��r1��r2��gpio_init����ڲ�����ʹ�üĴ������ݣ�
	ldr r0,=LIGHT_BLUE     //r0ָ���˿ں�����(�˿ں�|(���ź�))����=,����>=256,����ldr����������Ѱַ��
	mov r1,#GPIO_OUTPUT    //r1ָ�����ŷ���Ϊ���
	mov r2,#LIGHT_OFF      //r2ָ�����ŵĳ�ʼ״̬Ϊ��
	bl  gpio_init          //����gpio��ʼ��������gpio.s��

//��1.6��ʹ��ģ���ж�
    
//��1.7�������䡿�����жϣ���ʼ��������
	cpsie  i  
	//��ʾhello_information������ַ���
	ldr r0,=hello_information   //����ʾ�ַ����׵�ַ
	bl  printf		            //����printf��ʾ�ַ���
	
	//bl .   //�ڴ˴�׮(.��ʾ��ǰ��ַ)����ⷢ�������Ϊ���������ˣ�
	//Ƕ��ʽϵͳ�����ֵ��Է�ʽ��
	//1��ʹ�÷��������ԣ���Ҫ�ض��ı������Լ����������豸����ʵ��������������/SWD
	//2��ʹ�ô��ڻ�ȡ��λ���ĳ�������״̬�����öϵ㣨��ѭ������ʹ����ͣ��ĳһλ�ã��۲�����Ƿ���ȷ
	//   ע��������Ҫɾ����׮��λ��
	
//��1��======�������֣���β��=======================================

//��2��======��ѭ�����֣���ͷ��=====================================
	main_loop:                      //��ѭ����ǩ����ͷ��
//��2.1����ѭ����������mMainLoopCount+1
		ldr r2,=mMainLoopCount   //r2��mMainLoopCount�ĵ�ַ��mMainLoopCount�ǵ�ַ��
		ldr r1, [r2]             //��r2����ĵ�ַ�д洢��ֵ�浽r1��
		add r1,#1                //r1=r1+1
		str r1,[r2]	            //��r1�е�ֵ�浽r2����ĵ�ַ��ȥ
//��2.2��δ�ﵽ��ѭ�������趨ֵ������ѭ��
        ldr r2,=MainLoopNUM   //��MainLoopNUM���ڵĵ�ַ��ȡ������r2��MainLoopNUM�ǳ�����
		cmp r1,r2             //�Ƚ�r1��r2
		blO  main_loop       //δ�ﵽ������ѭ����lo���޷�����С�ڣ�
		//bne  main_loop     //δ�ﵽ������ѭ����ne�������ڣ�
// 2.1��2.2ʵ�ֵĹ����ǣ�������ѭ��ִ��MainLoopNUM�βż���ִ�У�����ʱ���ã��Ӷ��ﵽ���������Ч��
// �ȼ��ڸ߼������еģ� for (mMainLoopCount=0; mMainLoopCount<MainLoopNUM; mMainLoopCount++);
//��2.3���ﵽ��ѭ�������趨ֵ��ִ��������䣬���еƵ���������
//��2.3.1�����ѭ���������� mMainLoopCount=0
		ldr r2,=mMainLoopCount     //r2��mMainLoopCount�ĵ�ַ
		mov r1,#0                  //���ﵽѭ����������ѭ��������ֵ����
		str r1,[r2]	               //��r1�е�ֵ�浽r2���ڵ��ڴ��ַ��
//��2.3.2�����״̬��־mFlagΪ'L'���Ƶ���˸����+1����ʾ���ı��״̬����־�����ݵƵ���������Ӧ�ĵƣ��޸ĵƵ�����
		//�жϵƵ�״̬��־
		ldr r2,=mFlag		   
		ldr r6,[r2]
		cmp r6,#'L'			
		bne main_light_off	   //mFlag������'L'ת�ص�
		//mFlag����'L'���������
		ldr r3,=mLightCount	   //�Ƶ���˸����mLightCount+1
		ldr r1,[r3]
		add r1,#1				
		str r1,[r3]
		ldr r0,=light_show_count  //��ʾ�Ƶ���˸����ֵ
		ldr r2,=mLightCount
		ldr r1,[r2]
		bl  printf	
		ldr r2,=mFlag           //�Ƶ�״̬��־��Ϊ'A'����һ������ƣ�
		mov r7,#'A'
		str r7,[r2]             
		//����mLightType����ͬ��ɫ�ĵ�
		ldr r0,=light_show_type  //��ʾ�Ƶ�����mLightType
		ldr r2,=mLightType
		ldr r1,[r2]
		bl  printf
		ldr r2,=mLightType		//��ȡ�Ƶ�����mLightType
		ldr r1,[r2]
		cmp r1,#0
		bne case_type_1			//������0ת�ж�1
		//����0�����:���
		ldr r0,=LIGHT_RED      //�����
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_red_on    //��ʾ�������ʾ
		bl  printf
		b end_case_type			//break
	case_type_1:
		ldr r2,=mLightType		//��ȡ�Ƶ�����mLightType
		ldr r1,[r2]
		cmp r1,#1
		bne case_type_2			//������1ת�ж�2
		//����1�����:�̵�
		ldr r0,=LIGHT_GREEN      //���̵�
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_green_on    //��ʾ�̵�����ʾ
		bl  printf
		b end_case_type			//break
	case_type_2:
		ldr r2,=mLightType		//��ȡ�Ƶ�����mLightType
		ldr r1,[r2]
		cmp r1,#2
		bne case_type_3			//������2ת�ж�3
		//����2�����:����
		ldr r0,=LIGHT_BLUE      //������
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_blue_on    //��ʾ��������ʾ
		bl  printf
		b end_case_type			//break
	case_type_3:
		ldr r2,=mLightType		//��ȡ�Ƶ�����mLightType
		ldr r1,[r2]
		cmp r1,#3
		bne case_type_4			//������3ת�ж�4
		//����3�����:���+�̵�=��
		ldr r0,=LIGHT_RED      //�����
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_red_on    //��ʾ�������ʾ
		bl  printf
		ldr r0,=LIGHT_GREEN      //���̵�
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_green_on    //��ʾ�̵�����ʾ
		bl  printf
		b end_case_type			//break
	case_type_4:
		ldr r2,=mLightType		//��ȡ�Ƶ�����mLightType
		ldr r1,[r2]
		cmp r1,#4
		bne case_type_5			//������4ת�ж�5
		//����4�����:���+����=��
		ldr r0,=LIGHT_RED      //�����
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_red_on    //��ʾ�������ʾ
		bl  printf
		ldr r0,=LIGHT_BLUE      //������
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_blue_on    //��ʾ��������ʾ
		bl  printf
		b end_case_type			//break
	case_type_5:
		ldr r2,=mLightType		//��ȡ�Ƶ�����mLightType
		ldr r1,[r2]
		cmp r1,#5
		bne case_type_6			//������5ת6
		//����5�����:�̵�+����=��
		ldr r0,=LIGHT_GREEN      //���̵�
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_green_on    //��ʾ�̵�����ʾ
		bl  printf
		ldr r0,=LIGHT_BLUE      //������
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_blue_on    //��ʾ��������ʾ
		bl  printf
		b end_case_type			//break
	case_type_6:
		//����6�����:���+�̵�+����=��
		ldr r0,=LIGHT_RED      //�����
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_red_on    //��ʾ�������ʾ
		bl  printf
		ldr r0,=LIGHT_GREEN      //���̵�
		ldr r1,=LIGHT_ON
		bl  gpio_set
		ldr r0, =light_show_green_on    //��ʾ�̵�����ʾ
		bl  printf
		ldr r0,=LIGHT_BLUE      //������
		ldr r1,=LIGHT_ON
		bl  gpio_set          
		ldr r0, =light_show_blue_on    //��ʾ��������ʾ
		bl  printf	
	end_case_type:
		//�޸ĵƵ�����mLightType+1����mLightType>=7��mLightType=0
		ldr r3,=mLightType		//�Ƶ�����mLightType
		ldr r1,[r3]
		add r1,#1				//mLightType++
		cmp r1,#7
		blo type_not_to_zero    //��mLightType>=7��mLightType=0
		mov r1,#0
	type_not_to_zero:  				//��mLightType<7��mLightType++�󲻸ı�
		str r1,[r3]
		//mFlag����'L'���������ϣ�ת
		b main_exit  
//��2.3.3�����״̬��־mFlagΪ'A'���ı��״̬����־�������еĵ�
	main_light_off:
        ldr r2,=mFlag		   //�Ƶ�״̬��־��Ϊ'L'����һ�������ƣ�
		mov r7,#'L'
		str r7,[r2]   
		ldr r0,=LIGHT_RED      //����
		ldr r1,=LIGHT_OFF
		bl  gpio_set
		ldr r0,=LIGHT_GREEN      //���̵�
		ldr r1,=LIGHT_OFF
		bl  gpio_set
		ldr r0,=LIGHT_BLUE      //������
		ldr r1,=LIGHT_OFF
		bl  gpio_set
		ldr r0, =light_show_off    //��ʾ������ʾ
		bl  printf	
	main_exit:
		b main_loop                 //����ѭ��
//��2��======��ѭ�����֣���β��=====================================
.end     //�������������־����β��
