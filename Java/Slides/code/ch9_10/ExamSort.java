package ch9_10;
import java.io.*;

public class ExamSort {
	private final int NUM=100;
	int digit[];
	
	private boolean isExist(int x,int i){
		boolean y=false;
		for (int j=0;j<i;j++)
			if (x==digit[j])
				return true;
		return y;
	}
	
	/**
	 * 生成互不相等的三位随机数
	 */
	public void generate(){
		digit=new int[NUM];
		int i=0;
		do{
			int x=(int)(Math.random()*1000);
			if (x<100)
				continue;
			if (isExist(x,i))
				continue;
			digit[i]=x;
			i++;
		}while (i<NUM);
	}
	
	/**
	 *将数组中的内容以二进制数值的方式写入到文件中
	 * @throws IOException 
	 */
	public void writeToBin(File fd,int[] digit) throws IOException{
		FileOutputStream fout=new FileOutputStream(fd);
		DataOutputStream out=new DataOutputStream(new BufferedOutputStream(fout));
		for (int i=0;i<digit.length;i++)
			out.writeInt(digit[i]);
		out.close();
	}
	
	public void writeToBin(File fd) throws IOException{
		this.writeToBin(fd,digit);
	}
	
	/**
	 * 将数组中的内容以文本的方式写入到文件中
	 * @throws IOException 
	 */
	public void writeToTxt(File fd,int[] digit) throws IOException{
		FileOutputStream fo=new FileOutputStream(fd,true);
		BufferedWriter out=new BufferedWriter(new OutputStreamWriter(fo));
		
		for (int i=0;i<digit.length;i++){
			out.write(digit[i]+" ");
			if (i%6==0)
				out.newLine();
		}				
		out.close();
	}

	/**
	 * 从二进制文件中读取数据，形成数组返回
	 * @throws IOException 
	 */
	public int[] readFromBin(File fd) throws IOException{
		int[] st=new int[NUM];
		int i=0;
		DataInputStream in=new DataInputStream(
				new BufferedInputStream(
						new FileInputStream(fd)));
		do{
			st[i]=in.readInt();
			i++;
		}while (i<NUM);
		in.close();
		return st;
	}
	
	private boolean cmpDig(int x,int y,int s,boolean asc){
		boolean r=false;
		int tx,ty;
		tx=ty=x;
		//x=345,s=1/2——表示按个/十位数处理
		for (int i=0;i<s;i++){
			tx=x%10;
			ty=y%10;
			x=x/10;
			y=y/10;
		}
		if (asc)
			r=(tx<=ty);
		else
			r=(tx>=ty);
		return r;
	}
	
	/**
	 * 将数组按要求排序
	 */
	public void sortByCon(int[] source,int bt,boolean asc){
		for (int i=0;i<source.length-1;i++)
			for (int j=0;j<source.length-i-1;j++)
				if (cmpDig(source[j],source[j+1],bt,asc)==false){
					int tmp=source[j];
					source[j]=source[j+1];
					source[j+1]=tmp;
		}
	}
	
	public static void main(String[] args) throws IOException{
		File f1=new File("g:\\mydt.dat");
		File f2=new File("g:\\mysd.dat");
		File f3=new File("g:\\mysd.txt");
		ExamSort st=new ExamSort();
		st.generate();
		st.writeToBin(f1);
		int[] dgs=st.readFromBin(f1);
		st.sortByCon(dgs,1,false);
		st.sortByCon(dgs,2,true);
		st.writeToBin(f2,dgs);
		st.writeToTxt(f3,dgs);
	}
}
