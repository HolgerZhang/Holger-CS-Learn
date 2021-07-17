package studentCardRecord.entity;

/**
 * 学生类
 */
public class Student {
    private final String id;    // 14 位学号
    private final String name;  // 姓名
    private final int year;     // 入学年份
    private final String major; // 专业
    private final String phone; // 联系电话

    public Student(String id, String name, int year, String major, String phone) {
        this.id = id;
        this.name = name;
        this.year = year;
        this.major = major;
        this.phone = phone;
    }

    public String getId() {
        return this.id;
    }

    public String getName() {
        return this.name;
    }

    public int getYear() {
        return this.year;
    }

    public String getMajor() {
        return this.major;
    }

    public String getPhone() {
        return this.phone;
    }

    @Override
    public String toString() {
        return "学号：" + this.id + System.lineSeparator() +
                "姓名：" + this.name + System.lineSeparator() +
                "入学年份：" + this.year + System.lineSeparator() +
                "专业：" + this.major + System.lineSeparator() +
                "联系方式：" + this.phone;
    }
}
