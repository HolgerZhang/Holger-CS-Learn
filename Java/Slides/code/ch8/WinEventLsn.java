package ch8;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class WinEventLsn extends WindowAdapter{
	public void windowClosing(WindowEvent arg0) {
		System.exit(0);
	}
}
