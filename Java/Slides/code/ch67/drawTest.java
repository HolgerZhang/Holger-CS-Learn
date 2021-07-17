package ch67;
import javax.swing.*;
import java.awt.*;

class drawPanel extends JPanel{
	private static final long serialVersionUID = 1L;
	
	private int[] ratio;
	private Color[] c;
	
	public drawPanel(int[] r,Color[] cl){
		ratio=r;
		c=cl;
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		int xCenter=this.getSize().width/2;
		int yCenter=this.getSize().height/2;
		int radius=(int)(Math.min(getSize().width,getSize().height)*0.4);
		int x=xCenter-radius;
		int y=yCenter-radius;
		
		int begin=0;
		for (int i=0;i<ratio.length;i++)
		{
			g.setColor(c[i]);
			g.fillArc(x,y,2*radius,2*radius,begin,ratio[i]*360/100);
			begin+=ratio[i]*360/100;
		}
	}
}

public class drawTest extends JFrame{
	private static final long serialVersionUID = 1L;
	
	public drawTest(int[] r,Color[] c){
		drawPanel dp=new drawPanel(r,c);
		this.getContentPane().add(dp);
		this.setSize(300,300);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public static void main(String[] args){
		int[] ratio={20,10,70};
		Color[] c={Color.RED,Color.BLUE,Color.YELLOW};
		new drawTest(ratio,c);
	}
}
