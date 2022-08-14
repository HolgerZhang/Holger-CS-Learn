using cn.edu.suda.sumcu.iot;
using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace SerialPort
{
	public partial class FrmMain : Form
	{
		//1. 窗体类的临时变量区
		//private System.IO.Ports.SerialPort UARTport;   //声明系统工具-串口对象的变量声明
		//private Uart uart1;                          //声明一个自定义的Uart类型（串口操作）的变量
		//private PCNode pcNode1;                      //声明一个自定义的PCNode类型的变量
		private EMUART emuart = EMUART.getInstance();
		SCI sci;    //要调用SCI类中所定义的函数
		byte[] recvData = new byte[100];

		public struct shakeData
		{
			// SizeConst用来定义数组大小
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 25)]
			public byte[] uecomType;          //通信模组类型
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
			public byte[] mcuType;            //MCU类型
			public uint uStartAds;            //User程序起始地址
			public uint uCodeSize;            //User程序总代码大小
			public uint replaceNum;           //替换更新最大字节
			public uint reserveNum;           //保留更新最大字节（不等于0意味着有User程序）
		}
		[StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
		public struct newshakeData
		{
			// SizeConst用来定义数组大小
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 25)]
			public byte[] uecomType;          //通信模组类型
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
			public byte[] mcuType;            //MCU类型
			public uint uStartAds;            //User程序起始地址
			public uint uCodeSize;            //User程序总代码大小
			public uint replaceNum;           //替换更新最大字节
			public uint reserveNum;           //保留更新最大字节（不等于0意味着有User程序）
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
			public byte[] BIOSVersion;            //BIOS版本号
		}
		private newshakeData newshakedata;
		private shakeData shakedata;
		private string uecomType;   //通信模组类型
		private string mcuType;     //MCU类型

		//2. 构造函数（启动窗体最先执行程序）
		public FrmMain()
		{
			//系统生成的构造函数（初始化窗体的元素）
			InitializeComponent();
			//禁止检测跨线程调用异常(
			CheckForIllegalCrossThreadCalls = false;
		}

		private object bytesToStruct(byte[] bytes, Type type)
		{
			//（1）变量声明
			int size;
			object obj;
			IntPtr structPtr;

			size = Marshal.SizeOf(type);
			//（2）判断字节长度
			if (size > bytes.Length) return null;
			//（3）分配结构体内存空间
			structPtr = Marshal.AllocHGlobal(size);
			//（4）将byte数组拷贝到分配好的内存空间
			Marshal.Copy(bytes, 0, structPtr, size);
			//（5）将内存空间转换为目标结构体
			obj = Marshal.PtrToStructure(structPtr, type);
			//（6）释放内存空间
			Marshal.FreeHGlobal(structPtr);
			return obj;
		}



		//3. 加载窗体事件程序（在构造函数之后执行的程序）
		private void FrmMain_Load(object sender, EventArgs e)
		{
			//btnCheckPcNode_Click(sender, e);                       
		}

		//========================以下是本窗体的各个事件响应函数==========================

		//------------------------单击“检测PC节点”按钮----------------------------------
		private void btnCheckPcNode_Click(object sender, EventArgs e)
		{
			int ret;            //返回值
			string com = "";    //串口信息
			string sTemp = "";
			byte[] recv = null;//保存串口接收信息
			byte[] shake = { (byte)10, (byte)'s', (byte)'h', (byte)'a', (byte)'k', (byte)'e' }; //与终端握手帧数据

			byte[] userShake = { (byte)11, (byte)'a', (byte)'u', (byte)'a', (byte)'r', (byte)'t', (byte)'?' }; //与终端握手帧数据
																											   //byte[] send = { (byte)'S' };
			string[] SCIPorts;
			SCIPorts = SCI.SCIGetPorts();
			this.Refresh();                     //刷新显示  
			if (emuart._Uartport != null) emuart._Uartport.Close();
			Thread.Sleep(10);   //等待串口关闭
			emuart = EMUART.getInstance();    //每次“重新连接”重新实例化
			ret = emuart.findDevice(out com, 115200);  //寻找emuart设备
			this.lbl_PC_Node_State.Text = com;       //右上角显示区

			if (ret == 1) goto btn_uartcheck_Click_EXIT1;
			//（4.2）找到串口，没有找到UE，退出函数
			else if (ret == 2) goto btn_uartcheck_Click_EXIT2;
			emuart.bufferClear();   //清除接收数组缓冲区
			emuart.send(shake, out recv, 200, 3); //获得设备的信息在recv中
			if (recv == null) goto btn_uartcheck_Click_EXIT3;  //没有接收到设备返回消息

			if (recv.Length == Marshal.SizeOf(typeof(shakeData)))
			{
				//byte数组转结构体
				shakedata = (shakeData)bytesToStruct(recv, typeof(shakeData));
				//获取握手帧数据
				uecomType = Encoding.Default.GetString(shakedata.uecomType).Replace("\0", "");
				mcuType = Encoding.Default.GetString(shakedata.mcuType).Replace("\0", "");

				//设置设备信息                   
				sTemp = com + "：" + uecomType + " " + mcuType;  //设备信息
																//状态提示
				this.lbl_PC_Node_State.Text = sTemp;     //右上角显示区
				this.button1.Enabled = true;
				this.button2.Enabled = true;
				this.button3.Enabled = true;
				this.button4.Enabled = true;
				this.button5.Enabled = true;
				this.button6.Enabled = true;
				this.button7.Enabled = true;
				this.button8.Enabled = true;
			}
			else if (recv.Length == Marshal.SizeOf(typeof(newshakeData)))
			{
				//byte数组转结构体
				newshakedata = (newshakeData)bytesToStruct(recv, typeof(newshakeData));
				//获取握手帧数据
				uecomType = Encoding.Default.GetString(newshakedata.uecomType).Replace("\0", "");
				mcuType = Encoding.Default.GetString(newshakedata.mcuType).Replace("\0", "");
				//设置设备信息                   
				sTemp = com + "：" + uecomType + " " + mcuType;  //设备信息

				if (sci != null && sci.IsOpen)
					sci.Close();
				//发送全局变量_SendByteArray中的数据,并返回结果
				for (int i = 0; i < SCIPorts.Length; i++)
				{
					if (SCIPorts[i] == com) continue;

					sci = new SCI(SCIPorts[i], 115200);
					if (sci.SCIOpen())
					{
						//sci.SCISendData(ref send);           //发送与Uart_User串口握手的数据信息
						sci.SCISendFrameData(ref userShake);

						Thread.Sleep(500);
						if (sci.SCIReceiveData(ref recvData))
						{
							//MessageBox.Show(System.Text.Encoding.Default.GetString(recvData));

							if (recvData.Length == 0 || !System.Text.Encoding.Default.GetString(recvData).Contains("I am an uart"))
							{
								this.tb_statue.Text = "未找到终端设备";
								//this.lbl_PC_Node_State.Text = "未找到终端设备";

								//MessageBox.Show("检查UART_User(KL36:UART0)串口有无接好");

								this.button1.Enabled = false;
								this.button2.Enabled = false;
								this.button3.Enabled = false;
								this.button4.Enabled = false;
								this.button5.Enabled = false;
								this.button6.Enabled = false;
								this.button7.Enabled = false;
								this.button8.Enabled = false;
								sci.Close();
								continue;
							}
							if (System.Text.Encoding.Default.GetString(recvData).Contains("I am an uart"))   //记录UART_User串口的Com号
							{
								this.tb_statue.Text = "找到终端设备，LED状态：蓝色";
								//this.lbl_PC_Node_State.Text = "连接终端在" + PublicVar.g_SCIComNum;
								PublicVar.g_SCIComNum = SCIPorts[i];
								this.button1.Enabled = true;
								this.button2.Enabled = true;
								this.button3.Enabled = true;
								this.button4.Enabled = true;
								this.button5.Enabled = true;
								this.button6.Enabled = true;
								this.button7.Enabled = true;
								this.button8.Enabled = true;
								btnCheckPcNode.Text = "重新连接设备";
								break;                                                              //找到后UART_User串口后，跳出循环
							}
						}
					}
				}
				//状态提示
				this.lbl_PC_Node_State.Text = sTemp;     //右上角显示区
			}
			else goto btn_uartcheck_Click_EXIT3;  //接收到错误返回
												  //(5)退出区
												  //(5.1)退出函数
			btn_uartcheck_Click_EXIT:
			btnCheckPcNode.Enabled = true;
			return;

		//(5.2)不存在可用串口
		btn_uartcheck_Click_EXIT1:
			btnCheckPcNode.Text = "运行状态：当前不存在可用串口";  //右上角提示区
			this.button1.Enabled = false;
			this.button2.Enabled = false;
			this.button3.Enabled = false;
			this.button4.Enabled = false;
			this.button5.Enabled = false;
			this.button6.Enabled = false;
			this.button7.Enabled = false;
			this.button8.Enabled = false;
			goto btn_uartcheck_Click_EXIT;

		//(5.3)存在串口，但不存在emuar设备
		btn_uartcheck_Click_EXIT2:
			emuart.terminate(115200); //发送数据给终端设备，让终端设备清空其数据缓冲区
			btnCheckPcNode.Text = "重新连接";  //连接按键文本
			lbl_PC_Node_State.Text = "运行状态：已连接串口" + com + "但未找到设备";   //右上角提示区
			this.button1.Enabled = false;
			this.button2.Enabled = false;
			this.button3.Enabled = false;
			this.button4.Enabled = false;
			this.button5.Enabled = false;
			this.button6.Enabled = false;
			this.button7.Enabled = false;
			this.button8.Enabled = false; 
			goto btn_uartcheck_Click_EXIT;

		//(5.4)没有正确接收到设备返回消息
		btn_uartcheck_Click_EXIT3:
			emuart.terminate(115200); //发送数据给终端设备，让终端设备清空其数据缓冲区
			btnCheckPcNode.Text = "重新连接";   //连接按钮文本
			lbl_PC_Node_State.Text = "找到GEC在" + com + "但握手失败，请再次单击[重新连接]按钮";   //右上角提示区
			this.button1.Enabled = false;
			this.button2.Enabled = false;
			this.button3.Enabled = false;
			this.button4.Enabled = false;
			this.button5.Enabled = false;
			this.button6.Enabled = false;
			this.button7.Enabled = false;
			this.button8.Enabled = false;
			goto btn_uartcheck_Click_EXIT;
		}

		//--------------------------单击窗口关闭“X”按钮---------------------------------
		private void FrmMain_FormClosing(object sender, FormClosingEventArgs e)
		{
			if (sci != null && sci.IsOpen)
			{
				//如果串口未关闭，则关闭
				sci.Close();
			}
		}

		//发送数据
		private void sendData(byte cmd)
		{
			byte[] SendByteArray = new byte[1];          // 定义发送缓冲区
			try
			{
				SendByteArray[0] = cmd;
				sci.SCISendFrameData(ref SendByteArray);
				Thread.Sleep(800);
				if (sci.SCIReceiveData(ref recvData))
				{
					this.Txt_recv2.Text += Encoding.Default.GetString(recvData);
				}
			}
			catch
			{
				this.Txt_recv2.Text += "操作失败！\n";
			}
			this.Txt_recv2.SelectionStart = Txt_recv2.Text.Length;
			this.Txt_recv2.ScrollToCaret();
			this.Txt_recv2.Refresh();
		}

		//---------------------------单击“清空显示框”按钮-------------------------------
		private void btnClear1_Click(object sender, EventArgs e)
		{
			this.Txt_recv2.Text = "";
			this.Txt_recv2.Refresh();
		}

		//以下为按钮点击事件
		private void button1_Click(object sender, EventArgs e)
		{
			sendData(1);
			this.tb_statue.Text = "LED状态：" + "红色";
			this.tb_statue.Refresh();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			sendData(2);
			this.tb_statue.Text = "LED状态：" + "蓝色";
			this.tb_statue.Refresh();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			sendData(3);
			this.tb_statue.Text = "LED状态：" + "绿色";
			this.tb_statue.Refresh();
		}

		private void button4_Click(object sender, EventArgs e)
		{
			sendData(4);
			this.tb_statue.Text = "LED状态：" + "青色";
			this.tb_statue.Refresh();
		}

		private void button5_Click(object sender, EventArgs e)
		{
			sendData(5);
			this.tb_statue.Text = "LED状态：" + "紫色";
			this.tb_statue.Refresh();
		}

		private void button6_Click(object sender, EventArgs e)
		{
			sendData(6);
			this.tb_statue.Text = "LED状态：" + "黄色";
			this.tb_statue.Refresh();
		}

		private void button7_Click(object sender, EventArgs e)
		{
			sendData(7);
			this.tb_statue.Text = "LED状态：" + "白色";
			this.tb_statue.Refresh();
		}

		private void button8_Click(object sender, EventArgs e)
		{
			sendData(0);
			this.tb_statue.Text = "LED状态：" + "关闭";
			this.tb_statue.Refresh();
		}
	}
}
