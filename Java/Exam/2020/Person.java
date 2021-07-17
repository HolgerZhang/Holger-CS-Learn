package exam;

public class Person implements Comparable<Person>{
	String id;
	String name;
	int age;
	String email;
	//String tel;
	
	public Person(String aline) {
		String[] items=aline.split(";");
		this.id=items[0];
		this.name=items[1];
		this.setAge(Integer.parseInt(items[2]));
		this.setEmail(items[3]);
	}
	
	public Person(String sid, String snm) {
		this.id=sid;
		this.name=snm;
	}
	
	//public void setTel(String tl){
	//	this.tel=tl;
	//}
	
	public void setAge(int ag) {
		this.age=ag;
	}
	
	public String getId() {
		return this.id;
	}
	
	public String getName() {
		return this.name;
	}
	
	public int getAge() {
		return this.age;
	}
	
	public void setEmail(String em) {
		this.email=em;
	}
	
	public String getEmail() {
		return this.email;
	}
	
	public Person(String sid,String snm, int ag, String em) {
		this(sid,snm);
		this.setAge(ag);
		this.setEmail(em);
	}
	
	public String toString() {
		StringBuffer sbr=new StringBuffer("");
		sbr.append(String.format("%-22s%-10s%-5d%-30s", this.id,this.name,this.age,this.email));
		return sbr.toString();
	}

	//按Email地址进行比较
	public int compareTo(Person p) {
		int ppos=p.getEmail().indexOf("@");
		//String pfix=p.getEmail().substring(ppos+1);
		int tpos=this.email.indexOf("@");
		//String tfix=this.email.substring(tpos+1);
		//int rst=tfix.compareTo(pfix);
		//if (rst!=0)
		//	return rst;
		String pfix=p.getEmail().substring(0, ppos-1);
		String tfix=this.email.substring(0,tpos-1);
		return (tfix.compareTo(pfix));
	}
	
	public boolean isMatch(Person p) {
		boolean rst=true;
		if (!p.getId().trim().isEmpty()) {
			rst=this.id.contains(p.getId());
			if (rst==false)
				return rst;
		}
		if (!p.getName().trim().isEmpty()) {
			rst=this.name.contains(p.getName());
			if (rst==false)
				return rst;
		}
		if (p.getAge()>0) {
			rst=this.age==p.getAge();
			if (rst==false)
				return rst;
		}
		if (!p.getEmail().trim().isEmpty()) {
			rst=this.email.contains(p.getEmail());
			if (rst==false)
				return rst;
		}
		return true;
	}
	
}
