package symexample;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * 学生注册窗口类
 *
 * @see FrameNormal
 */
public class FrameRegister extends FrameNormal {
    private final ArrayList<Student> students;  // 所有新增的学生
    private final ArrayList<JCheckBox> favorites;   // 学生爱好

    /**
     * 构造函数，初始化属性
     */
    public FrameRegister() {
        super("学生注册", WINDOW_SMALL, "新增", "保存");
        this.students = new ArrayList<>();
        this.favorites = new ArrayList<>();
    }

    // 交互逻辑覆盖

    /**
     * 实现窗口显示逻辑，显示窗口前被调用
     * 不冻结窗口，设置底部标签值
     */
    @Override
    protected void onStart() {
        super.onStart();
        this.frozen(false);
    }

    /**
     * 窗口关闭时的操作，关闭窗口前被调用
     * 检查是否有未保存的学生信息
     *
     * @return true
     */
    @Override
    protected boolean onFinish() {
        this.checkNotAddedStudent();
        if (!students.isEmpty()) {
            if (JOptionPane.showConfirmDialog(this,
                    String.format("还有 %d 个学生信息未保存，是否在关闭前保存？", this.students.size()),
                    "未保存的学生",
                    JOptionPane.YES_NO_OPTION) == JOptionPane.OK_OPTION) {
                this.onClickRightButton();
            } else {
                this.students.clear();
                this.setBottomLabelText("已添加 0 名学生");
            }
        }
        return true;
    }

    /**
     * 刷新显示区域的内容
     */
    @Override
    protected void onRefresh() {
        this.setBottomLabelText("已添加 0 名学生");
    }

    // 学生爱好组件实现：多选框

    /**
     * 学生爱好显示逻辑
     * 多选框实现
     */
    @Override
    protected void favoriteInitialize() {
        GridLayout layout = new GridLayout(0, 3);
        layout.setHgap(15);
        layout.setVgap(5);
        this.favoriteContent.setLayout(layout);
        for (String item : Student.FAVORITE) {
            JCheckBox box = new JCheckBox(item);
            box.setFont(FONT_NORMAL);
            this.favoriteContent.add(box);
            this.favorites.add(box);
        }
    }

    /**
     * 清空学生爱好信息
     * 所有多选框取消选定
     */
    @Override
    protected void clearFavorite() {
        for (JCheckBox box : this.favorites) {
            box.setSelected(false);
        }
    }

    /**
     * 从窗口获取学生爱好信息
     *
     * @return 学生爱好信息
     */
    @Override
    protected List<String> accessFavorite() {
        ArrayList<String> result = new ArrayList<>();
        for (JCheckBox box : this.favorites) {
            if (box.isSelected()) {
                result.add(box.getText());
            }
        }
        return result;
    }

    // 底部按钮功能实现

    /**
     * 左（新增）按钮点击时的回调函数
     * 临时保存用户此次输入的学生的注册信息到集合类 ArrayList 中
     */
    @Override
    protected void onClickLeftButton() {
        Student student = this.getStudentFromView(false);
        if (student != null) {
            this.students.add(student);
            this.clear();
            this.setBottomLabelText(String.format("已添加 %d 名学生", this.students.size()));
        }
    }

    /**
     * 右（保存）按钮点击时的回调函数
     * 保存用户此次输入的学生的注册信息到文件中
     * 检查是否有没有新增的学生以及是否输入学生
     */
    @Override
    protected void onClickRightButton() {
        this.checkNotAddedStudent();
        if (this.students.size() == 0) {  // 没有添加学生信息
            JOptionPane.showMessageDialog(this,
                    "还没有添加学生信息",
                    "注册失败",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        boolean success = true;
        try {
            FileManager manager = new FileManager(Student.SAVED_FILE_NAME);
            for (Student student : this.students) {
                manager.writeStudent(student);
            }
        } catch (IOException e) {  // 出现错误
            e.printStackTrace();
            success = false;
            JOptionPane.showMessageDialog(this,
                    String.format("%d 名学生注册时出现错误\n%s", this.students.size(), e.getMessage()),
                    "注册失败",
                    JOptionPane.INFORMATION_MESSAGE);
        }
        if (success) {  // 注册成功
            JOptionPane.showMessageDialog(this,
                    String.format("成功注册 %d 名学生", this.students.size()),
                    "注册成功",
                    JOptionPane.INFORMATION_MESSAGE);
            this.setBottomLabelText("已添加 0 名学生");
            this.students.clear();
        }
    }

    // 辅助函数

    /**
     * 检查显示区域还有未新增的学生信息
     * 如有，询问是否新增
     */
    private void checkNotAddedStudent() {
        Student tempStudent = this.getStudentFromView(true);
        if (tempStudent != null) {
            if (JOptionPane.showConfirmDialog(this,
                    "显示区域还有未新增的学生信息，是否新增？",
                    "未新增的学生",
                    JOptionPane.YES_NO_OPTION) == JOptionPane.OK_OPTION) {
                this.students.add(tempStudent);
                this.setBottomLabelText(String.format("已添加 %d 名学生", this.students.size()));
            }
            this.clear();
        }
    }
}
