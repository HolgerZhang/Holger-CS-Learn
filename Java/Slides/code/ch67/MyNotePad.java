package ch67;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class MyNotePad extends JFrame {

	private static final long serialVersionUID = 1L;

	private JTextField fname = new JTextField();
	private JTextField dirname = new JTextField();
	
	private JButton openBt = new JButton("打开");
	private JButton saveBt = new JButton("保存");
	
	private JPanel optPane = new JPanel();
	private JPanel navigatePane = new JPanel();
	
	private JTextArea content = new JTextArea();

	public MyNotePad(String title) {
		super(title);
		openBt.addActionListener(new OpenHandler());
		saveBt.addActionListener(new SaveHandler());
		
		optPane.add(openBt);
		optPane.add(saveBt);
		
		dirname.setEditable(false);
		fname.setEditable(false);		
		navigatePane.setLayout(new GridLayout(2, 1));
		navigatePane.add(fname);
		navigatePane.add(dirname);
		
		Container con = this.getContentPane();
		con.add(optPane, BorderLayout.SOUTH);
		con.add(navigatePane, BorderLayout.NORTH);
		con.add(new JScrollPane(content), BorderLayout.CENTER);

		this.setSize(500, 300);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	class OpenHandler implements ActionListener {

		public void actionPerformed(ActionEvent e) {
			JFileChooser jc = new JFileChooser();
			int rVal = jc.showOpenDialog(MyNotePad.this);
			if (rVal==JFileChooser.APPROVE_OPTION)
			{
				File dir=jc.getCurrentDirectory();
				File file=jc.getSelectedFile();
				fname.setText(file.getName());
				dirname.setText(dir.toString());
				//显示内容
				content.setText(read(new File(dir,file.getName())));
			}
			if (rVal==JFileChooser.CANCEL_OPTION)
			{
				fname.setText("You pressed cancel");
				dirname.setText("");
				content.setText("");
			}
		}
	}
	
	class SaveHandler implements ActionListener{

		public void actionPerformed(ActionEvent e) {
			JFileChooser jc=new JFileChooser();
			int rVal=jc.showSaveDialog(MyNotePad.this);
			if (rVal==JFileChooser.APPROVE_OPTION)
			{
				File dir=jc.getCurrentDirectory();
				File file=jc.getSelectedFile();
				fname.setText(file.getName());
				dirname.setText(dir.toString());
				write(new File(dir,file.getName()),content.getText());
			}
			if (rVal==JFileChooser.CANCEL_OPTION)
			{
				fname.setText("You pressed cancel");
				dirname.setText("");
			}
		}	
	}
	
	private String read(File file){
		try{
			BufferedReader rd=new BufferedReader(
					new InputStreamReader(new FileInputStream(file),"GBK"));
			String data=null;
			StringBuffer buffer=new StringBuffer();
			while ((data=rd.readLine())!=null)
				buffer.append(data+"\n");
			rd.close();
			return buffer.toString();
		}catch(IOException e){
			throw new RuntimeException(e);
		}
	}
	
	private void write(File file,String str){
		try{
			PrintWriter writer=new PrintWriter(
					new OutputStreamWriter(new FileOutputStream(file),"GBK"));
			writer.println(str);
			writer.close();
		}catch(IOException e){
			throw new RuntimeException(e);
		}
	}
	
	public static void main(String[] args){
		new MyNotePad("记事本");
	}
}
