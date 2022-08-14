using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

///---------------------------------------------------------------------
/// <summary>                                                           
/// ��          :SCI:���ڹ���ʵ����                                     
/// ��   ��   ��:�򿪴��ڡ��رմ��ڼ����ڵĽ��պͷ��͹���               
/// ���к�������:                                                       
///             (1)SCIInit:���ڳ�ʼ��                                   
///             (2)SCISendData:��������                                 
///             (3)SCIReceiveData:��������                              
///             (4)SCIClose:�رմ���                                    
///             (5)SCIReceInt: ���ô��ڽ����ж�����                   
/// ˵        ��:��ģ�������Ĵ�������޹�                             
/// </summary>                                                          
/// <remarks></remarks>                                                 
/// --------------------------------------------------------------------


namespace SerialPort
{

    public class SCI : System.IO.Ports.SerialPort
    {

        /// ----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:���쵱ǰ��Ķ��󣬳�ʼ�����ڳ�Ա����
        /// �ڲ�����:��                                                     
        /// </summary>                                                      
        /// <param name="ComNum">���ں�,�ַ�������</param>                  
        /// <param name="Baud">������,����</param>                          
            
        /// ----------------------------------------------------------------
        public SCI(string ComNum, Int32 Baud)
        {
            try{
                this.Close();               //��֤��ʼ��֮ǰ�ǹرյ�
                this.PortName = ComNum;     //���ô��ں�
                this.BaudRate = Baud;       //���ò�����
                this.Parity = System.IO.Ports.Parity.None;//��������żУ��
                this.DataBits = 8;          //����8��������λ
                this.StopBits = System.IO.Ports.StopBits.One;//����1λֹͣλ
                this.ReadBufferSize = 4096; //���ջ�������С(�ֽ�) 
                this.WriteBufferSize = 2048;//���ͻ�������С(�ֽ�)
            }catch{
                Console.WriteLine("SCI���󴴽�ʧ��");
            }
        }

        /// ----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:�򿪴���
        /// �ڲ�����:��                                                     
        /// </summary>                                                      
        /// ----------------------------------------------------------------
        public bool SCIOpen()
        {
            try
            {
                this.Open();                //�򿪴���
            }
            catch
            {
                return false;
            }
            return true;
        }


