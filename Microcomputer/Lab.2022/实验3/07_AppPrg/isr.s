//======================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn)
//���¼�¼��2019-09-27 V1.0
//======================================================================
.include "include.inc"

//start ������������
.type  USART2_IRQHandler, function
.global USART2_IRQHandler
.type  cmp_string, function
.type  data_isempty, function
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
      push {r0-r7,lr}      //r0-r7,lr��ջ������r7��������ռ��ã�lr��Ϊ�����ж�ǰpc��ֵ��
      //uint_8 flag
	  sub sp,#4         //ͨ���ƶ�spָ���ȡ��ַ
	  mov r7,sp         //����ȡ���ĵ�ַ����r7
//�����ֽ�
      mov r1,r7         //r1=r7 ��Ϊ����һ���ֽڵĵ�ַ
      mov r0,#UARTA		//r0ָ�����ں�
      bl  uart_re1      //���ý���һ���ֽ��Ӻ��������յ��Ĵ浽r0
      ldr r1,=0x20003000  //���յ����ݲ��ֵĴ����ַgcRecvBuf
      bl  emuart_frame  //����֡��������,r0=���ݲ��ֳ���
      cmp r0,#0			//���ɹ�����֡��ʽ����תЭ�����
      bne UARTA_IRQHandler_success_revc
      //����ֱ���˳�
      bl UARTA_IRQHandler_finish    //break
UARTA_IRQHandler_success_revc:
      //����Э��: (byte)11, (byte)'a', (byte)'u', (byte)'a', (byte)'r', (byte)'t', (byte)'?'
      ldr r0,=0x20003000
      ldrb r0,[r0]		//��ȡ���ݲ��ֵ�һλ->r0
      cmp r0,#11		//�ж�����Э��
      bne UARTA_IRQHandler_next_r
      ldr r0,=handshake_check_str	//string1
      ldr r1,=0x20003000
      add r1,#1			//string2
      mov r2,#6			//�ַ�������
      bl cmp_string
      cmp r0,#0
      bne UARTA_IRQHandler_next_r	//��������Э��
      //����λ�����֣�ȷ��ͨ�Ź�ϵ
      mov r0,#UARTA
      ldr r1,=handshake_send_str
      bl  uart_send_string
      bl UARTA_IRQHandler_finish    //break
