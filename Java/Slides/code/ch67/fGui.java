package ch67;

import javax.swing.*;
import java.awt.*;
public class fGui{
	public static void main(String[] args){
		JFrame fm=new JFrame("��ӭ");
		JButton btn1=new JButton("ȷ��");
		JButton btn2=new JButton("ȡ��");
		JButton btn3=new JButton("����");
		//==========Using of LayoutManager
		FlowLayout c=new FlowLayout();
		fm.setLayout(c);
		fm.getContentPane().add(btn1);
		fm.getContentPane().add(btn2);
		fm.getContentPane().add(btn3);
		//==================================
		fm.setSize(200,200);
		int x,y;
		Dimension dm=Toolkit.getDefaultToolkit().getScreenSize();
		y=(dm.height-fm.getHeight())/2;
		x=(dm.width-fm.getWidth())/2;
		fm.setLocation(x,y);
		fm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fm.setVisible(true);		
	}
}
