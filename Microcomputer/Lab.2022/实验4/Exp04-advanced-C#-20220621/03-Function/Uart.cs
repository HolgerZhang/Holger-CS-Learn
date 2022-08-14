using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SerialPort
{
    /// ==================================================================================
    /// <summary>                                                           
    /// �������:Uart:���ڹ�����                                     
    /// ��Ĺ���:�򿪴��ڡ��رմ��ڼ����ڵĽ��պͷ��͹���               
    /// �ӿں�������1��findCOM:��ѯ�������ں�
    ///           ��2��open:�򿪴���
    ///           ��3��sendData:��������                                 
    ///           ��4��recvData:��������                              
    ///           ��5��close:�رմ���                                    
    ///           ��6��setReceInt:���ô��ڽ����ж�����                     
    /// </summary>                                              
    /// ==================================================================================
    public partial class Uart
    {
        //ʵ����ϵͳ������
        private System.IO.Ports.SerialPort _Uartport;

        public bool IsOpen
        {
            get { return _Uartport.IsOpen; }
        }

        public System.IO.Ports.SerialPort port
        {
            get { return _Uartport; }
        }

        //����ӿ�---���캯��-------------------------------------------------------------

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// ��0�����캯��1:�������ڹ�����ʵ����                     
        /// ��ʽ����: port��ϵͳ����ʵ��
        ///           comName����������
        /// </summary>                                                                     
        /// <param name="port">ϵͳ�Ĵ�����</param>                  
        /// <param name="comName">��������,���磺"COM23"</param>                          
        /// <returns>��</returns>                  
        /// ------------------------------------------------------------------------------
        public Uart(System.IO.Ports.SerialPort port, string comName)
        {
            this._Uartport = port;
            init_set_para(comName, 9600);
        }

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// ��0�����캯��2:�������ڹ���ʵ����                                  
        /// ��ʽ����: port��ϵͳ����ʵ��
        ///           comName����������
        ///           baud��������
        /// </summary>                                                                     
        /// <param name="port">ϵͳ�Ĵ�����</param>                  
        /// <param name="comName">��������,���磺"COM23"</param>
        /// <param name="baud">������,���磺9600</param>  
        /// <returns>��</returns>                  
        /// -----------------------------------------------------------------------------
        public Uart(System.IO.Ports.SerialPort port, string comName, Int32 baud)
        {
            this._Uartport = port;
            init_set_para(comName, baud);
        }

        //����ӿ�---�ӿں���-------------------------------------------------------------

        /// ------------------------------------------------------------------------------
        /// <summary>
        /// ��1����ѯ�������ںź���:��ѯ�������ں�
        /// ��ʽ��������
        /// </summary>
        /// <returns>���ں����� [0]=��������;[1-9]=��Ӧ���ں�</returns>
        /// ------------------------------------------------------------------------------
        public static int[] findCOM()
        {
            int sciPortNumCount;           //��������
            int sciportNum = 0, m;
            int[] portNo = new int[10];   //���ں����� 

            //ͨ��WMI��ȡ����PC��USB���ϵĴ��ڣ�USB-COM���ڣ�
            string[] ss = PubUtil.MulGetHardwareInfo(PubUtil.HardwareEnum.
                          Win32_PnPEntity, "Name");
            sciPortNumCount = ss.Length;   //��ǰ�����ϵ�USB-COM���ڸ���
            portNo[0] = sciPortNumCount;   //�洢��portNo[0]��
            
            //��ȡ���ں� 
            for (int i = 0; i < sciPortNumCount; i++)
            {
                sciportNum = 0;
                m = 0;
                while (m < ss[i].Length)  //��ȡ��i�����ڵĴ��ں�
                {
                    while (ss[i][m] >= 48 && ss[i][m] <= 58)
                    {
                        sciportNum = sciportNum * 10 + ss[i][m] - '0';
                        m++;
                    }
                    m++;
                }
                portNo[i + 1] = sciportNum;  //���еĴ��ںŶ�������
            }
            return portNo;
        }
               
        ///-------------------------------------------------------------------------------
        /// <summary>
        /// ��2���򿪴��ں���:�򿪴���
        /// </summary>
        /// <returns>true_�򿪳ɹ�  false_��ʧ��</returns>
        /// ------------------------------------------------------------------------------
        public bool open()
        {
            try
            {
                if (!_Uartport.IsOpen)  _Uartport.Open();
            }
            catch
            {
                return false;
            }
            return true;
        }

        ///-------------------------------------------------------------------
        /// <summary>  
        /// ��3���������ݺ��� :���ڷ�������                                          
        /// </summary>                                                      
        /// <param name="sendArray">����Ҫ���͵�����,�ֽ�����</param>   
        /// <param name="sendArrayLen">����Ҫ�������ݵ��ֽ���</param>   
        /// <returns>true_���ͳɹ� false_����ʧ��</returns>                                
        ///-------------------------------------------------------------------
        public bool sendData(byte[] sendArray, int sendArrayLen)
        {
            try
            {
                if (!_Uartport.IsOpen)  open();                
                 _Uartport.Write(sendArray, 0, sendArrayLen);//ͨ�����ڷ��ͳ�ȥ
            }
            catch
            {
                return false;
            }
            return true;
        }

        ///-------------------------------------------------------------------------------
        /// <summary>  
        /// ��4���������ݺ��� :��ȡ���ڽ��ջ��������ݣ����뷵������(�����峤�����飩��                                              
        /// </summary>    
        /// <returns>���ؽ��յ�������</returns>                               
        ///-------------------------------------------------------------------------------
        public byte[] recvData()
        {
            byte[] tmp = new byte[1000];
            byte[] Data;
            int len = 0;
            try
            {
                while (_Uartport.BytesToRead > 0)
                    tmp[len++] = (byte)_Uartport.ReadByte();
                Data = new byte[len];
                for (int i = 0; i < len; i++)
                    Data[i] = tmp[i];
            }
            catch
            {
                return null;
            }
            return Data;
        }

        ///-------------------------------------------------------------------------------
        /// <summary> 
        /// ��5���رմ��ں���:�رմ���                                               
        /// </summary>   
        /// <returns>�رճɹ�,����true�����򷵻�false</returns>                                
        ///-------------------------------------------------------------------------------
        public bool close()
        {
            try
            {
                if (!_Uartport.IsOpen) return true;
                _Uartport.DiscardInBuffer();    //�������ջ�����������
                _Uartport.DiscardOutBuffer();   //�������ͻ�����������
                _Uartport.Dispose();            //�ͷŴ���ͨ�ŵ�������Դ
                _Uartport.Close();              //�رմ���
            }
            catch
            {
                return false;
            }
            return true;
        }

        ///-------------------------------------------------------------------------------
        /// <summary>  
        /// ��6�����ô��ڽ����ж���������:���ô��ڵġ�DataReceived���¼�(�ж�)�Ĵ����ֽ���                                          
        /// ��ʽ����: n�����������¼����ֽ�����1~1024��                                                     
        /// </summary> 
        /// <param name="n">�յ����ֽ���>=n,�򴥷�DataReceived�¼�</param>                 
        ///-------------------------------------------------------------------------------
        public void setReceInt(int n)
        {
            //���ô��ڽ����ж�����
            if (_Uartport.IsOpen) close();
            _Uartport.ReceivedBytesThreshold = n;
            //������ϣ���
            open();
        }

    //�ڲ�������Ŵ�����ͷ��--------------------------------------------------------------
        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// ���ڳ�ʼ������:��ʼ������,���򿪴���                                  
        /// �ڲ�����:���캯������   
        /// ��ʽ����: comName����������
        ///           baud��   ������
        /// </summary>                                                                     
        /// <param name="comName">��������,���磺"COM23"</param>
        /// <param name="baud">������,���磺9600</param>                           
        /// <returns>true_���ڳ�ʼ���ɹ� false_��ʼ��ʧ��</returns>                  
        /// ------------------------------------------------------------------------------
        private bool init_set_para(string comName, Int32 baud)
        {
            try
            {
                if (_Uartport.IsOpen) _Uartport.Close();         //����򿪣���رմ���

                _Uartport.PortName = comName;     //���ô��ں�
                _Uartport.BaudRate = baud;       //���ò�����
                _Uartport.Parity = System.IO.Ports.Parity.None;//��������żУ��
                _Uartport.DataBits = 8;          //����8��������λ
                _Uartport.StopBits = System.IO.Ports.StopBits.One;//����1λֹͣλ
                _Uartport.ReadBufferSize = 4096; //���ջ�������С(�ֽ�) 
                _Uartport.WriteBufferSize = 2048;//���ͻ�������С(�ֽ�)
                _Uartport.ReceivedBytesThreshold = 1;
            }
            catch
            {
                return false; //��������,����false
            }
            return true;
        }
    //�ڲ�������Ŵ�����β��--------------------------------------------------------------
    }

}