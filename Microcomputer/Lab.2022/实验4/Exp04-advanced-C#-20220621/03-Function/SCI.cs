using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

///---------------------------------------------------------------------
/// <summary>                                                           
/// 类          :SCI:串口功能实现类                                     
/// 类   功   能:打开串口、关闭串口及串口的接收和发送功能               
/// 类中函数包含:                                                       
///             (1)SCIInit:串口初始化                                   
///             (2)SCISendData:发送数据                                 
///             (3)SCIReceiveData:接收数据                              
///             (4)SCIClose:关闭串口                                    
///             (5)SCIReceInt: 设置串口接收中断条件                   
/// 说        明:本模块与具体的窗体界面无关                             
/// </summary>                                                          
/// <remarks></remarks>                                                 
/// --------------------------------------------------------------------


namespace SerialPort
{

    public class SCI : System.IO.Ports.SerialPort
    {

        /// ----------------------------------------------------------------
        /// <summary>                                                       
        /// 功    能:构造当前类的对象，初始化串口成员变量
        /// 内部调用:无                                                     
        /// </summary>                                                      
        /// <param name="ComNum">串口号,字符串类型</param>                  
        /// <param name="Baud">波特率,整型</param>                          
            
        /// ----------------------------------------------------------------
        public SCI(string ComNum, Int32 Baud)
        {
            try{
                this.Close();               //保证初始化之前是关闭的
                this.PortName = ComNum;     //设置串口号
                this.BaudRate = Baud;       //设置波特率
                this.Parity = System.IO.Ports.Parity.None;//设置无奇偶校验
                this.DataBits = 8;          //设置8比特数据位
                this.StopBits = System.IO.Ports.StopBits.One;//设置1位停止位
                this.ReadBufferSize = 4096; //接收缓冲区大小(字节) 
                this.WriteBufferSize = 2048;//发送缓冲区大小(字节)
            }catch{
                Console.WriteLine("SCI对象创建失败");
            }
        }

        /// ----------------------------------------------------------------
        /// <summary>                                                       
        /// 功    能:打开串口
        /// 内部调用:无                                                     
        /// </summary>                                                      
        /// ----------------------------------------------------------------
        public bool SCIOpen()
        {
            try
            {
                this.Open();                //打开串口
            }
            catch
            {
                return false;
            }
            return true;
        }


        ///-----------------------------------------------------------------
        /// <summary>                                                      
        /// 功    能:关闭串口                                               
        /// 内部调用:无                                                     
        /// </summary>                                                      
        /// <returns>返回一个布尔值,当串口成功关闭后,返回true              
        ///          否则返回false</returns>                                
        ///-----------------------------------------------------------------
        public bool SCIClose()
        {
            try
            {
                this.DiscardInBuffer(); //丢弃接收缓冲区的数据
                this.DiscardOutBuffer();//丢弃发送缓冲区的数据
                this.Dispose();         //释放串行通信的所有资源
                this.Close();           //关闭串口
            }
            catch
            {
                //产生错误,返回false
                return false;
            }
            return true;
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 功    能:串口发送数据                                           
        /// 内部调用:无                                                     
        /// </summary>                                                      
        /// <param name="SendArray">存放要发送的数据,字节数组</param>      
        /// <returns>返回一个布尔值,当发送成功后,返回True;                 
        ///          否则返回False</returns>                                
        ///-----------------------------------------------------------------
        public bool SCISendData(ref byte[] SendArray)
        {
            if (!this.IsOpen)
            {
                return false;
            }
            try
            {
                this.Write(SendArray, 0, SendArray.Length);//通过串口发送出去
            }
            catch
            {
                return false;//产生错误,返回false
            }
            return true;
        }


        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 功    能:串口发送帧格式数据                                           
        /// 内部调用:无                                                     
        /// </summary>                                                      
        /// <param name="SendArray">存放要发送的数据,字节数组</param>      
        /// <returns>返回一个布尔值,当发送成功后,返回True;                 
        ///          否则返回False</returns>                                
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
                //帧头
                sendData[index++] = emuartFrameHead[0];
                sendData[index++] = emuartFrameHead[1];
                //数据长度
                sendData[index++] = (byte)(SendArray.Length >> 8);
                sendData[index++] = (byte)(SendArray.Length);
                //数据
                if (SendArray.Length > 0)
                    Array.Copy(SendArray, 0, sendData, index, SendArray.Length);
                index += SendArray.Length;
                //CRC校验
                UInt16 temp16 = emuart_crc16(SendArray, SendArray.Length);
                sendData[index++] = (byte)(temp16 >> 8);
                sendData[index++] = (byte)(temp16);
                //发送帧尾
                sendData[index++] = emuartFrameTail[0];
                sendData[index++] = emuartFrameTail[1];


                this.Write(sendData, 0, sendData.Length);//通过串口发送出去
            }
            catch
            {
                return false;//产生错误,返回false
            }
            return true;
        }














        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 功    能:收取串口接收缓冲区数据，放入数组。数组为传地址方式传参
        ///          数带入。             
        /// 函数调用:无                                                     
        /// </summary>                                                      
        /// <param name="ReceiveArray">存放接收数据数组,字节数组</param>    
        /// <returns>返回一个布尔值,当接收成功后,返回true                   
        ///          否则,返回false</returns>                               
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

            //一帧收完后统一转码处理，防止中文出现乱码
            while (lenPre < lenNow)
            {
                System.Threading.Thread.Sleep(Convert.ToInt32(Math.Ceiling(2.0*9*1000/(this.BaudRate)) ));
                lenPre = lenNow;
                lenNow = this.BytesToRead;//获取接收缓冲区中的字节数       
            }

            try
            {
                ReceiveArray = new byte[lenNow];
                this.Read(ReceiveArray, 0, lenNow);//从接收缓冲区中读取数据，将其放入ReceiveArray中,并清除缓冲区       
            }
            catch
            {
                return false;//产生错误,返回false
            }
            return true;//正确，返回true
        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 功    能:设置串口“DataReceived”事件（中断）的触发条件                                          
        /// 函数调用:无                                                     
        /// </summary>                                                     
        /// <param name="a">设置“DataReceived”事件的触发条件,整型</param>                 
        ///-----------------------------------------------------------------
        public void SCIReceInt(int a)
        {
            //设置串口接收中断条件
            this.ReceivedBytesThreshold = a;
        }

        /// ------------------------------------------------------------------------------
        /// <summary>
        /// （1）查询本机串口号函数:查询本机串口
        /// 形式参数：无
        /// </summary>
        /// <returns>串口号数组 </returns>
        /// ------------------------------------------------------------------------------
        public static string[] SCIGetPorts()
        {          
            return GetPortNames();
        }

        private byte[] emuartFrameHead = new byte[2] { 0xa5, 0x06 };
        private byte[] emuartFrameTail = new byte[2] { 0xb6, 0x07 };

        //=====================================================================
        //函数名称：emuart_crc16
        //功能概要：将数据进行16位的CRC校验，返回校验后的结果值
        //参数说明：ptr:需要校验的数据缓存区
        //                len:需要检验的数据长度
        //函数返回：计算得到的校验值
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