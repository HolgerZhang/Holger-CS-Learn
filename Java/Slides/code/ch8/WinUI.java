package ch8;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class WinUI extends JFrame {

	private static final long serialVersionUID = 1L;

	private JButton btnRed, btnBlue, btnYellow;

	private JPanel plButton, plShowColor;

	public WinUI() {
		super("按钮事件演示");
		this.setSize(300, 200);
		this.setLocation(200, 200);

		plButton = new JPanel();
		plShowColor = new JPanel();
		Container con = this.getContentPane();
		con.add(plButton, BorderLayout.NORTH);
		con.add(plShowColor, BorderLayout.CENTER);
		btnRed = new JButton("红色");
		btnBlue = new JButton("蓝色");
		btnYellow = new JButton("黄色");
		plButton.add(btnRed);
		plButton.add(btnBlue);
		plButton.add(btnYellow);

		// 追加事件处理--匿名类(没有命名，直接实例化)
		btnRed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				plShowColor.setBackground(Color.RED);
			}
		});

		btnBlue.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				plShowColor.setBackground(Color.BLUE);
			}
		});

		btnYellow.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				plShowColor.setBackground(Color.YELLOW);
			}
		});
		
		//追加一个this能响应窗口关闭动作
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent arg0) {
				JOptionPane.showConfirmDialog(null,"是否关闭？");
				System.exit(0);
			}			
		});
		
		this.setVisible(true);
	}

	public static void main(String[] arg) {
		new WinUI();
	}
}
