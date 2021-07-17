package ch9_10;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FilenameFilter;
import java.util.Date;

public class SearchPad extends JFrame {
	private static final long serialVersionUID = 1L;

	private JTextField searchKey;
	private JTextField searchSource;
	private JTextArea searchResult;
	private JButton btnSearch;

	public SearchPad(String title) {
		super(title);

		Box b1 = Box.createHorizontalBox();
		b1.add(Box.createHorizontalStrut(10));
		b1.add(new JLabel("查找信息："));
		searchKey = new JTextField();
		b1.add(searchKey);
		b1.add(Box.createHorizontalStrut(10));

		Box b2 = Box.createHorizontalBox();
		b2.add(Box.createHorizontalStrut(10));
		b2.add(new JLabel("查找位置："));
		searchSource = new JTextField();
		b2.add(searchSource);
		b2.add(Box.createHorizontalStrut(10));

		Box b = Box.createVerticalBox();
		b.add(Box.createVerticalStrut(10));
		b.add(b1);
		b.add(Box.createVerticalStrut(10));
		b.add(b2);
		b.add(Box.createVerticalStrut(10));

		searchResult = new JTextArea();
		JScrollPane jsp = new JScrollPane(searchResult);

		JPanel jp = new JPanel();
		btnSearch = new JButton("查找");
		jp.add(btnSearch);

		ActHandler act = new ActHandler();
		btnSearch.addActionListener(act);

		this.getContentPane().add(b, BorderLayout.NORTH);
		this.getContentPane().add(jsp, BorderLayout.CENTER);
		this.getContentPane().add(jp, BorderLayout.SOUTH);

		this.setSize(600, 450);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}

	public static void main(String[] args) {
		new SearchPad("检索");
	}

	class ActHandler implements ActionListener {
		private String getShow(File fd) {
			String strTmp = "";
			strTmp += fd.getName() + "\t";
			strTmp += fd.length() + "\t";
			strTmp += fd.getParent() + "\t";
			Date dt = new Date(fd.lastModified());
			strTmp += dt.toString() + "\n";
			return strTmp;
		}

		private void listDir(File dir) {
			if (dir.isFile()) {
				searchResult.append(getShow(dir));
				return;
			}
			CmpHandler hd = new CmpHandler(searchKey.getText().trim());
			File[] fd = dir.listFiles(hd);
			if (fd == null || fd.length < 1)
				return;
			for (int i = 0; i < fd.length; i++)
				listDir(fd[i]);
		}

		public void actionPerformed(ActionEvent e) {
			if (searchSource.getText().trim().isEmpty()) {
				JOptionPane.showMessageDialog(SearchPad.this, "请输入要检索的位置！");
				return;
			}
			if (searchKey.getText().trim().length() <= 0) {
				JOptionPane.showMessageDialog(SearchPad.this, "请输入要检索的关键字！");
				return;
			}
			
			File fd = new File(searchSource.getText().trim());
			if (!fd.exists() || fd.isFile()) {
				JOptionPane.showMessageDialog(SearchPad.this, "要检索的位置不正确！");
				return;
			}
			
			searchResult.setText("");
			listDir(fd);
		}
	}
}

class CmpHandler implements FilenameFilter {
	private String key;

	public CmpHandler(String k) {
		key = k;
	}

	public boolean accept(File dir, String name) {
		File fd = new File(dir, name);
		if (fd.isDirectory())
			return true;
		if (name.indexOf(key) != -1)
		//if (name.endsWith(key))
			return true;
		return false;
	}
}