namespace SerialPort
{
    partial class FrmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.btnCheckPcNode = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.lbl_PC_Node_State = new System.Windows.Forms.Label();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.button8 = new System.Windows.Forms.Button();
			this.button7 = new System.Windows.Forms.Button();
			this.button6 = new System.Windows.Forms.Button();
			this.button5 = new System.Windows.Forms.Button();
			this.button4 = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.button1 = new System.Windows.Forms.Button();
			this.tb_statue = new System.Windows.Forms.TextBox();
			this.btnClear1 = new System.Windows.Forms.Button();
			this.Txt_recv2 = new System.Windows.Forms.TextBox();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.groupBox7 = new System.Windows.Forms.GroupBox();
			this.groupBox1.SuspendLayout();
			this.groupBox3.SuspendLayout();
			this.groupBox7.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnCheckPcNode
			// 
			this.btnCheckPcNode.Location = new System.Drawing.Point(385, 17);
			this.btnCheckPcNode.Name = "btnCheckPcNode";
			this.btnCheckPcNode.Size = new System.Drawing.Size(198, 36);
			this.btnCheckPcNode.TabIndex = 0;
			this.btnCheckPcNode.Text = "连接终端设备";
			this.btnCheckPcNode.UseVisualStyleBackColor = true;
			this.btnCheckPcNode.Click += new System.EventHandler(this.btnCheckPcNode_Click);
			// 
			// groupBox1
			// 
			this.groupBox1.BackColor = System.Drawing.SystemColors.MenuBar;
			this.groupBox1.Controls.Add(this.lbl_PC_Node_State);
			this.groupBox1.Controls.Add(this.btnCheckPcNode);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
			this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
			this.groupBox1.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.groupBox1.ForeColor = System.Drawing.SystemColors.MenuHighlight;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(587, 59);
			this.groupBox1.TabIndex = 20;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "终端节点状态";
			// 
			// lbl_PC_Node_State
			// 
			this.lbl_PC_Node_State.AutoSize = true;
			this.lbl_PC_Node_State.Font = new System.Drawing.Font("宋体", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.lbl_PC_Node_State.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.lbl_PC_Node_State.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
			this.lbl_PC_Node_State.Location = new System.Drawing.Point(24, 31);
			this.lbl_PC_Node_State.Name = "lbl_PC_Node_State";
			this.lbl_PC_Node_State.Size = new System.Drawing.Size(85, 13);
			this.lbl_PC_Node_State.TabIndex = 1;
			this.lbl_PC_Node_State.Text = "请先连接设备";
			// 
			// groupBox3
			// 
			this.groupBox3.Controls.Add(this.button8);
			this.groupBox3.Controls.Add(this.button7);
			this.groupBox3.Controls.Add(this.button6);
			this.groupBox3.Controls.Add(this.button5);
			this.groupBox3.Controls.Add(this.button4);
			this.groupBox3.Controls.Add(this.button3);
			this.groupBox3.Controls.Add(this.button2);
			this.groupBox3.Controls.Add(this.button1);
			this.groupBox3.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.groupBox3.ForeColor = System.Drawing.SystemColors.Highlight;
			this.groupBox3.Location = new System.Drawing.Point(3, 65);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(580, 73);
			this.groupBox3.TabIndex = 35;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "LED灯颜色控制面板";
			// 
			// button8
			// 
			this.button8.Enabled = false;
			this.button8.Font = new System.Drawing.Font("微软雅黑", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.button8.Location = new System.Drawing.Point(493, 21);
			this.button8.Name = "button8";
			this.button8.Size = new System.Drawing.Size(61, 44);
			this.button8.TabIndex = 35;
			this.button8.Text = "关闭LED";
			this.button8.UseVisualStyleBackColor = true;
			this.button8.Click += new System.EventHandler(this.button8_Click);
			// 
			// button7
			// 
			this.button7.Enabled = false;
			this.button7.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.button7.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
			this.button7.Location = new System.Drawing.Point(426, 21);
			this.button7.Name = "button7";
			this.button7.Size = new System.Drawing.Size(61, 44);
			this.button7.TabIndex = 35;
			this.button7.Text = "白色";
			this.button7.UseVisualStyleBackColor = true;
			this.button7.Click += new System.EventHandler(this.button7_Click);
			// 
			// button6
			// 
			this.button6.Enabled = false;
			this.button6.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.button6.ForeColor = System.Drawing.Color.DarkOrange;
			this.button6.Location = new System.Drawing.Point(359, 21);
			this.button6.Name = "button6";
			this.button6.Size = new System.Drawing.Size(61, 44);
			this.button6.TabIndex = 35;
			this.button6.Text = "黄色";
			this.button6.UseVisualStyleBackColor = true;
			this.button6.Click += new System.EventHandler(this.button6_Click);
			// 
			// button5
			// 
			this.button5.Enabled = false;
			this.button5.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.button5.ForeColor = System.Drawing.Color.DarkOrchid;
			this.button5.Location = new System.Drawing.Point(292, 21);
			this.button5.Name = "button5";
			this.button5.Size = new System.Drawing.Size(61, 44);
			this.button5.TabIndex = 35;
			this.button5.Text = "紫色";
			this.button5.UseVisualStyleBackColor = true;
			this.button5.Click += new System.EventHandler(this.button5_Click);
			// 
			// button4
			// 
			this.button4.Enabled = false;
			this.button4.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.button4.ForeColor = System.Drawing.Color.Turquoise;
			this.button4.Location = new System.Drawing.Point(225, 21);
			this.button4.Name = "button4";
			this.button4.Size = new System.Drawing.Size(61, 44);
			this.button4.TabIndex = 35;
			this.button4.Text = "青色";
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new System.EventHandler(this.button4_Click);
			// 
			// button3
			// 
			this.button3.Enabled = false;
			this.button3.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.button3.ForeColor = System.Drawing.Color.Green;
			this.button3.Location = new System.Drawing.Point(158, 21);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(61, 44);
			this.button3.TabIndex = 35;
			this.button3.Text = "绿色";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler(this.button3_Click);
			// 
			// button2
			// 
			this.button2.Enabled = false;
			this.button2.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.button2.ForeColor = System.Drawing.Color.Blue;
			this.button2.Location = new System.Drawing.Point(91, 21);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(61, 44);
			this.button2.TabIndex = 35;
			this.button2.Text = "蓝色";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// button1
			// 
			this.button1.Enabled = false;
			this.button1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.button1.ForeColor = System.Drawing.Color.Red;
			this.button1.Location = new System.Drawing.Point(24, 21);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(61, 44);
			this.button1.TabIndex = 35;
			this.button1.Text = "红色";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// tb_statue
			// 
			this.tb_statue.Location = new System.Drawing.Point(3, 247);
			this.tb_statue.Name = "tb_statue";
			this.tb_statue.Size = new System.Drawing.Size(580, 21);
			this.tb_statue.TabIndex = 26;
			// 
			// btnClear1
			// 
			this.btnClear1.Location = new System.Drawing.Point(515, 25);
			this.btnClear1.Name = "btnClear1";
			this.btnClear1.Size = new System.Drawing.Size(59, 66);
			this.btnClear1.TabIndex = 21;
			this.btnClear1.Text = "清空显示框";
			this.btnClear1.UseVisualStyleBackColor = true;
			this.btnClear1.Click += new System.EventHandler(this.btnClear1_Click);
			// 
			// Txt_recv2
			// 
			this.Txt_recv2.BackColor = System.Drawing.SystemColors.ButtonFace;
			this.Txt_recv2.Font = new System.Drawing.Font("宋体", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.Txt_recv2.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.Txt_recv2.Location = new System.Drawing.Point(12, 25);
			this.Txt_recv2.Multiline = true;
			this.Txt_recv2.Name = "Txt_recv2";
			this.Txt_recv2.ReadOnly = true;
			this.Txt_recv2.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.Txt_recv2.Size = new System.Drawing.Size(497, 66);
			this.Txt_recv2.TabIndex = 24;
			// 
			// textBox2
			// 
			this.textBox2.BackColor = System.Drawing.SystemColors.ActiveCaption;
			this.textBox2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.textBox2.ForeColor = System.Drawing.Color.AliceBlue;
			this.textBox2.Location = new System.Drawing.Point(-7, 198);
			this.textBox2.Multiline = true;
			this.textBox2.Name = "textBox2";
			this.textBox2.ReadOnly = true;
			this.textBox2.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.textBox2.Size = new System.Drawing.Size(591, 26);
			this.textBox2.TabIndex = 25;
			this.textBox2.Text = "KW01无线收发测试软件B1功能：\r\n\r\n单击按钮，自动搜寻找到KW01的PC_NODE，显示相关信息。";
			// 
			// groupBox7
			// 
			this.groupBox7.Controls.Add(this.textBox2);
			this.groupBox7.Controls.Add(this.Txt_recv2);
			this.groupBox7.Controls.Add(this.btnClear1);
			this.groupBox7.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.groupBox7.ForeColor = System.Drawing.SystemColors.Highlight;
			this.groupBox7.Location = new System.Drawing.Point(3, 144);
			this.groupBox7.Name = "groupBox7";
			this.groupBox7.Size = new System.Drawing.Size(580, 97);
			this.groupBox7.TabIndex = 27;
			this.groupBox7.TabStop = false;
			this.groupBox7.Text = "提示信息";
			// 
			// FrmMain
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
			this.ClientSize = new System.Drawing.Size(587, 272);
			this.Controls.Add(this.tb_statue);
			this.Controls.Add(this.groupBox7);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.groupBox3);
			this.Name = "FrmMain";
			this.ShowIcon = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "STM32L4-LED灯控制程序-20220621 (张昊)";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FrmMain_FormClosing);
			this.Load += new System.EventHandler(this.FrmMain_Load);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox3.ResumeLayout(false);
			this.groupBox7.ResumeLayout(false);
			this.groupBox7.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCheckPcNode;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lbl_PC_Node_State;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox tb_statue;
        private System.Windows.Forms.Button btnClear1;
        private System.Windows.Forms.TextBox Txt_recv2;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.GroupBox groupBox7;
		private System.Windows.Forms.Button button8;
		private System.Windows.Forms.Button button7;
		private System.Windows.Forms.Button button6;
		private System.Windows.Forms.Button button5;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button1;
	}
}

