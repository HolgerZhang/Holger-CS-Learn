namespace Exp05_advanced_C_Sharp
{
	partial class FrmMain
	{
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows 窗体设计器生成的代码

		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.dev_list = new System.Windows.Forms.ComboBox();
			this.dev_stat = new System.Windows.Forms.Label();
			this.connect_button = new System.Windows.Forms.Button();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.label3 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.sys_time_text = new System.Windows.Forms.TextBox();
			this.mcu_time_text = new System.Windows.Forms.TextBox();
			this.send_button = new System.Windows.Forms.Button();
			this.program_info_text = new System.Windows.Forms.TextBox();
			this.timer_sys_time = new System.Windows.Forms.Timer(this.components);
			this.SCIPort = new System.IO.Ports.SerialPort(this.components);
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.dev_list);
			this.groupBox1.Controls.Add(this.dev_stat);
			this.groupBox1.Controls.Add(this.connect_button);
			this.groupBox1.Location = new System.Drawing.Point(2, 3);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(298, 82);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "串口连接";
			// 
			// dev_list
			// 
			this.dev_list.FormattingEnabled = true;
			this.dev_list.Location = new System.Drawing.Point(10, 56);
			this.dev_list.Name = "dev_list";
			this.dev_list.Size = new System.Drawing.Size(82, 20);
			this.dev_list.TabIndex = 3;
			this.dev_list.Click += new System.EventHandler(this.dev_list_Click);
			// 
			// dev_stat
			// 
			this.dev_stat.AutoSize = true;
			this.dev_stat.Location = new System.Drawing.Point(111, 38);
			this.dev_stat.Name = "dev_stat";
			this.dev_stat.Size = new System.Drawing.Size(77, 12);
			this.dev_stat.TabIndex = 2;
			this.dev_stat.Text = "请先打开串口";
			// 
			// connect_button
			// 
			this.connect_button.Location = new System.Drawing.Point(10, 19);
			this.connect_button.Name = "connect_button";
			this.connect_button.Size = new System.Drawing.Size(82, 31);
			this.connect_button.TabIndex = 0;
			this.connect_button.Text = "打开串口";
			this.connect_button.UseVisualStyleBackColor = true;
			this.connect_button.Click += new System.EventHandler(this.connect_button_Click);
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.label3);
			this.groupBox2.Controls.Add(this.label2);
			this.groupBox2.Controls.Add(this.sys_time_text);
			this.groupBox2.Controls.Add(this.mcu_time_text);
			this.groupBox2.Controls.Add(this.send_button);
			this.groupBox2.Location = new System.Drawing.Point(2, 91);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(298, 206);
			this.groupBox2.TabIndex = 1;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "时间设置";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(58, 105);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(65, 12);
			this.label3.TabIndex = 4;
			this.label3.Text = "系统时间：";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(64, 63);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(59, 12);
			this.label2.TabIndex = 3;
			this.label2.Text = "MCU时间：";
			// 
			// sys_time_text
			// 
			this.sys_time_text.Location = new System.Drawing.Point(149, 102);
			this.sys_time_text.Name = "sys_time_text";
			this.sys_time_text.ReadOnly = true;
			this.sys_time_text.Size = new System.Drawing.Size(100, 21);
			this.sys_time_text.TabIndex = 2;
			this.sys_time_text.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// mcu_time_text
			// 
			this.mcu_time_text.Location = new System.Drawing.Point(149, 60);
			this.mcu_time_text.Name = "mcu_time_text";
			this.mcu_time_text.ReadOnly = true;
			this.mcu_time_text.Size = new System.Drawing.Size(100, 21);
			this.mcu_time_text.TabIndex = 1;
			this.mcu_time_text.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// send_button
			// 
			this.send_button.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
			this.send_button.Enabled = false;
			this.send_button.Location = new System.Drawing.Point(113, 168);
			this.send_button.Name = "send_button";
			this.send_button.Size = new System.Drawing.Size(75, 23);
			this.send_button.TabIndex = 0;
			this.send_button.Text = "发送时间";
			this.send_button.UseVisualStyleBackColor = true;
			this.send_button.Click += new System.EventHandler(this.send_button_Click);
			// 
			// program_info_text
			// 
			this.program_info_text.BackColor = System.Drawing.SystemColors.MenuBar;
			this.program_info_text.ForeColor = System.Drawing.SystemColors.WindowFrame;
			this.program_info_text.Location = new System.Drawing.Point(2, 303);
			this.program_info_text.Name = "program_info_text";
			this.program_info_text.ReadOnly = true;
			this.program_info_text.Size = new System.Drawing.Size(298, 21);
			this.program_info_text.TabIndex = 2;
			// 
			// timer_sys_time
			// 
			this.timer_sys_time.Enabled = true;
			this.timer_sys_time.Interval = 1000;
			this.timer_sys_time.Tick += new System.EventHandler(this.timer_sys_time_Tick);
			// 
			// SCIPort
			// 
			this.SCIPort.BaudRate = 115200;
			this.SCIPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SCIPort_DataReceived);
			// 
			// FrmMain
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(302, 325);
			this.Controls.Add(this.program_info_text);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.MaximizeBox = false;
			this.Name = "FrmMain";
			this.ShowIcon = false;
			this.Text = "MCU时间设置工具 (张昊)";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FrmMain_FormClosing);
			this.Load += new System.EventHandler(this.FrmMain_Load);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label dev_stat;
		private System.Windows.Forms.Button connect_button;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox sys_time_text;
		private System.Windows.Forms.TextBox mcu_time_text;
		private System.Windows.Forms.Button send_button;
		private System.Windows.Forms.TextBox program_info_text;
		private System.Windows.Forms.Timer timer_sys_time;
		private System.Windows.Forms.ComboBox dev_list;
		private System.IO.Ports.SerialPort SCIPort;
	}
}

