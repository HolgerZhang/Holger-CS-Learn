package ch67;

import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;

public class TabbedPaneDemo extends JFrame {
	
	private String[] colorName = { "red", "blue", "green", "black", "yellow",
			"pink", "white" };

	private Color[] colors = { Color.RED, Color.BLUE, Color.GREEN, Color.BLACK,
			Color.YELLOW, Color.PINK, Color.WHITE };

//	private JTabbedPane tabs=new JTabbedPane();
	private JTabbedPane tabs = new JTabbedPane(
			JTabbedPane.BOTTOM,
			JTabbedPane.WRAP_TAB_LAYOUT);

	private JTextField txt = new JTextField(20);

	public TabbedPaneDemo(String title) {
		super(title);
		for (int i = 0; i < colors.length; i++) {
			JPanel pnl = new JPanel();
			pnl.setBackground(colors[i]);
			JButton btn=new JButton(colorName[i]);
			pnl.add(btn);
			//---------
			tabs.addTab(colorName[i], pnl); 
			// 加入一个页面
		}
		tabs.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent e) {
				txt.setText("Tab selected: " + tabs.getSelectedIndex());
			}
		});
		Container cnt = this.getContentPane();
		cnt.add(txt, BorderLayout.SOUTH);
		cnt.add(tabs, BorderLayout.CENTER);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
		setVisible(true);
	}

	public static void main(String[] args) {
		new TabbedPaneDemo("Hello");
	}
}
