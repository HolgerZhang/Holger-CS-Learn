package ch67;

import javax.swing.*;
import java.awt.*;
import javax.swing.border.*;

public class BorderDemo extends JFrame{
	
	private static final long serialVersionUID = 1L;

	public static JPanel getPanelWithBorder(Border b)
	{
		JPanel jp=new JPanel();
		jp.setLayout(new BorderLayout());
		String nm=b.getClass().toString();
		nm=nm.substring(nm.lastIndexOf('.')+1);
		//在JPanel中央添加一个JLabel，显式边框类型名
		jp.add(new JLabel(nm,JLabel.CENTER),BorderLayout.CENTER);
		jp.setBorder(b);
		return jp;
	}
	
	public BorderDemo(String title)
	{
		super(title);
		Container ct=this.getContentPane();
		ct.setLayout(new GridLayout(2,4));
		ct.add(getPanelWithBorder(new TitledBorder("Hi")));
		ct.add(getPanelWithBorder(new EtchedBorder()));
		ct.add(getPanelWithBorder(new LineBorder(Color.RED)));
		ct.add(getPanelWithBorder(new MatteBorder(5,5,30,30,Color.PINK)));
		ct.add(getPanelWithBorder(new BevelBorder(BevelBorder.RAISED)));
		ct.add(getPanelWithBorder(new SoftBevelBorder(BevelBorder.LOWERED)));
		ct.add(getPanelWithBorder(new CompoundBorder(new EtchedBorder(),new LineBorder(Color.BLUE))));
		
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
		setVisible(true);
	}
	
	public static void main(String[] args)
	{
		new BorderDemo("Hello");
	}
}
