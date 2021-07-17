package ch9_10;
import java.io.*;
public class ByteArrayTester {
	public static void main(String[] args){
		byte[] buff=new byte[]{2,15,67,-1,-9,9};
		/**int=>-1: 00000����0001=>111����10=>111����1(32��)
		 *=>byte: 11111111(�õ��ģ�1��Ӧ��byte��
		 *int =>-9: 0000����0001001=>111����1110110=>111����10111
		 *=>byte:11110111(�õ��ģ�9��Ӧ��byte)	 */		
		ByteArrayInputStream in=null;
		in=new ByteArrayInputStream(buff,1,4);		
		int data=in.read();
		/**byte:11111111��> 00000����011111111(32λ)int
		 * intֵ255
		 * byte:11110111=> 0000����011110111(32λ) int
		 * intֵ247
		 */
		while (data!=-1){
			System.out.println(data+" ");
			data=in.read();
		}	
		try{
			in.close();
		}catch(IOException e){
			System.err.println(e.getMessage());
		}
	}
}
