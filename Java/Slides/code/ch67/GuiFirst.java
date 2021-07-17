package ch67;

import java.awt.*;
import javax.swing.*;
public class GuiFirst{
	static String[] lbl={"7","8","9","+",
					"4","5","6","-",
					"1","2","3","*",
					"0",".","=","/"};
	public static void main(String[] arg){
		JFrame jf=new JFrame("ª∂”≠");
		
		jf.setSize(200,200);
		Dimension dm=Toolkit.getDefaultToolkit().getScreenSize();
		int x,y;
		x=(dm.width-jf.getWidth())/2;
		y=(dm.height-jf.getHeight())/2;
		jf.setLocation(x,y);
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);		
		JTextField jfl=new JTextField();
		JPanel jpl=new JPanel();
		Container con=jf.getContentPane();
		con.add(jfl,BorderLayout.NORTH);
		con.add(jpl,BorderLayout.CENTER);		
		//======================≤ºæ÷√Ê∞Â
		GridLayout gl=new GridLayout(4,4);
		jpl.setLayout(gl);
		JButton btn;
		for (int i=0;i<lbl.length;i++)
		{
			btn=new JButton(lbl[i]);
			jpl.add(btn,i);
		}
		//========================
		jf.setVisible(true);
	}
}
