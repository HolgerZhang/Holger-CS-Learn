package ch9_10;
import java.io.*;
public class StrTest {
	public static void main(String[] args) throws IOException{
		String str=new String("บร".getBytes(),"UTF-8");
		ByteArrayInputStream in=new ByteArrayInputStream(str.getBytes("UTF-8"));
		int data=in.read();
		while (data!=-1){
			System.out.println(data);
			data=in.read();
		}
		in.close();
	}
}
