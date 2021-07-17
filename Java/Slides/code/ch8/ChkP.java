package ch8;
import java.awt.*;
import java.awt.event.AdjustmentEvent;
import java.awt.event.AdjustmentListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.*;

class MPanel extends JPanel{
	private static final long serialVersionUID = 1L;
	
	private Color c;
	private int shape;
	
	public MPanel(){
		c=Color.BLACK;
		shape=1;
	}
	public void setColor(Color cl){
		c=cl;
	}
	public void setShape(int s){
		shape=s;
	}
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		int x,y,r;
		x=this.getWidth();
		y=this.getHeight();
		r=(int)(Math.min(x,y)*0.4);
		x=x/2-r;
		y=y/2-r;
		g.setColor(c);
		switch (shape){
		case 1:
			g.fillOval(x,y,2*r,2*r);
			break;
		case 2:
			g.fillRect(x,y,2*r,2*r);
			break;
		case 3:
			g.drawOval(x,y,2*r,2*r);
			break;
		case 4:
			g.drawRect(x,y,2*r,2*r);
		}
	}
}

public class ChkP extends JFrame 
		implements AdjustmentListener,ItemListener{
	private static final long serialVersionUID = 1L;

	//--------UI
	MPanel pl;
	JRadioButton[] shp;
	String[] lbl={"实心椭圆","实心矩形","空心椭圆","空心矩形"};
	ButtonGroup rgp;
	JScrollBar r,g,b;
	
	public ChkP(String title){
		super(title);
		pl=new MPanel();
		shp=new JRadioButton[4];
		rgp=new ButtonGroup();
		
		Box chk=Box.createHorizontalBox();
		chk.add(Box.createHorizontalStrut(5));
		for (int i=0;i<shp.length;i++){
			shp[i]=new JRadioButton(lbl[i]);
			rgp.add(shp[i]);
			shp[i].addItemListener(this);
			chk.add(shp[i]);
			chk.add(Box.createHorizontalStrut(5));
		}
		shp[0].setSelected(true);
		
		Box b1=Box.createHorizontalBox();
		b1.add(Box.createHorizontalStrut(5));
		b1.add(new JLabel("R:"));
		r=new JScrollBar(JScrollBar.HORIZONTAL,0,10,0,255);
		b1.add(r);
		b1.add(Box.createHorizontalStrut(5));
		
		Box b2=Box.createHorizontalBox();
		b2.add(Box.createHorizontalStrut(5));
		b2.add(new JLabel("G:"));
		g=new JScrollBar(JScrollBar.HORIZONTAL,0,10,0,255);
		b2.add(g);
		b2.add(Box.createHorizontalStrut(5));
		
		Box b3=Box.createHorizontalBox();
		b3.add(Box.createHorizontalStrut(5));
		b3.add(new JLabel("B:"));
		b=new JScrollBar(JScrollBar.HORIZONTAL,0,10,0,255);
		b3.add(b);
		b3.add(Box.createHorizontalStrut(5));
		
		Box bx=Box.createVerticalBox();
		bx.add(chk);
		bx.add(Box.createVerticalStrut(10));
		bx.add(b1);
		bx.add(Box.createVerticalStrut(10));
		bx.add(b2);
		bx.add(Box.createVerticalStrut(10));
		bx.add(b3);
		bx.add(Box.createVerticalStrut(10));
		
		Container con=this.getContentPane();
		con.add(pl,BorderLayout.CENTER);
		con.add(bx,BorderLayout.SOUTH);
		
		r.addAdjustmentListener(this);
		g.addAdjustmentListener(this);
		b.addAdjustmentListener(this);
		
		this.setSize(400,400);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}
	
	public static void main(String[] args) {
		new ChkP("绘图");
	}

	public void adjustmentValueChanged(AdjustmentEvent arg0) {
		int rr=r.getValue();
		int rg=g.getValue();
		int rb=b.getValue();
		Color c=new Color(rr,rg,rb);
		pl.setColor(c);
		pl.repaint();
	}

	public void itemStateChanged(ItemEvent arg0) {
		int i=0;
		while (i<shp.length){
			if (arg0.getSource()==shp[i]){
				pl.setShape(i+1);
				break;
			}
			i++;
		}
		pl.repaint();
	}
}
