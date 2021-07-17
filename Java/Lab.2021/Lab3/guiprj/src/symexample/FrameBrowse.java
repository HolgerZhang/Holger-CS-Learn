package symexample;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.text.MessageFormat;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * 学生查询类
 *
 * @see FrameNormal
 */
public class FrameBrowse extends FrameNormal {
    private HashMap<String, Student> students;    // 保存学生信息
    private final JLabel favorites;     // 当前学生爱好信息显示
    private List<String> keys;    // 学生索引信息
    private int prev, index, next;      // 前一个，当前，后一个学生索引下标

    /**
     * 构造函数，初始化属性
     */
    public FrameBrowse() {
        super("学生查询", WINDOW_SMALL, "previous", "next");
        this.favorites = new JLabel();
    }

    // 交互逻辑覆盖

    /**
     * 实现窗口显示逻辑，显示窗口前被调用
     * 冻结窗口，显示第一个学生
     */
    @Override
    protected void onStart() {
        super.onStart();
        this.frozen(true);
    }

    /**
     * 刷新显示区域的内容
     */
    @Override
    protected void onRefresh() {
        this.loadStudents();
        this.putStudentToView(getNextStudent());
        this.showStudentIndex();
    }

    // 学生爱好组件实现：标签

    /**
     * 学生爱好显示逻辑
     * 在一个标签中显示
     */
    @Override
    protected void favoriteInitialize() {
        this.favoriteContent.setLayout(new GridLayout(0, 1));
        this.favorites.setFont(FONT_PLAIN);
        this.favoriteContent.add(favorites);
    }

    /**
     * 将学生爱好信息显示到窗口
     *
     * @param favorites 学生爱好信息
     */
    @Override
    protected void putFavorite(List<String> favorites) {
        this.favorites.setText(String.format("<html>%s</html>", String.join("，", favorites)));
    }

    /**
     * 清空显示的学生信息
     */
    @Override
    protected void clearFavorite() {
        this.favorites.setText("");
    }

    // 底部按钮功能实现

    /**
     * 左 (previous) 按钮点击时的回调函数
     * 获取并显示前一个学生，若不存在提示信息
     */
    @Override
    protected void onClickLeftButton() {
        Student student = getPreviousStudent();
        this.showStudentIndex();
        if (student == null) {
            JOptionPane.showMessageDialog(this,
                    (this.keys.size() == 0) ? "没有可显示的学生" : "已经是第一个学生",
                    "没有更多学生",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        this.putStudentToView(student);
    }

    /**
     * 右 (next) 按钮点击时的回调函数
     * 获取并显示后一个学生，若不存在提示信息
     */
    @Override
    protected void onClickRightButton() {
        Student student = getNextStudent();
        this.showStudentIndex();
        if (student == null) {
            String msg = "已经是最后一个学生";
            if (this.keys.size() == 0) {
                msg = "没有可显示的学生";
            }
            JOptionPane.showMessageDialog(this,
                    msg,
                    "没有更多学生",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        this.putStudentToView(student);
    }

    // 辅助函数

    /**
     * 加载学生信息
     */
    private void loadStudents() {
        HashMap<String, Student> studentsFromFile;
        try {
            FileManager manager = new FileManager(Student.SAVED_FILE_NAME);
            studentsFromFile = manager.readStudents();
        } catch (IOException e) {  // 检查是否存在数据冲突
            e.printStackTrace();
            JOptionPane.showMessageDialog(this,
                    e.getMessage(),
                    "数据冲突",
                    JOptionPane.ERROR_MESSAGE);
            studentsFromFile = new HashMap<>();
        } catch (RuntimeException e) {  // 检查是否存在数据异常
            e.printStackTrace();
            JOptionPane.showMessageDialog(this,
                    String.format("%s @file='%s'", e.getMessage(), Student.SAVED_FILE_NAME),
                    "数据异常",
                    JOptionPane.ERROR_MESSAGE);
            studentsFromFile = new HashMap<>();
        }
        this.students = studentsFromFile;
        if (this.students.isEmpty()) {
            this.clear();
        }
        this.keys = new LinkedList<>(this.students.keySet());
        this.prev = -2;
        this.index = -1;
        this.next = 0;
    }

    /**
     * 显示当前展示的学生是第几个
     */
    private void showStudentIndex() {
        this.setBottomLabelText("当前为第 " + (this.index + 1) + " 名学生，共 " + this.keys.size() + " 条数据");
    }

    /**
     * 获取前一个学生
     *
     * @return 前一个学生，若不存在返回 null
     */
    private Student getPreviousStudent() {
        if (this.prev <= -1) {
            return null;
        }
        Student student = this.students.get(this.keys.get(this.prev));
        this.next--;
        this.index--;
        this.prev--;
        return student;
    }

    /**
     * 获取后一个学生
     *
     * @return 后一个学生，若不存在返回 null
     */
    private Student getNextStudent() {
        if (this.next >= this.students.size()) {
            return null;
        }
        Student student = this.students.get(this.keys.get(this.next));
        this.next++;
        this.index++;
        this.prev++;
        return student;
    }

}
