package ch8;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Light extends JPanel {
	private static final long serialVersionUID = 1L;
	private boolean red;
	private boolean yellow;
	private boolean green;

	public Light() {
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
		int px,py;
		px=this.getWidth()/2;
		py=this.getHeight()/2;
		if (red) {
			g.setColor(Color.RED);
			g.fillOval(px-10, py-35, 20, 20);
			g.setColor(Color.BLACK);
			g.drawOval(px-10, py-10, 20, 20);
			g.drawOval(px-10, py+15, 20, 20);
		} else if (yellow) {
			g.setColor(Color.YELLOW);
			g.fillOval(px-10, py-10, 20, 20);
			g.setColor(Color.BLACK);
			g.drawOval(px-10, py-35, 20, 20);
			g.drawOval(px-10, py+15, 20, 20);
		} else if (green) {
			g.setColor(Color.GREEN);
			g.fillOval(px-10, py+15, 20, 20);
			g.setColor(Color.BLACK);
			g.drawOval(px-10, py-10, 20, 20);
			g.drawOval(px-10, py-35, 20, 20);
		} else {
			g.setColor(Color.BLACK);
			g.drawOval(px-10, py-35, 20, 20);
			g.drawOval(px-10, py-10, 20, 20);
			g.drawOval(px-10, py+15, 20, 20);
		}
		g.drawRect(px-15, py-40, 30, 80);
	}
}

public class LightDemo extends JFrame implements ItemListener {
	private static final long serialVersionUID = 1L;

	private JRadioButton jrbRed, jrbYellow, jrbGreen;

	private ButtonGroup btg = new ButtonGroup();

	private Light light;

	public LightDemo() {
		super("交通路灯演示");
		light = new Light();

		JPanel p2 = new JPanel();
		jrbRed = new JRadioButton("红色");
		jrbYellow = new JRadioButton("黄色");
		jrbGreen = new JRadioButton("绿色");
		p2.add(jrbRed);
		p2.add(jrbYellow);
		p2.add(jrbGreen);
		btg.add(jrbRed);
		btg.add(jrbYellow);
		btg.add(jrbGreen);

		this.getContentPane().add(light, BorderLayout.CENTER);
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
			light.turnOnRed();
		else if (jrbYellow.isSelected())
			light.turnOnYellow();
		else if (jrbGreen.isSelected())
			light.turnOnGreen();
	}

	public static void main(String[] arg) {
		new LightDemo();
	}
}
