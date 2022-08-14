//==========================================================================
//�ļ����ƣ�systick.s
//���ܸ�Ҫ��systick ����Դ�ļ�
//��Ȩ���У����ݴ�ѧǶ��ʽ���������о�����(sumcu.suda.edu.cn)
//���¼�¼��2019-10-23   V1.0
//==========================================================================
.include "systick.inc"
//===========================================================================
//�������ƣ�systick_init
//�������أ���
//����˵����int_ms:�жϵ�ʱ��������λms �Ƽ�ѡ��5,10,......
//���ܸ�Ҫ����ʼ��SysTickģ�飬�����жϵ�ʱ����
//˵    �����ں�ʱ��Ƶ��MCU_SYSTEM_CLK_KHZ�궨����mcu.h��
//systick��msΪ��λ��349��2^24/48000������ȡ����������Χ1~349��
//===========================================================================
.type systick_init function          //����systick_initΪ��������                     
.global systick_init                 //��systick_init�����ȫ�ֺ���������оƬ��ʼ��֮�����
systick_init:
    push {r0,r1,r2,lr}
    ldr r2,=SysTick_CTRL     //����ǰ�ȹر�systick��CTRL���Ƽ�״̬�Ĵ���
    mov r1,#0
    str r1,[r2]
    ldr r2,=SysTick_VAL      //�����������VAL ������
    str r1,[r2]
//�Դ�����������
    cmp r0,#1                
    bcs systick_init_label1  
    mov r0,#10              //����С��1����ֵΪ10
systick_init_label1:
	ldr r1,=INTERVAL_TIME_MAX
    cmp r1,r0
    bcs systick_init_label2
	mov r0,#10              //���δ������ֵ����ֵΪ10
systick_init_label2:
    ldr r1,=MCU_SYSTEM_CLK_KHZ
    mul r1,r1,r0
    ldr r2,=SysTick_LOAD
    str r1,[r2]            //���ؼĴ�����ֵ
    ldr r1,=SysTick_CTRL
    ldr r2,[r1]
    ldr r0,=SysTick_CTRL_CLKSOURCE_Msk
    orr r2,r2,r0
    str r2,[r1]            //���Ƽ�״̬�Ĵ�����ֵ
//�趨 SysTick���ȼ�Ϊ3(SHPR3�Ĵ���������ֽ�=0xC0)
    ldr r0,=SysTick_IRQn 
    mov r1,#1
    ldr r2,=__NVIC_PRIO_BITS
    lsl r1,r2              //���Ʋ���
    sub r1,#1
//    ldr r2,=set_irq_priority//�����������ȼ�����
//   blx r2
//�����ж�,ʹ�ܸ�ģ��,��ʼ����
    ldr r0,=SysTick_CTRL_ENABLE_Msk
    ldr r1,=SysTick_CTRL_TICKINT_Msk
    orr r0,r0,r1           //�����
    ldr r1,=SysTick_CTRL
    ldr r2,[r1]
    orr r0,r0,r2
    str r0,[r1]            //���Ƽ�״̬�Ĵ�����ֵ
    pop {r0,r1,r2,pc}
