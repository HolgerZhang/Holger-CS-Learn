package ks1927405160;

import java.io.File;

// ����
public class Main {
	// �ļ�·��
	public static final String inFile = System.getProperty("user.dir") + File.separator + "product.txt";
	public static final String outFile = System.getProperty("user.dir") + File.separator + "result.txt";

	public static void main(String[] args) {
		// �����ļ�����
		File in = new File(inFile);
		File out = new File(outFile);
		new FrmProduct(in, out);  // ����GUI
	}

}
