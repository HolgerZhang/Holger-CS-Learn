package studentCardRecord;

import studentCardRecord.entity.Record;
import studentCardRecord.entity.Student;
import studentCardRecord.manager.FileManager;
import studentCardRecord.manager.StudentCardManager;

import java.io.IOException;
import java.util.List;

public class Execute {

    public static final String STUDENT_DATA_FILE = "resource/Stddata.txt";
    public static final String CARD_DATA_FILE = "resource/StdCard.txt";
    public static final String RECORD_DATA_FILE = "resource/Recorddata.txt";
    public static final String SAVE_TO_FILE = "resource/SaveTop.txt";
    public static final String SPLIT_STRING = "**************************************************";

    private final StudentCardManager container;

    public Execute() {
        this.container = new StudentCardManager();
    }

    public static void main(String[] args) {
        Execute execute = new Execute();
        // 读取文件，构建 "学生-一卡通-消费" 状态
        execute.establishState();
        // 统计每位学生一卡通的消费情况
        execute.statisticsAndSortStudent();
        // 找到存钱最多的学生，将其基本信息、其对应的一卡通信息，以及详细的用卡信息以文本文件的形式保存
        execute.findAndSaveDepositTopStudent();
    }

    public void establishState() {
        try {
            this.loadStudentData();
            this.loadCardData();
            this.loadRecordData();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void loadStudentData() throws IOException {
        FileManager fileManager = new FileManager(STUDENT_DATA_FILE, FileManager.IOMode.READ);
        fileManager.readLines(line -> {
            String[] fields = line.trim().split(" ");
            String studentId = fields[0], name = fields[1], major = fields[3], phone = fields[4];
            int year = Integer.parseInt(fields[2]); // 入学年份
            container.addStudent(studentId, name, year, major, phone);
        });
    }

    private void loadCardData() throws IOException {
        FileManager fileManager = new FileManager(CARD_DATA_FILE, FileManager.IOMode.READ);
        fileManager.readLines(line -> {
            String[] fields = line.trim().split(" ");
            // 学号 一卡通卡号
            String studentId = fields[0], cardId = fields[1];
            container.linkStudentCard(studentId, cardId);
        });
    }

    private void loadRecordData() throws IOException {
        FileManager fileManager = new FileManager(RECORD_DATA_FILE, FileManager.IOMode.READ);
        fileManager.readLines(line -> {
            String[] fields = line.trim().split(" ");
            String cardId = fields[0];  // 卡号
            // 用卡类型
            Record.RecordType type = (Integer.parseInt(fields[1]) == 0) ? Record.RecordType.DEPOSIT : Record.RecordType.CONSUME;
            double amount = Double.parseDouble(fields[2]);  // 发生金额
            int place = Integer.parseInt(fields[3]);    // 发生地点编号
            container.addRecord(cardId, type, amount, place);
        });
    }

    public void statisticsAndSortStudent() {
        // 按消费金额的非降序对学生进行排序
        this.container.getStudents().sort((student1, student2) -> {
            int consume1 = (int) (container.findCardByStudentId(student1.getId()).getConsume() * 100);
            int consume2 = (int) (container.findCardByStudentId(student2.getId()).getConsume() * 100);
            return consume1 - consume2;
        });
        // 将排序后的学生基本信息、其对应的一卡通基本信息和消费总金额发送到屏幕显示
        container.getStudents().forEach(student -> {
            System.out.println(SPLIT_STRING);
            System.out.println(student);
            System.out.println(container.findCardByStudentId(student.getId()).briefInformation());
        });
    }

    public void findAndSaveDepositTopStudent() {
        // 找到存钱最多的学生
        List<Student> students = this.container.getStudents();
        Student depositTopStudent = students.get(0);
        for (Student student : students) {
            if (this.container.findCardByStudentId(depositTopStudent.getId()).getDeposit() <
                    this.container.findCardByStudentId(student.getId()).getDeposit()) {
                // 若当前学生的存钱更多，替换之
                depositTopStudent = student;
            }
        }
        // 将其基本信息、其对应的一卡通信息，以及详细的用卡信息以文本文件的形式保存
        FileManager fileManager = new FileManager(SAVE_TO_FILE, FileManager.IOMode.WRITE);
        try {
            fileManager.writeLines(SPLIT_STRING,
                    depositTopStudent.toString(),
                    container.findCardByStudentId(depositTopStudent.getId()).detailedInformation());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
