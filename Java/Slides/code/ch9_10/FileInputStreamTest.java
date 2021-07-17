package ch9_10;

import java.io.*;
import common.CommVars;

public class FileInputStreamTest {
	public static void main(String[] args) throws IOException{
		FileOutputStream fin=new FileOutputStream(CommVars.DTP_PROJECT+"out\\results_2.txt");
		OutputStreamWriter out=new OutputStreamWriter(fin,"UTF-8");
		BufferedWriter bw=new BufferedWriter(out);
		
		FileReader fr=new FileReader(CommVars.DTP_PROJECT+"out\\results.txt");
		BufferedReader br=new BufferedReader(fr);
		String aln=br.readLine();
		while (aln!=null)
		{
			bw.write(aln);
			bw.newLine();
			aln=br.readLine();
		}
		br.close();
		bw.close();
	}
}
