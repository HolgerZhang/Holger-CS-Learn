package ch8;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Ligt extends JPanel {
	private static final long serialVersionUID = 1L;
	private boolean red;
	private boolean yellow;
	private boolean green;

	public Ligt() {
		red = false;
		yellow = false;
		green = false;
	}

	public void turnOnRed() {
		red = true;
		yellow = false;
		green = false;
		repaint();
	}

	public void turnOnYellow() {
		red = false;
		yellow = true;
		green = false;
		repaint();
	}

	public void turnOnGreen() {
		red = false;
		yellow = false;
		green = true;
		repaint();
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		if (red) {
			g.setColor(Color.RED);
			g.fillOval(10, 10, 20, 20);
			g.setColor(Color.BLACK);
			g.drawOval(10, 35, 20, 20);
			g.drawOval(10, 60, 20, 20);
			g.drawRect(5, 5, 30, 80);
		} else if (yellow) {
			g.setColor(Color.YELLOW);
			g.fillOval(10, 35, 20, 20);
			g.setColor(Color.BLACK);
			g.drawOval(10, 10, 20, 20);
			g.drawOval(10, 60, 20, 20);
			g.drawRect(5, 5, 30, 80);
		} else if (green) {
			g.setColor(Color.GREEN);
			g.fillOval(10, 60, 20, 20);
			g.setColor(Color.BLACK);
			g.drawOval(10, 35, 20, 20);
			g.drawOval(10, 10, 20, 20);
			g.drawRect(5, 5, 30, 80);
		} else {
			g.setColor(Color.BLACK);
			g.drawOval(10, 10, 20, 20);
			g.drawOval(10, 35, 20, 20);
			g.drawOval(10, 60, 20, 20);
			g.drawRect(5, 5, 30, 80);
		}
	}

	public Dimension getPreferredSize() {
		return new Dimension(40, 90);
	}
}

public class RadioButtonDemo extends JFrame implements ItemListener {
	private static final long serialVersionUID = 1L;

	private JRadioButton jrbRed, jrbYellow, jrbGreen;

	private ButtonGroup btg = new ButtonGroup();

	private Ligt Ligt;

	public RadioButtonDemo() {
		JPanel p1 = new JPanel();
		Ligt = new Ligt();
		p1.add(Ligt);

		JPanel p2 = new JPanel();
		jrbRed = new JRadioButton("��ɫ");
		jrbYellow = new JRadioButton("��ɫ");
		jrbGreen = new JRadioButton("��ɫ");
		p2.add(jrbRed);
		p2.add(jrbYellow);
		p2.add(jrbGreen);
		btg.add(jrbRed);
		btg.add(jrbYellow);
		btg.add(jrbGreen);

		this.getContentPane().add(p1, BorderLayout.CENTER);
		this.getContentPane().add(p2, BorderLayout.SOUTH);

		jrbRed.addItemListener(this);
		jrbYellow.addItemListener(this);
		jrbGreen.addItemListener(this);

		this.setSize(250, 180);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}

	public void itemStateChanged(ItemEvent e) {
		if (jrbRed.isSelected())
			Ligt.turnOnRed();
		else if (jrbYellow.isSelected())
			Ligt.turnOnYellow();
		else if (jrbGreen.isSelected())
			Ligt.turnOnGreen();
	}

	public static void main(String[] arg) {
		new RadioButtonDemo();
	}
}
