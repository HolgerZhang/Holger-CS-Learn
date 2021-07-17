package ch67;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.io.*;

public class ImageViewer {
	public static void main(String[] args) {
		ImageViewerFrame fm = new ImageViewerFrame();
		fm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fm.setVisible(true);
	}
}

class ImageViewerFrame extends JFrame {
	private static final long serialVersionUID = 1L;

	private JFileChooser chooser;

	private JLabel lbl;

	private static final int DEFAULT_WIDTH = 300;
	private static final int DEFAULT_HEIGHT = 400;

	public ImageViewerFrame() {
		this.setTitle("Õº∆¨‰Ø¿¿");
		this.setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		chooser = new JFileChooser();
		chooser.setCurrentDirectory(new File("."));

		lbl = new JLabel();
		this.getContentPane().add(lbl, BorderLayout.CENTER);

		JMenuBar mbr = new JMenuBar();
		this.setJMenuBar(mbr);
		JMenu menu = new JMenu("File");
		mbr.add(menu);
		JMenuItem mitem = new JMenuItem("Open");
		menu.add(mitem);
		mitem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int result = chooser.showOpenDialog(null);
				if (result == JFileChooser.APPROVE_OPTION) {
					String name = chooser.getSelectedFile().getAbsolutePath();
					System.out.println(name);
					lbl.setIcon(new ImageIcon(name));
				}
			}
		});

		JMenuItem mexit = new JMenuItem("Exit");
		menu.add(mexit);
		mexit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
	}
}
