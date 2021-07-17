package ch9_10;
import java.io.*;
public class PrintStreamTester{
	public static void readBuff(byte[] buff) throws IOException{
		ByteArrayInputStream in=new ByteArrayInputStream(buff);
		int data;
		while ((data=in.read())!=-1)
			System.out.print(data+" ");
		System.out.println();
		in.close();
	}
	
	public static void main(String[] args) throws IOException{
		ByteArrayOutputStream out=new ByteArrayOutputStream();
		PrintStream ps=new PrintStream(out,true);
		ps.print("��");
		ps.close();		
		byte[] buff=out.toByteArray();
		System.out.println("���ñ��ز���ϵͳĬ���ַ����룺");
		readBuff(buff);
		
		out=new ByteArrayOutputStream();
		DataOutputStream ds=new DataOutputStream(out);
		ds.writeUTF("��");
		ds.close();
		buff=out.toByteArray();
		System.out.println("����������Java��UTF-8���룺");
		readBuff(buff);
		
		byte[] b="��".getBytes("UTF-8");
		for (int i=0;i<b.length;i++)
			System.out.print(b[i]+" ");
		
	}
}
