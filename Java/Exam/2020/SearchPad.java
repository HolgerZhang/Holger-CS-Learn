package exam;
import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

import javax.swing.*;

public class SearchPad extends JFrame{
	JTextField jtfId, jtfName, jtfAge, jtfEmail;
	//JButton btnLoad;
	JButton btnSrch;
	
	
	class SrchAction implements ActionListener{

		Person srchPerson;	//待查找的人
		ArrayList<Person> personLst;	//已有的人员列表
		
		public void setsrchPerson() {
			srchPerson=new Person(jtfId.getText(), jtfName.getText());
			if (!jtfAge.getText().trim().isEmpty())
			srchPerson.setAge(Integer.parseInt(jtfAge.getText().trim()));
			srchPerson.setEmail(jtfEmail.getText());
		}
		
		public void setpersonLst(File fd){
			try {
				BufferedReader br=new BufferedReader(new FileReader(fd));
				personLst=new ArrayList<Person>();
				String aline=br.readLine();
				while (aline!=null && !aline.trim().isEmpty()) {
					Person p=new Person(aline);
					personLst.add(p);
					aline=br.readLine();
				}			
				br.close();
			}catch(IOException e) {
				System.err.println(e.getMessage());
			}
		}
		
		public ArrayList<Person> search(){
			if (personLst==null || personLst.isEmpty() || srchPerson==null)
				return null;
			ArrayList<Person> rst=new ArrayList<Person>();
			Iterator<Person> itr=personLst.iterator();
			while (itr.hasNext()) {
				Person p=itr.next();
				if (p.isMatch(srchPerson))
					rst.add(p);
			}
			return rst;
		}
		
		public void savesearchRst(File fd,ArrayList<Person> r) {
			try {
				BufferedWriter bw=new BufferedWriter(new FileWriter(fd));
				Collections.sort(r);
				for (Person p:r) {
					bw.write(p.toString());
					bw.newLine();
				}
				bw.close();
			}catch(IOException e) {
				System.err.println(e.getMessage());
			}
		}
		
		public void actionPerformed(ActionEvent eve) {
			/*
			Object src=eve.getSource();
			if (src==btnLoad) {
				File fd=new File(MainTest.SrcDTP);
				this.setpersonLst(fd);
				JOptionPane.showMessageDialog(null, "加载完毕！");
			}
			else if (src==btnSrch) {
				if (this.personLst==null) {
					File fd=new File(MainTest.SrcDTP);
					this.setpersonLst(fd);
				}
				*/
			File fd=new File(MainTest.SrcDTP);
			this.setpersonLst(fd);
			this.setsrchPerson();
			ArrayList<Person> rst=this.search();
			fd=new File(MainTest.RstDTP);
			this.savesearchRst(fd, rst);
			JOptionPane.showMessageDialog(null, "查找结果已保存到指定文件！");
		}
	}

	
	public SearchPad() {
		jtfId=new JTextField(10);
		jtfName=new JTextField(10);
		jtfAge=new JTextField(10);
		jtfEmail=new JTextField(10);
		//btnLoad=new JButton("加载");
		btnSrch=new JButton("查找");
		
		SrchAction actRsv=new SrchAction();
		
		Box line1=Box.createHorizontalBox();
		Box line2=Box.createHorizontalBox();
		Box line3=Box.createHorizontalBox();
		Box line4=Box.createHorizontalBox();
		line1.add(Box.createHorizontalStrut(10));
		line1.add(new JLabel("编号："));
		line1.add(Box.createGlue());
		line1.add(jtfId);
		
		line2.add(Box.createHorizontalStrut(10));
		line2.add(new JLabel("姓名："));
		line2.add(Box.createGlue());
		line2.add(jtfName);
		
		line3.add(Box.createHorizontalStrut(10));
		line3.add(new JLabel("年龄："));
		line3.add(Box.createGlue());
		line3.add(jtfAge);
		
		line4.add(Box.createHorizontalStrut(10));
		line4.add(new JLabel("Email："));
		line4.add(Box.createGlue());
		line4.add(jtfEmail);
		
		Box bx=Box.createVerticalBox();
		bx.add(line1);
		bx.add(Box.createVerticalStrut(10));
		bx.add(line2);
		bx.add(Box.createVerticalStrut(10));
		bx.add(line3);
		bx.add(Box.createVerticalStrut(10));
		bx.add(line4);
		JPanel tmp=new JPanel();
		//tmp.add(btnLoad);
		tmp.add(btnSrch);
		//btnLoad.addActionListener(actRsv);
		btnSrch.addActionListener(actRsv);
		Container c=this.getContentPane();
		c.add(bx, BorderLayout.CENTER);
		c.add(tmp,BorderLayout.SOUTH);
		
		this.setSize(300,250);
		this.setTitle("查找");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}
}
