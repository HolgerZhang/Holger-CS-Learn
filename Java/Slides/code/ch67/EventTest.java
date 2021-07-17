package ch67;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
class win extends WindowAdapter{
	public void windowClosing(WindowEvent e) {
		JOptionPane.showConfirmDialog(null,"是否真的要关闭？");
	}
}

public class EventTest extends JFrame{
	private static final long serialVersionUID = 1L;
	private JPanel cPanel;

	public EventTest(String title) {
		super(title);

		JPanel btnPanel = new JPanel();
		JButton btn1 = new JButton("红色");
		JButton btn2 = new JButton("黄色");
		JButton btn3 = new JButton("蓝色");
		btnPanel.add(btn1);
		btnPanel.add(btn2);
		btnPanel.add(btn3);
		win obj=new win();
		this.addWindowListener(obj);
		cPanel = new JPanel();

		// 加事件处理
		btn1.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				cPanel.setBackground(Color.RED);
			}			
		});
		
		btn2.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				cPanel.setBackground(Color.YELLOW);				
			}			
		});
		
		btn3.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				cPanel.setBackground(Color.BLUE);				
			}			
		});

		this.getContentPane().add(btnPanel, BorderLayout.NORTH);
		this.getContentPane().add(cPanel, BorderLayout.CENTER);

		this.setSize(300, 200);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	public static void main(String[] args) {
		new EventTest("事件演示");
	}
}
