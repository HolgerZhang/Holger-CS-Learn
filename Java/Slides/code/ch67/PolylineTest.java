package ch67;
import java.awt.*;
import javax.swing.*;

class PolyPanel extends JPanel{
	private static final long serialVersionUID = 1L;
	private int[] x;
	private int[] y;
	int count;
	int xPoint,yPoint;
	
	public PolyPanel(int len,int xp,int yp){
		count=2*len+1;
		xPoint=xp;
		yPoint=yp;
		x=new int[count];
		y=new int[count];
		for (int i=0;i<count;i++){
			x[i]=-len+i;
			y[i]=x[i]*x[i];
			x[i]+=xp;
			y[i]=yp-y[i];
			System.out.println(x[i]+","+y[i]);
		}
		
	}
	public void paintComponent(Graphics g){
		g.drawLine(0, yPoint, 300, yPoint);
		g.drawLine(xPoint,0,xPoint,200);
		g.drawPolyline(x,y,x.length);
	}
}

public class PolylineTest extends JFrame{
	private static final long serialVersionUID = 1L;
	public PolylineTest(){
		PolyPanel pl=new PolyPanel(20,150,100);
		this.getContentPane().add(pl);
		this.setSize(300,200);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}
	
	public static void main(String[] args){
		new PolylineTest();
	}
}
