package ch67;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class JFrameTest extends JFrame {
	private static final long serialVersionUID = 1L;
	private double d1,d2;
	private int tag;	//记录当前输入是第几个
	private char op;
	
	private JTextField jtf;
	private String[] tits={"7","8","9","+","4","5","6","-","1","2","3","*",
			"0",".","=","/"};
	
	class opand implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			//用户按下了运算符号
			if (jtf.getText().trim().equals("")|| tag==-1)
			{
				tag=0;
				jtf.setText("");
				return;		//重新开始
			}
			if (tag==0)
			{
				//现在文本框内容是d1
				d1=Double.parseDouble(jtf.getText());
				tag++;
			}
			else
			{
				//现在文本框内容是d2
				d2=Double.parseDouble(jtf.getText());
				d1=compute();
				d2=0;
			}
			jtf.setText("");
			op=e.getActionCommand().charAt(0);
		}
	}
	
	private double compute(){
		double dig;
		if (op=='+')
			dig=(d1+d2);
		else if (op=='-')
			dig=(d1-d2);
		else if (op=='*')
			dig=(d1*d2);
		else 
			dig=(d1/d2);
		return dig;
	}
	
	class digit implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			
			String dig=e.getActionCommand();
			if (dig.equals("="))
			{
				//填写数值
				if (tag==0)
					d1=Double.parseDouble(jtf.getText());
				else
					d2=Double.parseDouble(jtf.getText());
				dig=compute()+"";
				//为以后的运算做好准备
				tag=-1;
				d1=d2=0;
				op='+';
			}
			else
			{
				if (tag==-1)
				{
					jtf.setText("");
					tag=0;
				}				
				dig=jtf.getText().trim()+dig;
				//用户点击是数字按钮和小数点			
			}
			jtf.setText(dig);
		}		
	}
	
	class TxtValidate extends FocusAdapter{
		public void focusLost(FocusEvent e) {
			if (jtf.getText().trim().equals(""))
				return;
			try{
				Double.parseDouble(jtf.getText().trim());
			}catch(Exception ex){
				JOptionPane.showMessageDialog(JFrameTest.this,"输入的数值错误！");
				jtf.setText("");
			}
		}		
	}
	
	public JFrameTest()
	{
		super("计算器");
		JButton[] btns=new JButton[16];	
		tag=0;
		d1=d2=0;
		op='+';
		//创建生成了长度为16的数组，数组内容是引用，引用引向的内容并没有创建
		jtf=new JTextField();
		JPanel pal=new JPanel();
		
		Container con=this.getContentPane();
		con.add(jtf,BorderLayout.NORTH);
		con.add(pal,BorderLayout.CENTER);
		
		GridLayout gly=new GridLayout(4,4);
		pal.setLayout(gly);
		digit dig=new digit();
		opand opad=new opand();
		for (int i=0;i<btns.length;i++)
		{
			btns[i]=new JButton(tits[i]);	//实例化一个按钮
			pal.add(btns[i],i);
			if (i%4!=3)
				btns[i].addActionListener(dig);
			else
				btns[i].addActionListener(opad);
		}
		
		TxtValidate tv=new TxtValidate();
		jtf.addFocusListener(tv);
		this.setSize(200,200);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args)
	{
		new JFrameTest();
	}
}
