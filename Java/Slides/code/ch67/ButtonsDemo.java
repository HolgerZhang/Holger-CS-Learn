package ch67;
import java.awt.*;
import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.plaf.basic.*;

public class ButtonsDemo extends JFrame{
	
	private static final long serialVersionUID = 1L;
	private JButton jb=new JButton("JButton");
	private BasicArrowButton 
		up=new BasicArrowButton(BasicArrowButton.NORTH),
		down=new BasicArrowButton(BasicArrowButton.SOUTH),
		right=new BasicArrowButton(BasicArrowButton.EAST),
		left=new BasicArrowButton(BasicArrowButton.WEST);
	
	public ButtonsDemo(String title){
		super(title);
		Container ct=this.getContentPane();
		ct.setLayout(new FlowLayout());
		ct.add(jb);
		ct.add(new JToggleButton("JToggleButton"));
		ct.add(new JCheckBox("JCheckBox"));
		ct.add(new JRadioButton("JRadioButton"));
		JPanel jp=new JPanel();
		jp.setBorder(new TitledBorder("Directions"));
		jp.add(up);
		jp.add(down);
		jp.add(left);
		jp.add(right);
		ct.add(jp);
		pack();
		setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public static void main(String[] args)
	{
		new ButtonsDemo("Hello");
	}
}
