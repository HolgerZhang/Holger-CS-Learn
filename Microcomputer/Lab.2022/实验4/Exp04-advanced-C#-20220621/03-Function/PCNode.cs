using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SerialPort
{
    public partial class PCNode
    {
        /// ------------------------------------------------------------------------------
        /// <summary>                                                           
        /// 类          :Find_PC_Node:KW01寻找PC节点工具                                     
        /// 类   功   能:通过串口向PC节点发送握手包,确认连接              
        /// 类中函数包含:  
        ///             (1)shake:握手函数,通过串口向PC节点发握手信号,确认是否连接
        ///             (2)flashWrite:flash写函数
        /// </summary>                                              
        /// ------------------------------------------------------------------------------
        /// 
        //串口操作工具类
        private Uart uart1;

        public Uart PCNode_Uart1
        {
            get { return this.uart1; }
        }
        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 名    称:(0)Find_PC_Node:构造函数 
        /// 功    能: 创建KW01寻节点实例                                  
        /// 内部参数: uart1：  串口工具类
        /// </summary>                                                                     
        /// <param name="uart1">串口工具类</param>                                          
        /// <returns>true_串口初始化成功 false_初始化失败</returns>                  
        /// ------------------------------------------------------------------------------
        public PCNode()
        {
            uart1 = null;
        }


        /// ------------------------------------------------------------------------------
        /// <summary>  
        /// 功    能:寻找PCNode。                                  
        /// 形    参:无
        /// <returns>无</returns>                  
        /// -----------------------------------------------------------------------------
        public string findPCNode()
        {
            int i,j;
            string s1;
            int[] uartNoArray;   //
            System.IO.Ports.SerialPort uartport;
            //1.临时变量
      
            bool result = false;         //
            byte[] recvData = null;  ////串口接收返回的信息

            byte[] shakeframe = {(byte)'S',11,(byte)'T',0xa,0x0,
                                 (byte)'W',(byte)'h',(byte)'o',(byte)'a',(byte)'r',(byte)'e',
                                 (byte)'y',(byte)'o',(byte)'u',(byte)'?', 
                                 (byte)'E',(byte)'N'
                                 };

            //初始化内部调用函数临时变量
            s1 = string.Empty;    //初始化临时字符串（置空）

            //创建_port1对象
            uartport = new System.IO.Ports.SerialPort();
            //查询所有串口，串口数在uartNoArray[0]中

            uartNoArray = Uart.findCOM();
            //没有找到串口情况
            if (uartNoArray[0] == 0) return s1 = "没有找到USB串口";
           
            //有找到串口情况，遍历搜寻串口
            for (i = uartNoArray[0]; i >= 1; i--)
            {
                string comName = "COM" + uartNoArray[i].ToString();  //串口名称
                //
                uart1 = new Uart(uartport, comName, 9600); //初始化串口工具类
                // pcNode1 = new PCNode(uart1);            //初始化KW01操作工具类

                //PE和PC节点握手
                //s1 = shake(shakeframe);        //与PC节点握手

                //2.打开串口
                result = uart1.open();
                if (!result) continue;

                uart1.setReceInt(200);  //设置触发DataRecieved事件的字节数（目的是关闭该事件）

                result = uart1.sendData(shakeframe, shakeframe.Length); //发送握手数据

                if (!result) { uart1.close(); continue; }
                //
                System.Threading.Thread.Sleep(100);   //线程休眠0.1s
               
                recvData = uart1.recvData();          //接收数据 


                if (recvData == null || recvData.Length == 0 || recvData[0] != 'M') 
                   { uart1.close(); continue; }

                //将握手成功,数组转换成字符串,返回
                for (j = 3; j < recvData[1] + 2; j++) s1 += (char)recvData[j];

                s1 = comName + ":" + s1;
                break;
             }
             if (i==0) s1="有USB串口，但无PCNode";
             
             return s1;
        }

        
        /// ------------------------------------------------------------------------------
        /// <summary>  
        ///函数名: 
        ///函数执行状态：
        ///参数说明：
        ///             
        ///功能概要：
        /// </summary>   
        /// ------------------------------------------------------------------------------
        public byte[] PCNodeSendReturn(byte[] SendByteArray,int cnt,int time)
        {
            byte[] recvData=null;
            int i;
            
            try
            {
                for (i = 0; i < cnt; i++)
                {
                    uart1.setReceInt(200);   //测试串口接收中断使用
                    uart1.sendData(SendByteArray, SendByteArray.Length);  // 通过串口发送数据
                    System.Threading.Thread.Sleep(time);
                    recvData = uart1.recvData();                          // 通过串口接收数据
                   if (recvData.Length >= 1) break;
                }

            }
            catch
            {
                return recvData;  //产生错误,返回false
            }
            return recvData;    // 返回接收数据数据的首地址
        }


    }
}        