UARTA_IRQHandler_next_r:
      //���߼���ַ: "r"+������1B+ƫ����(2B)+���ֽ���1B
      ldr r0,=0x20003000
      ldrb r0,[r0]		//��ȡ���ݲ��ֵ�һλ->r0
      cmp r0,#'r'		//��ȡ�����߼���ַ��
      bne UARTA_IRQHandler_next_a
      //flash_read_logic(flash_ContentDetail,gcRecvBuf[1],(gcRecvBuf[2]<<8)|gcRecvBuf[3],gcRecvBuf[4]);
      ldr r0,=flash_ContentDetail
      ldr r1,=0x20003000
      add r1,#1
      ldrb r1,[r1]		//r1=gcRecvBuf[1]
      ldr r2,=0x20003000
      add r2,#2
      ldrb r2,[r2]
      lsl r2,r2,#8		//r2=gcRecvBuf[2]<<8
      ldr r3,=0x20003000
      add r3,#3
      ldrb r3,[r3]		//gcRecvBuf[3]
      orr r2,r2,r3		//r2=(gcRecvBuf[2]<<8)|gcRecvBuf[3]
      ldr r3,=0x20003000
      add r3,#4
      ldrb r3,[r3]		//r3=gcRecvBuf[4]
      bl flash_read_logic
      //�п�
      ldr r0,=flash_ContentDetail
      ldr r1,=0x20003000
      add r1,#4
      ldrb r1,[r1]		//r1=gcRecvBuf[4]
      bl data_isempty
      cmp r0,#0
      beq UARTA_IRQHandler_next_r_empty  //Ϊ����ת
      //��Ϊ�գ���������
      mov r0,#UARTA
      ldr r1,=0x20003000
      add r1,#4
      ldrb r1,[r1]		//r1=gcRecvBuf[4]
      ldr r2,=flash_ContentDetail
      bl uart_sendN
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_r_empty:
      //Ϊ�գ����Ϳ���Ϣ
      mov r0,#UARTA
      ldr r1,=flash_str1
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_a:
      //�������ַ: "a"+��ַ4B+���ֽ���1B
      ldr r0,=0x20003000
      ldrb r0,[r0]		//��ȡ���ݲ��ֵ�һλ->r0
      cmp r0,#'a'		//��ȡ���������ַ��
      bne UARTA_IRQHandler_next_w
      //flash_read_physical(flashRead,(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)|(gcRecvBuf[3]<<8)|gcRecvBuf[4],gcRecvBuf[5]);
      ldr r0,=flash_ContentDetail
      ldr r1,=0x20003000
      add r1,#1
      ldrb r1,[r1]
      lsl r1,r1,#24		//r1=gcRecvBuf[1]<<24
      ldr r2,=0x20003000
      add r2,#2	
      ldrb r2,[r2]
      lsl r2,r2,#16		//gcRecvBuf[2]<<16
      orr r1,r1,r2		//r1=(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)
      ldr r2,=0x20003000
      add r2,#3
      ldrb r2,[r2]
      lsl r2,r2,#8		//gcRecvBuf[3]<<8
      orr r1,r1,r2		//r1=(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)|(gcRecvBuf[3]<<8)
      ldr r2,=0x20003000
      add r2,#4
      ldrb r2,[r2]		//gcRecvBuf[4]
      orr r1,r1,r2		//r1=(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)|(gcRecvBuf[3]<<8)|gcRecvBuf[4]
      ldr r2,=0x20003000
      add r2,#5
      ldrb r2,[r2]		//r2=gcRecvBuf[5]
      bl flash_read_physical
      //�п�
      ldr r0,=flash_ContentDetail
      ldr r1,=0x20003000
      add r1,#5
      ldrb r1,[r1]		//r1=gcRecvBuf[5]
      bl data_isempty
      cmp r0,#0
      beq UARTA_IRQHandler_next_a_empty  //Ϊ����ת
      //��Ϊ�գ���������
      mov r0,#UARTA
      ldr r1,=0x20003000
      add r1,#5
      ldrb r1,[r1]		//r1=gcRecvBuf[5]
      ldr r2,=flash_ContentDetail
      bl uart_sendN
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_a_empty:
      //Ϊ�գ����Ϳ���Ϣ
      mov r0,#UARTA
      ldr r1,=flash_str1
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_w:
      //д��: "w"+������1B+ƫ����(2B)+д���ֽ���1B+д������nB
      ldr r0,=0x20003000
      ldrb r0,[r0]		//��ȡ���ݲ��ֵ�һλ->r0
      cmp r0,#'w'		//д��
      bne UARTA_IRQHandler_next_e
      //д��ǰ�Ȳ�����flash_erase(gcRecvBuf[1]);
      ldr r0,=0x20003000
      add r0,#1
      ldrb r0,[r0]		//r0=gcRecvBuf[1]
      bl flash_erase
      cmp r0,#0
      bne UARTA_IRQHandler_next_w_failed  //��Ϊ0,��תʧ��
      //flash_write(gcRecvBuf[1], (gcRecvBuf[2]<<8)|gcRecvBuf[3],gcRecvBuf[4],&gcRecvBuf[5]);
      ldr r0,=0x20003000
      add r0,#1
      ldrb r0,[r0]		//r0=gcRecvBuf[1]
      ldr r1,=0x20003000
      add r1,#2
      ldrb r1,[r1]
      lsl r1,r1,#8		//r1=gcRecvBuf[2]<<8
      ldr r2,=0x20003000
      add r2,#3
      ldrb r2,[r2]		//gcRecvBuf[3]
      orr r1,r1,r2		//r1=(gcRecvBuf[2]<<8)|gcRecvBuf[3]
      ldr r2,=0x20003000
      add r2,#4
      ldrb r2,[r2]		//r2=gcRecvBuf[4]
      ldr r3,=0x20003000
      add r3,#5			//r3=&gcRecvBuf[5]
      bl flash_write
      cmp r0,#0
      bne UARTA_IRQHandler_next_w_failed  //��Ϊ0,��תʧ��
      //Ϊ0��д��ɹ�
      mov r0,#UARTA
      ldr r1,=flash_str5
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_w_failed:
      //д��ʧ��
      mov r0,#UARTA
      ldr r1,=flash_str6
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
//      //TEST recv
//      mov r0,#UARTA
//      ldr r1,=0x20003000
//      add r1,#1
//      ldrb r1,[r1]		//r1=gcRecvBuf[1]
//      bl uart_send1
//      mov r0,#UARTA
//      ldr r1,=0x20003000
//      add r1,#2
//      ldrb r1,[r1]		//r1=gcRecvBuf[2]
//      bl uart_send1
//      mov r0,#UARTA
//      ldr r1,=0x20003000
//      add r1,#3
//      ldrb r1,[r1]		//gcRecvBuf[3]
//      bl uart_send1
//      mov r0,#UARTA
//      ldr r1,=0x20003000
//      add r1,#4
//      ldrb r1,[r1]		//r1=gcRecvBuf[4]
//      ldr r2,=0x20003000
//      add r2,#5			//r2=&gcRecvBuf[5]
//      bl uart_sendN
//      bl UARTA_IRQHandler_finish  //break
//      //TEST revc end
UARTA_IRQHandler_next_e:
      //����: "e"+������1B
      ldr r0,=0x20003000
      ldrb r0,[r0]		//��ȡ���ݲ��ֵ�һλ->r0
      cmp r0,#'e'		//����
      bne UARTA_IRQHandler_next_default
      //flash_erase(gcRecvBuf[1]);
      ldr r0,=0x20003000
      add r0,#1
      ldrb r0,[r0]		//r0=gcRecvBuf[1]
      bl flash_erase
      cmp r0,#0
      bne UARTA_IRQHandler_next_e_failed  //��Ϊ0,��תʧ��
      //Ϊ0�������ɹ�
      mov r0,#UARTA
      ldr r1,=flash_str3
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_e_failed:
      //����ʧ��
      mov r0,#UARTA
      ldr r1,=flash_str4
      bl uart_send_string
      bl UARTA_IRQHandler_finish  //break
