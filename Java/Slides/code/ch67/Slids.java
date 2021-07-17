package ch67;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class GPanel extends JPanel{
	private static final long serialVersionUID = 1L;
	private int r,g,b;
	public GPanel(){
		r=g=b=0;
	}
	public void setR(int tr){
		r=tr;
	}
	public void setG(int tg){
		g=tg;
	}
	public void setB(int tb){
		b=tb;
	}
	public void paintComponent(Graphics pg){
		super.paintComponent(pg);
		Color c=new Color(r,g,b);
		pg.setColor(c);
		int r=(int)(Math.min(this.getSize().width,this.getSize().height)*0.4);
		int x=this.getSize().width/2-r;
		int y=this.getSize().height/2-r;
		pg.fillOval(x, y, r*2, r*2);
	}
	public Dimension getPreferredSize(){
		return new Dimension(300,250);
	}
}
public class Slids extends JFrame implements AdjustmentListener{
	private static final long serialVersionUID = 1L;
	JScrollBar r,g,b;
	GPanel gp;
	
	public Slids(){
		JPanel jp=new JPanel();
		gp=new GPanel();
		jp.add(gp);
		
		JPanel jp1=new JPanel();
		jp1.setLayout(new GridLayout(3,1));
		
		r=new JScrollBar(JScrollBar.HORIZONTAL,0,10,0,255);
		g=new JScrollBar(JScrollBar.HORIZONTAL,0,10,0,255);
		b=new JScrollBar(JScrollBar.HORIZONTAL,0,10,0,255);
		
		jp1.add(r);
		jp1.add(g);
		jp1.add(b);
		
		this.getContentPane().add(jp,BorderLayout.CENTER);
		this.getContentPane().add(jp1,BorderLayout.SOUTH);
		
		r.addAdjustmentListener(this);
		g.addAdjustmentListener(this);
		b.addAdjustmentListener(this);
		
		this.setSize(300,400);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}
	
	public static void main(String[] args){
		new Slids();
	}

	public void adjustmentValueChanged(AdjustmentEvent e) {
		if (e.getSource()==r)
			gp.setR(r.getValue());
		else if (e.getSource()==g)
			gp.setG(g.getValue());
		else
			gp.setB(b.getValue());
		gp.repaint();
	}
}
