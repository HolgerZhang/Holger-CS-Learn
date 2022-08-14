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
    /// 类的名称:Uart:串口工具类                                     
    /// 类的功能:打开串口、关闭串口及串口的接收和发送功能               
    /// 接口函数：（1）findCOM:查询本机串口号
    ///           （2）open:打开串口
    ///           （3）sendData:发送数据                                 
    ///           （4）recvData:接收数据                              
    ///           （5）close:关闭串口                                    
    ///           （6）setReceInt:设置串口接收中断条件                     
    /// </summary>                                              
    /// ==================================================================================
    public partial class Uart
    {
        //实例化系统串口类
        private System.IO.Ports.SerialPort _Uartport;

        public bool IsOpen
        {
            get { return _Uartport.IsOpen; }
        }

        public System.IO.Ports.SerialPort port
        {
            get { return _Uartport; }
        }

        //对外接口---构造函数-------------------------------------------------------------

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// （0）构造函数1:创建串口工具类实例。                     
        /// 形式参数: port：系统串口实例
        ///           comName：串口名称
        /// </summary>                                                                     
        /// <param name="port">系统的串口类</param>                  
        /// <param name="comName">串口名称,例如："COM23"</param>                          
        /// <returns>无</returns>                  
        /// ------------------------------------------------------------------------------
        public Uart(System.IO.Ports.SerialPort port, string comName)
        {
            this._Uartport = port;
            init_set_para(comName, 9600);
        }

        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// （0）构造函数2:创建串口工具实例。                                  
        /// 形式参数: port：系统串口实例
        ///           comName：串口名称
        ///           baud：波特率
        /// </summary>                                                                     
        /// <param name="port">系统的串口类</param>                  
        /// <param name="comName">串口名称,例如："COM23"</param>
        /// <param name="baud">波特率,例如：9600</param>  
        /// <returns>无</returns>                  
        /// -----------------------------------------------------------------------------
        public Uart(System.IO.Ports.SerialPort port, string comName, Int32 baud)
        {
            this._Uartport = port;
            init_set_para(comName, baud);
        }

        //对外接口---接口函数-------------------------------------------------------------

        /// ------------------------------------------------------------------------------
        /// <summary>
        /// （1）查询本机串口号函数:查询本机串口号
        /// 形式参数：无
        /// </summary>
        /// <returns>串口号数组 [0]=串口数量;[1-9]=对应串口号</returns>
        /// ------------------------------------------------------------------------------
        public static int[] findCOM()
        {
            int sciPortNumCount;           //串口数量
            int sciportNum = 0, m;
            int[] portNo = new int[10];   //串口号数组 

            //通过WMI获取接在PC机USB口上的串口（USB-COM串口）
            string[] ss = PubUtil.MulGetHardwareInfo(PubUtil.HardwareEnum.
                          Win32_PnPEntity, "Name");
            sciPortNumCount = ss.Length;   //当前电脑上的USB-COM串口个数
            portNo[0] = sciPortNumCount;   //存储到portNo[0]中
            
            //提取串口号 
            for (int i = 0; i < sciPortNumCount; i++)
            {
                sciportNum = 0;
                m = 0;
                while (m < ss[i].Length)  //提取第i个串口的串口号
                {
                    while (ss[i][m] >= 48 && ss[i][m] <= 58)
                    {
                        sciportNum = sciportNum * 10 + ss[i][m] - '0';
                        m++;
                    }
                    m++;
                }
                portNo[i + 1] = sciportNum;  //所有的串口号都在这了
            }
            return portNo;
        }
               
        ///-------------------------------------------------------------------------------
        /// <summary>
        /// （2）打开串口函数:打开串口
        /// </summary>
        /// <returns>true_打开成功  false_打开失败</returns>
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
        /// （3）发送数据函数 :串口发送数据                                          
        /// </summary>                                                      
        /// <param name="sendArray">传入要发送的数据,字节数组</param>   
        /// <param name="sendArrayLen">传入要发送数据的字节数</param>   
        /// <returns>true_发送成功 false_发送失败</returns>                                
        ///-------------------------------------------------------------------
        public bool sendData(byte[] sendArray, int sendArrayLen)
        {
            try
            {
                if (!_Uartport.IsOpen)  open();                
                 _Uartport.Write(sendArray, 0, sendArrayLen);//通过串口发送出去
            }
            catch
            {
                return false;
            }
            return true;
        }

        ///-------------------------------------------------------------------------------
        /// <summary>  
        /// （4）接收数据函数 :收取串口接收缓冲区数据，放入返回数组(不定义长度数组）。                                              
        /// </summary>    
        /// <returns>返回接收到的数组</returns>                               
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
        /// （5）关闭串口函数:关闭串口                                               
        /// </summary>   
        /// <returns>关闭成功,返回true，否则返回false</returns>                                
        ///-------------------------------------------------------------------------------
        public bool close()
        {
            try
            {
                if (!_Uartport.IsOpen) return true;
                _Uartport.DiscardInBuffer();    //丢弃接收缓冲区的数据
                _Uartport.DiscardOutBuffer();   //丢弃发送缓冲区的数据
                _Uartport.Dispose();            //释放串行通信的所有资源
                _Uartport.Close();              //关闭串口
            }
            catch
            {
                return false;
            }
            return true;
        }

        ///-------------------------------------------------------------------------------
        /// <summary>  
        /// （6）设置串口接收中断条件函数:设置串口的“DataReceived”事件(中断)的触发字节数                                          
        /// 形式参数: n：触发接收事件的字节数（1~1024）                                                     
        /// </summary> 
        /// <param name="n">收到的字节数>=n,则触发DataReceived事件</param>                 
        ///-------------------------------------------------------------------------------
        public void setReceInt(int n)
        {
            //设置串口接收中断条件
            if (_Uartport.IsOpen) close();
            _Uartport.ReceivedBytesThreshold = n;
            //设置完毕，打开
            open();
        }

    //内部函数存放处（开头）--------------------------------------------------------------
        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 串口初始化函数:初始化串口,并打开串口                                  
        /// 内部调用:构造函数调用   
        /// 形式参数: comName：串口名称
        ///           baud：   波特率
        /// </summary>                                                                     
        /// <param name="comName">串口名称,例如："COM23"</param>
        /// <param name="baud">波特率,例如：9600</param>                           
        /// <returns>true_串口初始化成功 false_初始化失败</returns>                  
        /// ------------------------------------------------------------------------------
        private bool init_set_para(string comName, Int32 baud)
        {
            try
            {
                if (_Uartport.IsOpen) _Uartport.Close();         //如果打开，则关闭串口

                _Uartport.PortName = comName;     //设置串口号
                _Uartport.BaudRate = baud;       //设置波特率
                _Uartport.Parity = System.IO.Ports.Parity.None;//设置无奇偶校验
                _Uartport.DataBits = 8;          //设置8比特数据位
                _Uartport.StopBits = System.IO.Ports.StopBits.One;//设置1位停止位
                _Uartport.ReadBufferSize = 4096; //接收缓冲区大小(字节) 
                _Uartport.WriteBufferSize = 2048;//发送缓冲区大小(字节)
                _Uartport.ReceivedBytesThreshold = 1;
            }
            catch
            {
                return false; //产生错误,返回false
            }
            return true;
        }
    //内部函数存放处（结尾）--------------------------------------------------------------
    }

}