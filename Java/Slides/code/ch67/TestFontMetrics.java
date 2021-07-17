package ch67;
import java.awt.*;
import javax.swing.*;

class MessagePanel extends JPanel{
	private String message="Welcom to Java GUI";	
	private int xCoordinate=20;
	private int yCoordinate=20;	
	private boolean centered;
	
	public MessagePanel(){
	}
	public MessagePanel(String mess){
		message=mess;
	}	
	public String getMessage(){
		return message;
	}
	public void setMessage(String mess){
		message=mess;
	}	
	public int getXCoordinate(){
		return xCoordinate;
	}
	public void setXCoordinate(int x){
		this.xCoordinate=x;
	}
	public int getYCoordinate(){
		return this.yCoordinate;
	}
	public void setYCoordinate(int y){
		this.yCoordinate=y;
	}
	public boolean isCentered(){
		return centered;
	}
	public void setCentered(boolean cen){
		this.centered=cen;
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		if (this.centered){
			FontMetrics fm=g.getFontMetrics();
			int w=fm.stringWidth(message);
			int h=fm.getAscent();
			this.xCoordinate=(this.getSize().width-w)/2;
			this.yCoordinate=(this.getSize().height-h)/2;
		}
		g.drawString(message,xCoordinate,yCoordinate);
	}
}

public class TestFontMetrics extends JFrame{
	
	private static final long serialVersionUID = 1L;

	public TestFontMetrics(){
		MessagePanel msgP=new MessagePanel("Welcom to Java GUI");
		msgP.setForeground(Color.RED);
		msgP.setFont(new Font("SansSerif",Font.BOLD+Font.ITALIC,20));
		msgP.setCentered(true);
		this.getContentPane().add(msgP);
		this.setSize(300,200);
		this.setTitle("Test FontMetrics");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}
	
	public static void main(String[] args){
		new TestFontMetrics();
	}
}
