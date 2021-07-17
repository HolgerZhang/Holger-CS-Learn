package ch67;

import javax.swing.*;
import java.awt.*;
public class BoxLayoutFrame extends JFrame{	
	public BoxLayoutFrame()	{
		setTitle("BoxLayoutTest");
		setSize(200,200);
		
		JLabel lblName=new JLabel("Name:");
		JTextField jtfName=new JTextField(10);
		jtfName.setMaximumSize(jtfName.getPreferredSize());
		Box box1=Box.createHorizontalBox();
		box1.add(lblName);
		box1.add(Box.createHorizontalStrut(10));
		box1.add(jtfName);		
		JLabel lblPass=new JLabel("Password:");
		JTextField jtfPass=new JPasswordField(10);
		jtfPass.setMaximumSize(jtfPass.getPreferredSize());
		Box box2=Box.createHorizontalBox();
		box2.add(lblPass);
		box2.add(Box.createHorizontalStrut(10));
		box2.add(jtfPass);		
		JButton jbtOk=new JButton("OK");
		JButton jbtCancel=new JButton("Cancel");
		Box box3=Box.createHorizontalBox();
		box3.add(jbtOk);
		box3.add(Box.createHorizontalGlue());
		box3.add(jbtCancel);
		
		Box panelBox=Box.createVerticalBox();
		panelBox.add(box1);
		panelBox.add(Box.createVerticalStrut(10));
		panelBox.add(box2);
		panelBox.add(Box.createVerticalGlue());
		panelBox.add(box3);
		
		getContentPane().add(panelBox,BorderLayout.CENTER);		
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}
	
	public static void main(String[] args) {
		new BoxLayoutFrame();
	}
}
