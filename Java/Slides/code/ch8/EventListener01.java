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
		//根据点击按钮上面的文字（红、黄、蓝）修改jpl的背景色
		String str=e.getActionCommand();
		if (str.trim().equals("红色"))
			jpl.setBackground(Color.RED);
		else if (str.trim().equals("蓝色"))
			jpl.setBackground(Color.BLUE);
		else if (str.trim().equals("黄色"))
			jpl.setBackground(Color.YELLOW);
	}
}
