package symexample;

import java.io.*;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;

/**
 * 文件管理类
 */
public class FileManager {

    private final File file;

    public FileManager(String filename) throws IOException {
        String filePath = System.getProperty("user.dir") + File.separator + filename;
        this.file = new File(filePath);
        if (!this.file.exists()) {
            if (!this.file.createNewFile()) {
                throw new IOException("文件创建失败");
            }
        }
    }

    /**
     * 向文件追加按行写入学生信息
     *
     * @param student 学生对象
     */
    public void writeStudent(Student student) throws IOException {
        try (FileOutputStream file = new FileOutputStream(this.file, true);
             OutputStreamWriter out = new OutputStreamWriter(file);
             BufferedWriter writer = new BufferedWriter(out)) {  // try-with-resources 结构管理文件对象
            writer.write(student.toString());
            writer.newLine();
        }
    }

    /**
     * 从文件按行读取学生信息
     *
     * @return 保存学生信息的 HashMap
     */
    public HashMap<String, Student> readStudents() throws IOException {
        HashMap<String, Student> students = new HashMap<>();
        int lines = 0;
        try (FileInputStream in = new FileInputStream(this.file);
             BufferedReader reader = new BufferedReader(new InputStreamReader(in))) {  // try-with-resources 结构管理文件对象
            String rawLine;
            while ((rawLine = reader.readLine()) != null) {
                lines++;
                Student student = Student.parseStudent(rawLine);
                students.put(student.getId(), student);
            }
        }
        if (lines != students.size()) { // 检查文件是否存在冲突
            throw new IOException("学生学号存在重复项，数据加载失败");
        }
        return students;
    }

}
