package ch9_10;

import java.io.*;

import common.CommVars;

public class UseBuffer {
	public static void main(String[] args) throws IOException{
		final int size=1024;
		FileInputStream in=new FileInputStream(CommVars.DTP_PROJECT+"out\\results.txt");
		FileOutputStream out=new FileOutputStream(CommVars.DTP_PROJECT+"out\\out.txt");
		byte[] buff=new byte[size];
		int len=in.read(buff);
		while (len!=-1){
			out.write(buff,0,len);
			len=in.read(buff);
		}
		in.close();
		out.close();
	}
}