UARTA_IRQHandler_next_default:  //default
      ldr r1,=unknown_info_str
      mov r0,#UARTA		//r0ָ�����ں�
      bl  uart_send_string
//������Σ����һָ��ֳ�
UARTA_IRQHandler_finish:
      cpsie   i         //��������ж�
      add r7,#4         //��ԭr7
      mov sp,r7         //��ԭsp
      pop {r0-r7,pc}       //r0-r7,pc��ջ����ԭr7��ֵ��pc��lr,�������ж�ǰ�������ִ��


//=========================�ڲ�����====================================
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
//�������ƣ�data_isempty
//����������r0-data��r1-����
//�������أ�0-empty��1-not
//�������ܣ���������data�����Ƿ�Ϊ��
//======================================================================
data_isempty:
	push {r1-r7,lr}
	mov r2,#0	//��������
	mov r3,#0	//0-empty��1-not
data_isempty_loop:
	cmp r2,r1	//��r2>=r1������ѭ��
	bge data_isempty_exit
	ldrb r4,[r0,r2] //r4=r0[r2]
	add r2,#1		//r2++
	cmp r4,#0xff  //����ȣ�����ѭ��
	beq data_isempty_loop
	//�����ȣ��������ݣ���Ϊ�գ�����ѭ��
	mov r3,#1
data_isempty_exit:
	mov r0,r3
	pop {r1-r7,pc}
	
