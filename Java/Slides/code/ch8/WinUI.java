package ch8;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class WinUI extends JFrame {

	private static final long serialVersionUID = 1L;

	private JButton btnRed, btnBlue, btnYellow;

	private JPanel plButton, plShowColor;

	public WinUI() {
		super("��ť�¼���ʾ");
		this.setSize(300, 200);
		this.setLocation(200, 200);

		plButton = new JPanel();
		plShowColor = new JPanel();
		Container con = this.getContentPane();
		con.add(plButton, BorderLayout.NORTH);
		con.add(plShowColor, BorderLayout.CENTER);
		btnRed = new JButton("��ɫ");
		btnBlue = new JButton("��ɫ");
		btnYellow = new JButton("��ɫ");
		plButton.add(btnRed);
		plButton.add(btnBlue);
		plButton.add(btnYellow);

		// ׷���¼�����--������(û��������ֱ��ʵ����)
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
		
		//׷��һ��this����Ӧ���ڹرն���
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent arg0) {
				JOptionPane.showConfirmDialog(null,"�Ƿ�رգ�");
				System.exit(0);
			}			
		});
		
		this.setVisible(true);
	}

	public static void main(String[] arg) {
		new WinUI();
	}
}
