package ch67;

import java.awt.event.*;
import javax.swing.*;
import java.awt.*;

public class ActieventTest extends JFrame{
	
	private static final long serialVersionUID = 1L;
	private JButton btn1,btn2,btn3;
	private JPanel pnl;
	
	public ActieventTest()
	{
		JPanel p1=new JPanel();
		btn1=new JButton("ºì");
		btn2=new JButton("»Æ");
		btn3=new JButton("À¶");
		p1.add(btn1);
		p1.add(btn2);
		p1.add(btn3);
		this.getContentPane().add(p1,BorderLayout.NORTH);
		
		pnl=new JPanel();
		this.getContentPane().add(pnl,BorderLayout.CENTER);
		
		btn1.addActionListener(new ActionListener()
			{
				public void actionPerformed(ActionEvent e) {
					pnl.setBackground(Color.RED);
				}
			}
			);
		//btn2.addActionListener(this);
		//btn3.addActionListener(this);
		
		this.setTitle("ÊÂ¼þ²âÊÔ");
		this.setSize(200,200);
	}
	
	public static void main(String[] args)
	{
		ActieventTest act=new ActieventTest();
		act.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		act.setVisible(true);
	}
	
	
}


