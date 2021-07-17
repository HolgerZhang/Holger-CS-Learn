package ch9_10;
import java.io.*;
import java.nio.charset.*;

public class EncodeTester {
	public static void main(String[] arg) throws IOException{
		System.out.println("���ڴ��в���Unicode���룺");
		char c='��';
		int lowBit=c & 0xFF;	//��õ�8λ
		int highBit=(c & 0xFF00) >> 8;	//��ø�8λ
		System.out.println(highBit+" "+lowBit);
		
		String s="��";
		System.out.println("���ñ��ز���ϵͳĬ���ַ����룺");
		PrintStreamTester.readBuff(s.getBytes());
		
		System.out.println("����GBK�ַ����룺");
		PrintStreamTester.readBuff(s.getBytes("GBK"));
		
		System.out.println("���ñ�׼UTF-8���룺");
		PrintStreamTester.readBuff(s.getBytes("UTF-8"));
		
		Charset ch=Charset.defaultCharset();
		System.out.println(ch);
	}
}
