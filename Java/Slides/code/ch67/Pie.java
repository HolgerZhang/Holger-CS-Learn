package ch67;

/*编写程序，使用圆饼图显示作业、平时测验、期中考试和期末考试占总成绩的百分比。
 假设作业占20%，用红色显示；测验10%，用绿色显示；期中占30％，用蓝色表示；期末占40％，用橙色显示。*/
import java.awt.*;
import javax.swing.*;
class PiePanel extends JPanel{
	private int project,quiz,midterm,fina;	
	public PiePanel(int p,int q,int m,int f){
		project=p;
		quiz=q;
		midterm=m;
		fina=f;
	}
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		int xCenter=this.getSize().width/2;
		int yCenter=this.getSize().height/2;
		int radius=(int)(Math.min(getSize().width,getSize().height)*0.4);
		int x=xCenter-radius;
		int y=yCenter-radius;
		g.setColor(Color.RED);		
		g.fillArc(x,y,2*radius,2*radius,0,project*360/100);
		g.setColor(Color.GREEN);
		g.fillArc(x,y,2*radius,2*radius,project*360/100,quiz*360/100);
		g.setColor(Color.BLUE);
		g.fillArc(x,y,2*radius,2*radius,(project+quiz)*360/100,midterm*360/100);
		g.setColor(Color.ORANGE);
		g.fillArc(x,y,2*radius,2*radius,(project+quiz+midterm)*360/100,fina*360/100);
	}
}
public class Pie extends JFrame{
	private static final long serialVersionUID = 1L;
	public Pie(String title,int p,int q,int m,int f){
		super(title);
		PiePanel pnl=new PiePanel(p,q,m,f);
		this.getContentPane().add(pnl);
		this.setSize(300,300);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}	
	public static void main(String[] args){
		new Pie("圆饼图",20,10,30,40);
	}
}
