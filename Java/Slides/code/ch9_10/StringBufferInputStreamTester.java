package ch9_10;
import java.io.*;

public class StringBufferInputStreamTester {
	public static void main(String[] args) throws IOException{
		StringBufferInputStream in=new StringBufferInputStream("���ã�");
		int data=in.read();
		while (data!=-1){
			//System.out.print(data+" ");
			System.out.print((char)data+" ");
			data=in.read();
		}
		in.close();
	}
}
