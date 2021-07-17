package exam;

public class MainTest {
	public final static String DTP_PROJECT=System.getProperty("user.dir")+"/out";
	public final static String SrcDTP=DTP_PROJECT+"/src.txt";
	public final static String RstDTP=DTP_PROJECT+"/rst.txt";
	public static void main(String[] args) {
		new SearchPad();
	}
}
