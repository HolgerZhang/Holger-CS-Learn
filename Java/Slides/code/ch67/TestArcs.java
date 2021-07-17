package ch67;

import javax.swing.*;
import java.awt.*;
public class TestArcs extends JFrame{
	public TestArcs(){
		setTitle("ShowArcs");
		getContentPane().add(new ArcsPanel());
	}
	public static void main(String[] args){
		TestArcs fm=new TestArcs();
		fm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fm.setSize(200,300);
		fm.setVisible(true);
	}
}
class ArcsPanel extends JPanel{
	public void paintComponent(Graphics g)	{
		super.paintComponent(g);
		int xCenter=this.getSize().width/2;
		int yCenter=this.getSize().height/2;
		int radius=(int)(Math.min(getSize().width,getSize().height)*0.4);
		int x=xCenter-radius;
		int y=yCenter-radius;
		g.setColor(Color.BLACK);
		g.fillArc(x,y,2*radius,2*radius,0,30);
		g.fillArc(x,y,2*radius,2*radius,90,30);
		g.fillArc(x,y,2*radius,2*radius,180,30);
		g.fillArc(x,y,2*radius,2*radius,270,30);
	}
}