package ks1927405160;

public class Product {
	public static String[] TYPES = { "ȫ��", "����", "�ֻ�", "�鼮" }; // ��������

	private String id;  //��Ʒ���
	private String name; // ����
	private String type; // ����
	private double price; // �۸�
	private int number; // ���

	public Product(String line) {
		String[] args = line.split(";");
		id = args[0];
		name = args[1];
		type = args[2];
		price = Double.parseDouble(args[3]);
		number = Integer.parseInt(args[4]);
	}

	public String toString() {
		return id + ";" + name + ";" + type + ";" + price + ";" + number;
	}
	
	public String getType() {
		return type;
	}
	
	public String getId() {
		return id;
	}
	
	public int getNumber() {
		return number;
	}
	
}
