package symexample;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

/**
 * 学生类
 */
public class Student {
    // 学院信息属性值
    public static final String[] COLLEGE = new String[]{"计算机科学与技术学院", "光电科学与工程学院", "数学科学学院",
            "东吴商学院", "物理科学与技术学院", "外国语学院", "电子信息学院", "能源学院", "纺织与服装工程学院", "王健法学院"};
    // 爱好信息属性值
    public static final String[] FAVORITE = new String[]{"读书", "听音乐", "跑步", "乒乓球", "羽毛球", "滑雪"};
    // 性别
    public static final String SEX_MAN = "男";
    public static final String SEX_WOMAN = "女";
    // 数据格式化分隔符
    public static final String FIELD_SEPARATOR = "/";
    public static final String FAVORITE_SEPARATOR = ",";
    public static final String SAVED_FILE_NAME = "student.txt"; // 数据保存路径
    // 数据字段
    private final String id;    // 学号
    private final String name;  // 姓名
    private final String sex;      // 性别
    private final String college;// 学院
    private final String city;  // 城市
    private final LinkedList<String> favorite;  // 爱好

    /**
     * 构造函数
     *
     * @param id       学号
     * @param name     姓名
     * @param sex      性别
     * @param college  学院
     * @param city     城市
     * @param favorite 爱好
     */
    public Student(String id, String name, String sex, String college, String city, List<String> favorite) throws RuntimeException {
        this.id = id;
        this.name = name;
        if (!(sex.equals(SEX_MAN) || sex.equals(SEX_WOMAN))) {
            throw new RuntimeException("错误的 sex 属性");
        }
        this.sex = sex;
        this.college = college;
        this.city = city;
        this.favorite = new LinkedList<>(favorite);
    }

    // 属性 Getter Setter

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getSex() {
        return sex;
    }

    public String getCollege() {
        return college;
    }

    public String getCity() {
        return city;
    }

    public List<String> getFavorite() {
        return favorite;
    }

    // 字符串序列化/反序列化方法

    /**
     * 将学生信息转换为字符串
     * 格式：id/name/sex/college/city/favorite_1,favorite_2,...,favorite_n
     */
    @Override
    public String toString() {
        return id + FIELD_SEPARATOR + name + FIELD_SEPARATOR + sex + FIELD_SEPARATOR + college + FIELD_SEPARATOR
                + city + FIELD_SEPARATOR + String.join(FAVORITE_SEPARATOR, favorite);
    }

    /**
     * 字符串解析为 Student 对象
     * 格式：id/name/sex/college/city/favorite_1,favorite_2,...,favorite_n
     */
    public static Student parseStudent(String string) throws RuntimeException {
        String[] line = string.trim().split(FIELD_SEPARATOR);
        List<String> favorites = new LinkedList<>();
        if (line.length == 6) {
            favorites = Arrays.asList(line[5].trim().split(FAVORITE_SEPARATOR));
        }
        return new Student(line[0], line[1], line[2], line[3], line[4], favorites);
    }

}
