package ch67;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class PlafPanel extends JPanel {
	private static final long serialVersionUID = 1L;

	void makeButton(String name, final String plafName) {
		JButton button = new JButton(name);
		this.add(button);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				try {
					UIManager.setLookAndFeel(plafName);
					SwingUtilities.updateComponentTreeUI(PlafPanel.this);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	public PlafPanel() {
		makeButton("Metal", "javax.swing.plaf.metal.MetalLookAndFeel");
		makeButton("Motif", "com.sun.java.swing.plaf.motif.MotifLookAndFeel");
		makeButton("Windows",
				"com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
	}
}

class PlafFrame extends JFrame {
	private static final long serialVersionUID = 1L;

	public static final int WIDTH = 300;
	public static final int HEIGHT = 200;

	public PlafFrame() {
		setTitle("PlafTest");
		setSize(WIDTH, HEIGHT);

		PlafPanel panel = new PlafPanel();
		Container contentPane = getContentPane();
		contentPane.add(panel);
	}
}

public class PlafTest {
	public static void main(String[] args) {
		PlafFrame frame = new PlafFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}