        ///-----------------------------------------------------------------
        /// <summary>                                                      
        /// ��    ��:�رմ���                                               
        /// �ڲ�����:��                                                     
        /// </summary>                                                      
        /// <returns>����һ������ֵ,�����ڳɹ��رպ�,����true              
        ///          ���򷵻�false</returns>                                
        ///-----------------------------------------------------------------
        public bool SCIClose()
        {
            try
            {
                this.DiscardInBuffer(); //�������ջ�����������
                this.DiscardOutBuffer();//�������ͻ�����������
                this.Dispose();         //�ͷŴ���ͨ�ŵ�������Դ
                this.Close();           //�رմ���
            }
            catch
            {
                //��������,����false
                return false;
            }
            return true;
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:���ڷ�������                                           
        /// �ڲ�����:��                                                     
        /// </summary>                                                      
        /// <param name="SendArray">���Ҫ���͵�����,�ֽ�����</param>      
        /// <returns>����һ������ֵ,�����ͳɹ���,����True;                 
        ///          ���򷵻�False</returns>                                
        ///-----------------------------------------------------------------
        public bool SCISendData(ref byte[] SendArray)
        {
            if (!this.IsOpen)
            {
                return false;
            }
            try
            {
                this.Write(SendArray, 0, SendArray.Length);//ͨ�����ڷ��ͳ�ȥ
            }
            catch
            {
                return false;//��������,����false
            }
            return true;
        }


        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:���ڷ���֡��ʽ����                                           
        /// �ڲ�����:��                                                     
        /// </summary>                                                      
        /// <param name="SendArray">���Ҫ���͵�����,�ֽ�����</param>      
        /// <returns>����һ������ֵ,�����ͳɹ���,����True;                 
        ///          ���򷵻�False</returns>                                
        ///-----------------------------------------------------------------
        public bool SCISendFrameData(ref byte[] SendArray)
        {
            if (!this.IsOpen)
            {
                return false;
            }
            try
            {
                byte[] sendData = new byte[SendArray.Length + 8];
                int index = 0;
                //֡ͷ
                sendData[index++] = emuartFrameHead[0];
                sendData[index++] = emuartFrameHead[1];
                //���ݳ���
                sendData[index++] = (byte)(SendArray.Length >> 8);
                sendData[index++] = (byte)(SendArray.Length);
                //����
                if (SendArray.Length > 0)
                    Array.Copy(SendArray, 0, sendData, index, SendArray.Length);
                index += SendArray.Length;
                //CRCУ��
                UInt16 temp16 = emuart_crc16(SendArray, SendArray.Length);
                sendData[index++] = (byte)(temp16 >> 8);
                sendData[index++] = (byte)(temp16);
                //����֡β
                sendData[index++] = emuartFrameTail[0];
                sendData[index++] = emuartFrameTail[1];


                this.Write(sendData, 0, sendData.Length);//ͨ�����ڷ��ͳ�ȥ
            }
            catch
            {
                return false;//��������,����false
            }
            return true;
        }














        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:��ȡ���ڽ��ջ��������ݣ��������顣����Ϊ����ַ��ʽ����
        ///          �����롣             
        /// ��������:��                                                     
        /// </summary>                                                      
        /// <param name="ReceiveArray">��Ž�����������,�ֽ�����</param>    
        /// <returns>����һ������ֵ,�����ճɹ���,����true                   
        ///          ����,����false</returns>                               
        ///-----------------------------------------------------------------
        public bool SCIReceiveData(ref byte[] ReceiveArray)
        {
            int lenPre,lenNow;

            lenPre = 0;
            lenNow = 1;

            if (!this.IsOpen)
            {
                return false;
            }

            //һ֡�����ͳһת�봦����ֹ���ĳ�������
            while (lenPre < lenNow)
            {
                System.Threading.Thread.Sleep(Convert.ToInt32(Math.Ceiling(2.0*9*1000/(this.BaudRate)) ));
                lenPre = lenNow;
                lenNow = this.BytesToRead;//��ȡ���ջ������е��ֽ���       
            }

            try
            {
                ReceiveArray = new byte[lenNow];
                this.Read(ReceiveArray, 0, lenNow);//�ӽ��ջ������ж�ȡ���ݣ��������ReceiveArray��,�����������       
            }
            catch
            {
                return false;//��������,����false
            }
            return true;//��ȷ������true
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// ��    ��:���ô��ڡ�DataReceived���¼����жϣ��Ĵ�������                                          
        /// ��������:��                                                     
        /// </summary>                                                     
        /// <param name="a">���á�DataReceived���¼��Ĵ�������,����</param>                 
        ///-----------------------------------------------------------------
        public void SCIReceInt(int a)
        {
            //���ô��ڽ����ж�����
            this.ReceivedBytesThreshold = a;
        }

        /// ------------------------------------------------------------------------------
        /// <summary>
        /// ��1����ѯ�������ںź���:��ѯ��������
        /// ��ʽ��������
        /// </summary>
        /// <returns>���ں����� </returns>
        /// ------------------------------------------------------------------------------
        public static string[] SCIGetPorts()
        {          
            return GetPortNames();
        }

        private byte[] emuartFrameHead = new byte[2] { 0xa5, 0x06 };
        private byte[] emuartFrameTail = new byte[2] { 0xb6, 0x07 };

        //=====================================================================
        //�������ƣ�emuart_crc16
        //���ܸ�Ҫ�������ݽ���16λ��CRCУ�飬����У���Ľ��ֵ
        //����˵����ptr:��ҪУ������ݻ�����
        //                len:��Ҫ��������ݳ���
        //�������أ�����õ���У��ֵ
        //=====================================================================
        UInt16 emuart_crc16(byte[] ptr, int len)
        {
            UInt16 i, j, tmp, crc16;

            crc16 = 0xffff;
            for (i = 0; i < len; i++)
            {
                crc16 = (UInt16)(ptr[i] ^ crc16);
                for (j = 0; j < 8; j++)
                {
                    tmp = (UInt16)(crc16 & 0x0001);
                    crc16 = (UInt16)(crc16 >> 1);
                    if (tmp != 0)
                        crc16 = (UInt16)(crc16 ^ 0xa001);
                }
            }
            return crc16;
        }
    }
}