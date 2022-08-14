using System;

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

	public partial class SCI
	{
		/// ----------------------------------------------------------------
		/// <summary>                                                       
		/// 功    能:初始化串口,并打开串口                                  
		/// 内部调用:无                                                     
		/// </summary>                                                      
		/// <param name="Port">串口控件,串口类型</param>                    
		/// <param name="ComNum">串口号,字符串类型</param>                  
		/// <param name="Baud">波特率,整型</param>                          
		/// <returns>返回一个布尔值,当串口成功打开后,返回true               
		///          当串口打开异常时,返回false </returns>                  
		/// ----------------------------------------------------------------
		public bool SCIInit(System.IO.Ports.SerialPort Port,
							string ComNum, Int32 Baud)
		{
			try
			{
				Port.Close();               //保证初始化之前是关闭的
				Port.PortName = ComNum;     //设置串口号
				Port.BaudRate = Baud;       //设置波特率
				Port.Parity = System.IO.Ports.Parity.None;//设置无奇偶校验
				Port.DataBits = 8;          //设置8比特数据位
				Port.StopBits = System.IO.Ports.StopBits.One;//设置1位停止位
				Port.ReadBufferSize = 4096; //接收缓冲区大小(字节) 
				Port.WriteBufferSize = 2048;//发送缓冲区大小(字节)
				Port.Open();                //打开串口
			}
			catch
			{

				return false; //产生错误,返回false
			}
			return true;
		}

		///-----------------------------------------------------------------
		/// <summary>                                                       
		/// 功    能:串口发送数据                                           
		/// 内部调用:无                                                     
		/// </summary>                                                      
		/// <param name="Port">串口控件,串口类型</param>                   
		/// <param name="SendArray">存放要发送的数据,字节数组</param>      
		/// <returns>返回一个布尔值,当发送成功后,返回True;                 
		///          否则返回False</returns>                                
		///-----------------------------------------------------------------
		public bool SCISendData(System.IO.Ports.SerialPort Port,
									   ref byte[] SendArray)
		{
			try
			{
				Port.Write(SendArray, 0, SendArray.Length);//通过串口发送出去
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
		/// 功    能:收取串口接收缓冲区数据，放入数组。数组为传地址方式传参
		///          数带入。             
		/// 函数调用:无                                                     
		/// </summary>                                                      
		/// <param name="Port">串口控件,串口类型</param>                    
		/// <param name="ReceiveArray">存放接收数据数组,字节数组</param>    
		/// <returns>返回一个布尔值,当接收成功后,返回true                   
		///          否则,返回false</returns>                               
		///-----------------------------------------------------------------
		public bool SCIReceiveData(System.IO.Ports.SerialPort Port,
									ref byte[] ReceiveArray)
		{
			int lenPre, lenNow;
			lenPre = 0;
			lenNow = 1;

			//一帧收完后统一转码处理，防止中文出现乱码
			while (lenPre < lenNow)
			{
				//波特率代表每秒传送的字节数，（1000/Port.BaudRate）毫秒传输一位
				//一帧数据是8数据位加1停止位共9位，数据放入缓冲区再从缓冲区取出来，所以时间要乘以2保证有足够时间处理
				//将当前线程挂起，挂起时间为(2.0 * 9 * 1000 / (Port.BaudRate))毫秒
				System.Threading.Thread.Sleep(Convert.ToInt32(Math.Ceiling(2.0 * 9 * 1000 / (Port.BaudRate))));
				lenPre = lenNow;
				lenNow = Port.BytesToRead;//获取接收缓冲区中的字节数
			}
			try
			{
				ReceiveArray = new byte[lenNow];
				Port.Read(ReceiveArray, 0, lenNow);//从接收缓冲区中读取数据，将其放入ReceiveArray中,并清除缓冲区       
			}
			catch
			{
				return false;//产生错误,返回false
			}
			return true;//正确，返回true
		}

		///-----------------------------------------------------------------
		/// <summary>                                                      
		/// 功    能:关闭串口                                               
		/// 内部调用:无                                                     
		/// </summary>                                                      
		/// <param name="Port">串口控件,串口类型</param>                    
		/// <returns>返回一个布尔值,当串口成功关闭后,返回true              
		///          否则返回false</returns>                                
		///-----------------------------------------------------------------
		public bool SCIClose(System.IO.Ports.SerialPort Port)
		{
			try
			{
				Port.DiscardInBuffer(); //丢弃接收缓冲区的数据
				Port.DiscardOutBuffer();//丢弃发送缓冲区的数据
				Port.Dispose();         //释放串行通信的所有资源
				Port.Close();           //关闭串口
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
		/// 功    能:设置串口“DataReceived”事件（中断）的触发条件                                          
		/// 函数调用:无                                                     
		/// </summary>                                                     
		/// <param name="Port">串口控件,串口类型</param>                    
		/// <param name="a">设置“DataReceived”事件的触发条件,整型</param>                 
		///-----------------------------------------------------------------
		public void SCIReceInt(System.IO.Ports.SerialPort Port, int a)
		{
			//设置串口接收中断条件
			Port.ReceivedBytesThreshold = a;
		}
	}
}