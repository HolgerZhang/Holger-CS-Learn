package ch9_10;

import java.io.*;
import java.util.Date;

public class UseFile {
	public static void listDir(File dir){
		if (dir.isFile())
			return;
		
		File[] lists=dir.listFiles();		
		String info="目录:"+dir.getName()+"(";
		for (int i=0;i<lists.length;i++)
			info+=lists[i].getName()+" ";
		info+=")";
		System.out.println(info);
		
		for (int i=0;i<lists.length;i++){
			File f=lists[i];
			if (f.isFile())
				System.out.println("文件:"+f.getName()
						+" canRead:"+f.canRead()
						+" lastModified:"+new Date(f.lastModified()));
			else
				listDir(f);		//递归调用
		}
	}
	
	
	public static void deleteDir(File file){
		if (file.isFile()){
			file.delete();
			return;
		}
		//是目录，先删除目录下的所有文件和子目录，最后删除该目录
		File[] lists=file.listFiles();
		for (int i=0;i<lists.length;i++)
			deleteDir(lists[i]);		//递归调用
		file.delete();
	}
	
	public static void main(String[] args) throws IOException {
		File dir1=new File("g:\\svm");
//		if (!dir1.exists())
//			dir1.mkdir();
//		
//		File dir2=new File(dir1,"dir2");
//		if (!dir2.exists())
//			dir2.mkdir();
//		
//		File dir4=new File(dir1,"dir3\\dir4");
//		if (!dir4.exists())
//			dir4.mkdirs();
//		
//		File file=new File(dir2,"test.txt");
//		if (!file.exists())
//			file.createNewFile();
		
//		listDir(dir1);
		deleteDir(dir1);
	}

}
