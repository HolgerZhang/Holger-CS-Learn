package ch8;
import javax.swing.*;
import javax.swing.border.TitledBorder;

import java.awt.*;

public class InputTest extends JFrame{
	private static final long serialVersionUID = 1L;
	
	public InputTest(){
		JRadioButton jck1=new JRadioButton("Sports",true);
		JRadioButton jck2=new JRadioButton("Music");
		JRadioButton jck3=new JRadioButton("Reading");
		JPanel jpl=new JPanel();
		TitledBorder tbl=new TitledBorder("兴趣爱好");
		jpl.setBorder(tbl);
		jpl.add(jck1);
		jpl.add(jck2);
		jpl.add(jck3);
		//----------真实分组
		ButtonGroup btg=new ButtonGroup();
		btg.add(jck1);
		btg.add(jck2);
		btg.add(jck3);
		
		String[] name={"zhang","wang","li","zhao","zhang","wang","li","zhao"};
		JList lst=new JList(name);
		JScrollPane jsp=new JScrollPane(lst);
		//jsp.getViewport().setView(lst);
		//lst.addItem("张");
		Container con=this.getContentPane();
		con.add(jpl,BorderLayout.NORTH);
		con.add(jsp,BorderLayout.CENTER);
		this.setSize(400,200);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] arg){
		new InputTest();
	}
}
