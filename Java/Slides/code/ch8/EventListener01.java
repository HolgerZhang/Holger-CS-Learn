package ch8;

import java.awt.Color;
import java.awt.event.*;
import javax.swing.*;

public class EventListener01 implements ActionListener{
	private JPanel jpl;
	public EventListener01(JPanel tmp){
		jpl=tmp;
	}	
	public void actionPerformed(ActionEvent e) {
		//���ݵ����ť��������֣��졢�ơ������޸�jpl�ı���ɫ
		String str=e.getActionCommand();
		if (str.trim().equals("��ɫ"))
			jpl.setBackground(Color.RED);
		else if (str.trim().equals("��ɫ"))
			jpl.setBackground(Color.BLUE);
		else if (str.trim().equals("��ɫ"))
			jpl.setBackground(Color.YELLOW);
	}
}
