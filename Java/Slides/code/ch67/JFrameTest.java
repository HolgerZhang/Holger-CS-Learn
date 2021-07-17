package ch67;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class JFrameTest extends JFrame {
	private static final long serialVersionUID = 1L;
	private double d1,d2;
	private int tag;	//��¼��ǰ�����ǵڼ���
	private char op;
	
	private JTextField jtf;
	private String[] tits={"7","8","9","+","4","5","6","-","1","2","3","*",
			"0",".","=","/"};
	
	class opand implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			//�û��������������
			if (jtf.getText().trim().equals("")|| tag==-1)
			{
				tag=0;
				jtf.setText("");
				return;		//���¿�ʼ
			}
			if (tag==0)
			{
				//�����ı���������d1
				d1=Double.parseDouble(jtf.getText());
				tag++;
			}
			else
			{
				//�����ı���������d2
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
				//��д��ֵ
				if (tag==0)
					d1=Double.parseDouble(jtf.getText());
				else
					d2=Double.parseDouble(jtf.getText());
				dig=compute()+"";
				//Ϊ�Ժ����������׼��
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
				//�û���������ְ�ť��С����			
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
				JOptionPane.showMessageDialog(JFrameTest.this,"�������ֵ����");
				jtf.setText("");
			}
		}		
	}
	
	public JFrameTest()
	{
		super("������");
		JButton[] btns=new JButton[16];	
		tag=0;
		d1=d2=0;
		op='+';
		//���������˳���Ϊ16�����飬�������������ã�������������ݲ�û�д���
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
			btns[i]=new JButton(tits[i]);	//ʵ����һ����ť
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
