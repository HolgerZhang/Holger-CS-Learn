using SerialPort;
using System;
using System.Text;
using System.Windows.Forms;

namespace Exp05_advanced_C_Sharp
{
	public partial class FrmMain : Form
	{
		//委托,将从串口接收到的数据显示到接收框里面
		delegate void handleinterfaceupdatedelegate(Object textbox,
													string text);

		static private int baud = 115200;

		SCI sci = new SCI();    //要调用SCI类中所定义的函数
		string[] SCIPorts;
		private bool listening = false;    //标识是否执行完invoke相关操作
		private bool closing = false;      //标识是否正在关闭串口

		public FrmMain()
		{
			InitializeComponent();
			//禁止检测跨线程调用异常
			CheckForIllegalCrossThreadCalls = false;
		}

		private void FrmMain_Load(object sender, EventArgs e)
		{
			connect_button.Text = "打开串口";
			dev_list.Enabled = true;
			GetSCIPorts();
		}

		/// <summary>
		/// 获取系统串口名并更新下拉列表
		/// </summary>
		private void GetSCIPorts()
		{
			SCIPorts = System.IO.Ports.SerialPort.GetPortNames();
			dev_list.Items.Clear();
			if (SCIPorts != null && SCIPorts.Length > 0)
			{
				for (int i = 0; i < SCIPorts.Length; i++)
				{
					dev_list.Items.Add(SCIPorts[i]);
				}
				dev_list.SelectedIndex = 0;
				connect_button.Enabled = true;
				dev_list.Enabled = true;
			}
			else
			{
				dev_list.Enabled = false;
				connect_button.Enabled = false;
				program_info_text.Text = "没有可用的串口,请检查!";
			}
		}

		/// <summary>
		/// 打开/关闭串口按钮点击事件，打开选择的串口
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void connect_button_Click(object sender, EventArgs e)
		{
			bool Flag;//标记打开是否成功
			string com = SCIPorts[dev_list.SelectedIndex];

			if (connect_button.Text == "打开串口")
			{
				//提示当前正在执行打开串口操作
				program_info_text.Text = "正在打开串口...";
				//进行串口的初始化,并用Flag返回结果
				Flag = sci.SCIInit(SCIPort, com, baud);

				if (Flag == true)//串口打开成功
				{
					connect_button.Text = "关闭串口";
					//[串口选择框]处于禁用状态
					dev_list.Enabled = false;
					send_button.Enabled = true;
					//状态上显示结果信息
					program_info_text.Text += "打开" + com + "成功!";
					dev_stat.Text = "当前串口：" + com;
				}
				else//串口打开失败
				{
					program_info_text.Text += "打开" + com + "失败!";
				}
			}
			else if (connect_button.Text == "关闭串口")
			{
				//提示当前操作
				program_info_text.Text = "正在关闭串口...";
				closing = true;     //正在关闭串口
				while (listening)
				{
					//使其能实时响应其他事件，避免系统出现假死现象
					//在接受数据操作时进行串口关闭操作，会因为假死现象对关闭串口事件没有反应
					//调用DoEvents能够使其即时响应关闭串口事件
					Application.DoEvents();
				}
				//执行关闭串口操作,并用Flag返回结果
				Flag = sci.SCIClose(SCIPort);
				if (Flag == true)
				{
					connect_button.Text = "打开串口";
					//[串口选择框]处于可用状态
					dev_list.Enabled = true;
					send_button.Enabled = false;
					program_info_text.Text += "关闭" + com + "成功!";
					dev_stat.Text = "请先打开串口";
					closing = false;    //关闭完成
				}
				else //串口关闭失败
				{
					program_info_text.Text += "关闭" + com + "失败!";
				}
			}
		}

		/// <summary>
		/// 发送时间按钮点击事件，向串口发送本机时间，格式为$$HH:mm:ss##
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void send_button_Click(object sender, EventArgs e)
		{
			if (!SCIPort.IsOpen)
			{
				//状态条进行提示
				program_info_text.Text += "请先打开串口!";
				return;
			}
			string sendString = DateTime.Now.ToString("$$HH:mm:ss##");
			program_info_text.Text = "发送: " + sendString;
			//将要发送的数据进行编码,并获取编码后的数据长度
			byte[] SendByteArray = Encoding.Default.GetBytes(sendString);
			bool Flag = sci.SCISendData(SCIPort, ref SendByteArray);
			if (Flag == true)
			{
				program_info_text.Text += " 成功!";
			}
			else
			{
				program_info_text.Text += " 失败!";
			}
		}

		/// <summary>
		/// 定时器Tick事件，用于定时更新GUI中的系统时间
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void timer_sys_time_Tick(object sender, EventArgs e)
		{
			DateTime dt = DateTime.Now;
			string time = dt.ToString("HH:mm:ss");
			sys_time_text.Text = time;
			sys_time_text.Refresh();
		}

		/// <summary>
		/// 串口收到数据事件，MCU每隔1s会将MCU时间通过串口发送给PC机。
		/// 格式为三个字节，分别表示小时、分钟、秒（均为数字）。
		/// PC机收到数据后，判断长度是否为3，并将其转换为形如HH:mm:ss的字符串显示在GUI对应位置。
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void SCIPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
		{
			//如果正在执行关闭操作
			if (closing)
			{
				return;
			}
			listening = true;
			byte[] recvData = new byte[1024];
			bool Flag = sci.SCIReceiveData(SCIPort, ref recvData);
			if (Flag == true)//串口接收数据成功
			{
				int len = recvData.Length;
				if (len == 3)
				{
					mcu_time_text.Clear();
					for (int i = 0; i < len; i++)
					{
						//异步更新TextBox
						SCIUpdateRevtxtbox(mcu_time_text, recvData[i].ToString("D2"));
						if (i < len - 1)
						{
							SCIUpdateRevtxtbox(mcu_time_text, ":");
						}
					}
				}
			}
			listening = false;  //接收数据结束
		}

		private void SCIUpdateRevtxtbox(Object textbox, string text)
		{
			//textbox显示文本与串口执行不在同一个线程中
			if (((TextBox)textbox).InvokeRequired)
			{
				handleinterfaceupdatedelegate InterFaceUpdate = new
					handleinterfaceupdatedelegate(SCIUpdateRevtxtbox);
				Invoke(InterFaceUpdate, new object[] { textbox, text });
			}
			else
			{
				((TextBox)textbox).Text += text;
				//把光标放在最后一行
				((TextBox)textbox).SelectionStart = ((TextBox)textbox).Text.Length;
				//将文本框中的内容调整到当前插入符号位置
				((TextBox)textbox).ScrollToCaret();
			}
		}

		private void FrmMain_FormClosing(object sender, FormClosingEventArgs e)
		{
			try
			{
				closing = true;     //正在关闭串口
				while (listening)
				{
					//使其能实时响应其他事件，避免系统出现假死现象
					Application.DoEvents();
				}
				sci.SCIClose(SCIPort);
				closing = false;    //关闭完成
			}
			catch
			{ }
		}

		private void dev_list_Click(object sender, EventArgs e)
		{
			GetSCIPorts();
		}
	}
}
