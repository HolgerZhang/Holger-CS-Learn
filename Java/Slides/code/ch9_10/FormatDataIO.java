package ch9_10;
import java.io.*;

import common.CommVars;

public class FormatDataIO {
	public static void main(String[] args) throws IOException{
		String fname=CommVars.DTP_PROJECT+"out\\t.txt";
		FileOutputStream out1=new FileOutputStream(fname);
		BufferedOutputStream out2=new BufferedOutputStream(out1);	//װ���ļ����
		DataOutputStream out=new DataOutputStream(out2);	//װ�δ�����������
		out.writeByte(-12);
		out.writeLong(12);
		out.writeChar('1');
		out.writeUTF("��");
		out.close();
		
		DataInputStream in=new DataInputStream(new BufferedInputStream(
				new FileInputStream(fname)));
		System.out.println(in.readByte());
		System.out.println(in.readLong());
		System.out.println(in.readChar());
		System.out.println(in.readUTF());
		in.close();
	}
}
