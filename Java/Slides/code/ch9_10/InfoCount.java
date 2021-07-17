package ch9_10;
import java.io.*;
import java.util.*;

public class InfoCount {
	public static ArrayList<String> readFromTxt(File fd) throws IOException{
		ArrayList<String> ret=new ArrayList<String>();
		FileReader rd=new FileReader(fd);
		BufferedReader in=new BufferedReader(rd);
		String line=in.readLine();
		while (line!=null){
			ret.add(line);
			line=in.readLine();
		}
		in.close();
		return ret;
	}
	
	public static int wordCount(String s){
		int ct=0;
		s=s.replaceAll("\t"," ");
		String[] t=s.split(" ");
		for (int i=0;i<t.length;i++)
			if (t[i].trim().length()>0)
				ct++;
		return ct;
	}
	
	public static void main(String[] args) throws IOException{
		File fd=new File("g:\\in.txt");
		ArrayList lst=readFromTxt(fd);
		int lines=0;
		int words=0;
		int chars=0;
		if (lst!=null)
			lines=lst.size();
		System.out.println("行数："+lines);
		for (int i=0;i<lines;i++){
			String str=(String)lst.get(i);
			chars+=str.toCharArray().length;
			words+=wordCount(str);
		}
		System.out.println("单词数："+words);
		System.out.println("字符数："+chars);
	}
}
