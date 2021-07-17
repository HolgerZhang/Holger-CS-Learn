package ks1927405160;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.*;
import java.util.*;


import javax.swing.*;


public class FrmProduct extends JFrame {
	
	private JRadioButton pidBtn; // ��Ʒ���
	private JRadioButton numBtn; // ��Ʒ���
	private ButtonGroup select; // ��Ʒ��� or ��Ʒ���
	private JComboBox<String> typeBox; // ����
	private JTextArea jta;  // �ı���
	private JButton saveBtn;  // ����
	
	private ArrayList<Product> list, show;  // ����
	private File saveTo;

	public FrmProduct(File from, File to) {
		pidBtn = new JRadioButton("��Ʒ���");
		numBtn = new JRadioButton("��Ʒ���");
		select = new ButtonGroup();
		select.add(pidBtn);
		select.add(numBtn);
		typeBox = new JComboBox<>(Product.TYPES);
		jta = new JTextArea();
		saveBtn = new JButton("����");
		
		saveTo = to;		
		list = new ArrayList<>();
		show = new ArrayList<>();
		
		Container content = getContentPane();
		
		// ����
		Box topLine = Box.createHorizontalBox();
		topLine.add(Box.createHorizontalStrut(10));
		JLabel label1 = new JLabel("����ʽ:");
		topLine.add(label1);
		topLine.add(Box.createHorizontalStrut(10));
		topLine.add(pidBtn);
		topLine.add(Box.createHorizontalStrut(10));
		topLine.add(numBtn);
		topLine.add(Box.createHorizontalGlue());
		JLabel label2 = new JLabel("ѡ������:");
		topLine.add(label2);
		topLine.add(Box.createHorizontalStrut(10));
		topLine.add(typeBox);
		topLine.add(Box.createHorizontalStrut(10));
		content.add(topLine, BorderLayout.NORTH);
		
		// ��ʾ���������ı���
		JScrollPane jsp = new JScrollPane(jta);
		jsp.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		content.add(jsp, BorderLayout.CENTER);
		
		// ȷ�ϰ�ť
		Box buttomLine = Box.createHorizontalBox();
		buttomLine.add(Box.createHorizontalGlue());
		buttomLine.add(saveBtn);
		buttomLine.add(Box.createHorizontalGlue());
		content.add(buttomLine, BorderLayout.SOUTH);
		
		setSize(500, 400);
		setTitle("�鿴��Ʒ");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		loadData(from);  // ��������
		initListener();  // ��ʼ��������
		
		pidBtn.setSelected(true);
		typeBox.setSelectedIndex(0);
		
		// ��ʾ����
		sortShown();
		setToShow();
		
		setVisible(true);
	}

	// ��������
	private void loadData(File file) {
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));
			String aline = null;
			while (null != (aline = br.readLine())) {
				if (aline.trim().isEmpty()) {
					continue;
				}
				Product p = new Product(aline);
				list.add(p);
				show.add(p);
			}
			br.close();
		} catch(IOException e) {
			System.err.println(e.getMessage());
		}
	}

	// ��ʼ��������
	private void initListener() {
		ItemListener litener1 = new SortListener();
		pidBtn.addItemListener(litener1);
		numBtn.addItemListener(litener1);
		ItemListener listener2 = new FilterListener();
		typeBox.addItemListener(listener2);
		saveBtn.addActionListener(new ClickListener());
	}
	
	// ��ʾ
	private void setToShow() {
		StringBuilder str = new StringBuilder();
		for (Product p : show) {
			str.append(p.toString());
			str.append("\n");
		}
		jta.setText(str.toString());
	}
	
	// ��ʾ����
	private void sortShown() {
		if (pidBtn.isSelected()) {
			Collections.sort(show, new ProductIdComparator());// ����id����ıȽ���
		} else if (numBtn.isSelected()) {
			Collections.sort(show, new ProductNumberComparator());// ���տ������ıȽ���
		}
	}
	
	// ����ѡ�������
	class SortListener implements ItemListener {
		@Override
		public void itemStateChanged(ItemEvent e) {
			if (e.getSource() == pidBtn) {
				sortShown();
			} else if (e.getSource() == numBtn) {
				sortShown();
			}
			setToShow();
		}
	}
	
	// ���ͼ���
	class FilterListener implements ItemListener {
		@Override
		public void itemStateChanged(ItemEvent e) {
			String selected = (String) typeBox.getSelectedItem();
			show.clear();
			for (Product p : list) {
				if (selected.equals("ȫ��") || p.getType().equals(selected)) {
					show.add(p);
				}
			}
			sortShown();
			setToShow();			
		} 
	}
	
	// �������
	class ClickListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent arg0) {
			try {
				BufferedWriter br = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(saveTo), "UTF-8"));
				for (Product p : show) {
					br.write(p.toString());
					br.newLine();
				}
				br.close();
			} catch(IOException e) {
				System.err.println(e.getMessage());
			}
			JOptionPane.showMessageDialog(null, "�ļ��ɹ�����");
		}
	}
	
	
}
