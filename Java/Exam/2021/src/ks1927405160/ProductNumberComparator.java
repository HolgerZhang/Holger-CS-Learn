package ks1927405160;

import java.util.Comparator;

//���տ������ıȽ���
public class ProductNumberComparator implements Comparator<Product> {
	@Override
	public int compare(Product arg0, Product arg1) {
		return arg0.getNumber() - arg1.getNumber();
	}
}
