package ks1927405160;

import java.util.Comparator;

// ����id����ıȽ���
public class ProductIdComparator implements Comparator<Product> {
	@Override
	public int compare(Product arg0, Product arg1) {
		return arg0.getId().compareTo(arg1.getId());
	}
}
