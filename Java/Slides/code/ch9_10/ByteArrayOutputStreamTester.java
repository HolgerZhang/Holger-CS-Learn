package ch9_10;
import java.io.*;

public class ByteArrayOutputStreamTester {
	public static void main(String[] args) throws IOException{
		ByteArrayOutputStream out=new ByteArrayOutputStream();
		byte[] a="ÄãºÃ".getBytes("UTF-8");
		out.write(a);
		
		for (int i=0;i<a.length;i++)
			System.out.print(a[i]+",");
		
		byte[] buff=out.toByteArray();
		out.close();
		
		ByteArrayInputStream in=new ByteArrayInputStream(buff);
		int len=in.available();
		byte[] buffin=new byte[len];
		in.read(buffin);
		in.close();
		
		System.out.println(new String(buffin,"UTF-8"));
	}
}
