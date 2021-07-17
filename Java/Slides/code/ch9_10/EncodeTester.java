package ch9_10;
import java.io.*;
import java.nio.charset.*;

public class EncodeTester {
	public static void main(String[] arg) throws IOException{
		System.out.println("在内存中采用Unicode编码：");
		char c='好';
		int lowBit=c & 0xFF;	//获得低8位
		int highBit=(c & 0xFF00) >> 8;	//获得高8位
		System.out.println(highBit+" "+lowBit);
		
		String s="好";
		System.out.println("采用本地操作系统默认字符编码：");
		PrintStreamTester.readBuff(s.getBytes());
		
		System.out.println("采用GBK字符编码：");
		PrintStreamTester.readBuff(s.getBytes("GBK"));
		
		System.out.println("采用标准UTF-8编码：");
		PrintStreamTester.readBuff(s.getBytes("UTF-8"));
		
		Charset ch=Charset.defaultCharset();
		System.out.println(ch);
	}
}
