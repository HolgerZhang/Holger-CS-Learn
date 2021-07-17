package ch8;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class PersonInfo extends JFrame 
	implements FocusListener,ActionListener{
	private static final long serialVersionUID = 1L;
	
	private JTextField jtfName;
	private JTextField jtfAge;
	private JRadioButton jrbMan;
	private JRadioButton jrbWoman;
	private JComboBox jcbDegree;
	private JTextArea jtaDescription;
	
	public PersonInfo(String t){
		super(t);
		this.setSize(300,400);
		int wd=this.getSize().width/8;
		
		Box b1=Box.createHorizontalBox();
		b1.add(Box.createHorizontalStrut(wd));
		b1.add(new JLabel("������"));
		jtfName=new JTextField(10);
		b1.add(jtfName);
		b1.add(Box.createHorizontalStrut(wd));
		
		Box b2=Box.createHorizontalBox();
		b2.add(Box.createHorizontalStrut(wd));
		b2.add(new JLabel("���䣺"));
		jtfAge=new JTextField(5);
		jtfAge.addFocusListener(this);
		b2.add(jtfAge);
		b2.add(Box.createHorizontalStrut(wd));
		
		Box b3=Box.createHorizontalBox();
		b3.add(Box.createHorizontalStrut(wd));
		b3.add(new JLabel("�Ա�"));
		jrbMan=new JRadioButton("��");
		jrbWoman=new JRadioButton("Ů");
		ButtonGroup bg=new ButtonGroup();
		bg.add(jrbMan);
		bg.add(jrbWoman);
		b3.add(jrbMan);
		b3.add(jrbWoman);
		b3.add(Box.createHorizontalStrut(this.getSize().width));
		
		Box b4=Box.createHorizontalBox();
		b4.add(Box.createHorizontalStrut(wd));
		b4.add(new JLabel("ѧ����"));
		String[] dg={"ר��","��ѧ����","˶ʿ","��ʿ","����"};
		jcbDegree=new JComboBox(dg);
		b4.add(jcbDegree);
		b4.add(Box.createHorizontalStrut(wd));
		
		jtaDescription=new JTextArea();
		JScrollPane p=new JScrollPane(jtaDescription);
		Box b5=Box.createHorizontalBox();
		b5.add(new JLabel("���˼���"));
		
		Box b=Box.createVerticalBox();
		b.add(Box.createVerticalStrut(10));
		b.add(b1);
		b.add(Box.createVerticalStrut(10));
		b.add(b2);
		b.add(Box.createVerticalStrut(10));
		b.add(b3);
		b.add(Box.createVerticalStrut(10));
		b.add(b4);
		b.add(Box.createVerticalStrut(10));
		b.add(b5);
		
		JPanel pl=new JPanel();
		JButton btnOk=new JButton("ȷ��");
		JButton btnCancel=new JButton("ȡ��");
		pl.add(btnOk);
		pl.add(btnCancel);
		btnCancel.addActionListener(this);
		btnOk.addActionListener(this);
		
		this.getContentPane().add(b,BorderLayout.NORTH);
		this.getContentPane().add(p,BorderLayout.CENTER);
		this.getContentPane().add(pl,BorderLayout.SOUTH);
		
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] arg){
		new PersonInfo("������Ϣ");
	}

	public void focusGained(FocusEvent e) {		
	}

	public void focusLost(FocusEvent e) {
		if (jtfAge.getText().trim().equals(""))
			return;
		//����������Ƿ���ȷ��
		try{
			int age=Integer.parseInt(jtfAge.getText().trim());
			if (age<=0||age>200)
				throw new Exception();
		}catch(Exception ex){
			JOptionPane.showMessageDialog(this,"�����������");
			jtfAge.setText("");
		}
	}

	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().trim().equals("ȷ��"))
		{
			boolean isOk=true;
			if (jtfName.getText().trim().equals(""))
				isOk=false;
			else if (jtfAge.getText().trim().equals(""))
				isOk=false;
			else if (!(jrbMan.isSelected()||jrbWoman.isSelected()))
				isOk=false;
			else if (jtaDescription.getText().trim().equals(""))
				isOk=false;
			if (isOk==false)
				JOptionPane.showMessageDialog(this,"ȱ������δ��д!");
		}
		else
		{
			jtfName.setText("");
			jtfAge.setText("");
			jrbMan.setSelected(false);
			jrbWoman.setSelected(false);
			jcbDegree.setSelectedIndex(0);
			jtaDescription.setText("");
		}
	}
}
