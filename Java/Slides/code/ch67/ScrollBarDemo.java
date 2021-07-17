package ch67;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class MessPanel extends JPanel{
	private static final long serialVersionUID = 1L;
	private int x=20,y=20;
	
	public void setX(int xi){
		x=xi;
	}
	public void setY(int yi){
		y=yi;
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		String str="欢迎进入J2EE平台！";
		Font font=new Font("宋体",Font.BOLD,40);
		g.setFont(font);
		g.drawString(str, x, y);
	}
	
	public Dimension getPreferredSize(){
		return new Dimension(200,100);
	}
	
	public Dimension getMinimumSize(){
		return new Dimension(200,100);
	}
}

public class ScrollBarDemo extends JFrame implements AdjustmentListener{
	private static final long serialVersionUID = 1L;
	JScrollBar jscbHort,jscbVert;
	MessPanel pl;
	
	public ScrollBarDemo(){
		jscbVert=new JScrollBar(Adjustable.VERTICAL);
		jscbHort=new JScrollBar(Adjustable.HORIZONTAL);		
		pl=new MessPanel();
		Container c=this.getContentPane();
		c.add(pl,BorderLayout.CENTER);
		c.add(jscbVert,BorderLayout.EAST);
		c.add(jscbHort,BorderLayout.SOUTH);
		jscbHort.addAdjustmentListener(this);
		jscbVert.addAdjustmentListener(this);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(300,200);
		this.setVisible(true);
	}
	
	public void adjustmentValueChanged(AdjustmentEvent e) {
		if (e.getSource()==jscbHort){
			double value=jscbHort.getValue();
			double max=jscbHort.getMaximum();
			double newx=(value/max*pl.getSize().width);
			pl.setX((int)newx);
			pl.repaint();			
		}
		else if (e.getSource()==jscbVert){
			double value=jscbVert.getValue();
			double max=jscbVert.getMaximum();
			double newY=(value*pl.getSize().height/max);
			pl.setY((int)newY);
			pl.repaint();
		}		
	}
	
	public static void main(String[] arg){
		new ScrollBarDemo();
	}

}
