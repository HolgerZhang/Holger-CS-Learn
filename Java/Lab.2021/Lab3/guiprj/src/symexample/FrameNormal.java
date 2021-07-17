package symexample;

import javax.swing.*;
import java.awt.*;
import java.util.List;

/**
 * 学生信息显示基类（抽象类）
 * 不可直接实例化，需要重写方法：
 * - (abstract) setFavoriteToShow(): void
 * - (abstract) onClickLeftButton(): void
 * - (abstract) onClickRightButton(): void
 * 根据需要重写方法：
 * - clearFavorite(): void
 * - accessFavorite(): List
 * - putFavorite(List): void
 *
 * @see FrameBase
 */
public abstract class FrameNormal extends FrameBase {

    private static final int TEXT_MAX_SIZE = 20; // 文本框最大大小
    private static final int HORIZONTAL_STRUT_WIDTH = 40;   // 水平支柱大小
    private static final int VERTICAL_STRUT_HEIGHT = 50;    // 垂直支柱大小

    protected final Container favoriteContent;   // 为学生爱好的显示提供专有面板，供子类实现显示逻辑

    private final Container centerContent;    // 中央信息面板
    private final JTextField idText;    // 学号文本框
    private final JTextField nameText;  // 姓名文本框
    private final JRadioButton manButton;  // 性别：男单选框
    private final JRadioButton womanButton;// 性别：女单选框
    private final JRadioButton emptySexButton;// 性别未选中（不显示，用于表示未选定性别的状态）
    private final JComboBox<String> collegeList; // 学院下拉列表
    private final JTextField cityText;  // 城市文本框
    private final JButton leftButton;      // 左按钮
    private final JButton rightButton;     // 右按钮
    private final JLabel bottomLabel;   // 底部标签

    /**
     * 构造函数，初始化属性
     *
     * @param title        窗口标题
     * @param size         窗口大小
     * @param leftBtnName  左按钮文本
     * @param rightBtnName 右按钮文本
     */
    protected FrameNormal(String title, Dimension size, String leftBtnName, String rightBtnName) {
        super(title, size);
        // 组件初始化
        this.idText = new JTextField();
        this.nameText = new JTextField();
        this.cityText = new JTextField();
        this.manButton = new JRadioButton("男");
        this.womanButton = new JRadioButton("女");
        this.emptySexButton = new JRadioButton();
        this.collegeList = new JComboBox<>(Student.COLLEGE);
        this.favoriteContent = new JPanel();
        this.bottomLabel = new JLabel();
        this.leftButton = new JButton(leftBtnName);
        this.rightButton = new JButton(rightBtnName);
        this.centerContent = new JPanel();
    }

    // 重写覆盖窗口显示逻辑

    /**
     * 实现窗口显示逻辑，显示窗口前被调用
     * 设置为不可最大化，2 列布局，并初始化窗口各组件
     */
    @Override
    protected void onStart() {
        super.onStart();
        this.setResizable(false);    // 不可改变大小
        // 初始化中央信息面板
        this.centerContent.setLayout(new BoxLayout(this.centerContent, BoxLayout.PAGE_AXIS));
        this.content.add(this.centerContent, BorderLayout.CENTER);
        this.centerContent.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        this.centerContent.add(Box.createVerticalGlue());
        // 初始化各组件
        this.initNowPosition();
        this.initTextField("<html>学号 <font color=\"red\">*</font></html>", this.idText);
        this.initTextField("<html>姓名 <font color=\"red\">*</font></html>", this.nameText);
        this.initTextField("<html>城市 <font color=\"red\">*</font></html>", this.cityText);
        this.initSexChoice();
        this.initCollegeBox();
        this.initFavorite();
        this.initButton();
        this.initBottomLabel();
    }

    // 组件初始化方法

    /**
     * 初始化顶部位置信息
     */
    private void initNowPosition() {
        JLabel titleLabel = new JLabel("当前位置：" + this.getTitle());
        titleLabel.setHorizontalAlignment(JLabel.LEFT);
        titleLabel.setFont(FONT_PLAIN);
        this.content.add(titleLabel, BorderLayout.NORTH);
    }

    /**
     * 学生信息组件统一初始化方法
     *
     * @param labelString 提示文字
     * @param container   学生信息组件
     */
    private void normalInitialize(String labelString, Container container) {
        Box box = Box.createHorizontalBox();
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        JLabel label = new JLabel(labelString);
        label.setHorizontalAlignment(JLabel.LEFT);
        label.setFont(FONT_NORMAL);
        box.add(label);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        box.add(container);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.centerContent.add(box);
        this.centerContent.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
    }

    /**
     * 初始化文本框
     *
     * @param labelString 提示文字
     * @param textField   文本框对象
     */
    private void initTextField(String labelString, JTextField textField) {
        textField.setFont(FONT_PLAIN);
        textField.setColumns(TEXT_MAX_SIZE);
        this.normalInitialize(labelString, textField);
    }

    /**
     * 初始化性别单选项
     * 只有一个单选框可以被选中
     */
    private void initSexChoice() {
        Container innerSexContainer = new JPanel();
        GridLayout layout = new GridLayout(0, 2);
        layout.setHgap(50);
        innerSexContainer.setLayout(layout);
        ButtonGroup sexChoice = new ButtonGroup();
        this.manButton.setFont(FONT_NORMAL);
        this.womanButton.setFont(FONT_NORMAL);
        sexChoice.add(this.manButton);
        sexChoice.add(this.womanButton);
        sexChoice.add(this.emptySexButton);
        innerSexContainer.add(this.manButton);
        innerSexContainer.add(this.womanButton);
        this.normalInitialize("<html>性别 <font color=\"red\">*</font></html>", innerSexContainer);
    }

    /**
     * 初始化学院下拉列表
     */
    private void initCollegeBox() {
        this.collegeList.setEditable(false);
        this.collegeList.setMaximumRowCount(5);
        this.collegeList.setFont(FONT_PLAIN);
        this.collegeList.setSelectedIndex(-1);
        this.normalInitialize("<html>学院 <font color=\"red\">*</font></html>", this.collegeList);
    }

    /**
     * 初始化爱好信息
     * 为学生爱好的显示提供专有面板，供子类实现显示逻辑
     */
    private void initFavorite() {
        this.favoriteInitialize();
        this.normalInitialize("<html>爱好  </html>", this.favoriteContent);
    }

    /**
     * 初始化按钮
     */
    private void initButton() {
        Box box = Box.createHorizontalBox();
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.leftButton.setFont(FONT_NORMAL);
        box.add(this.leftButton);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.rightButton.setFont(FONT_NORMAL);
        box.add(this.rightButton);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.centerContent.add(box);
        this.centerContent.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        this.leftButton.addActionListener(event -> FrameNormal.this.onClickLeftButton());
        this.rightButton.addActionListener(event -> FrameNormal.this.onClickRightButton());
    }

    /**
     * 初始化底部标签
     */
    private void initBottomLabel() {
        this.bottomLabel.setText("");
        this.bottomLabel.setFont(FONT_PLAIN);
        this.content.add(this.bottomLabel, BorderLayout.SOUTH);
    }

    // 学生爱好组件占位方法（子类实现/覆盖）

    /**
     * 学生爱好显示逻辑
     * (交给子类实现)
     */
    protected abstract void favoriteInitialize();

    /**
     * 清空学生爱好信息
     * (子类选择性实现)
     */
    protected void clearFavorite() {
    }

    /**
     * 从窗口获取学生爱好信息
     * (子类选择性实现)
     *
     * @return 学生爱好信息
     */
    protected List<String> accessFavorite() {
        return null;
    }

    /**
     * 将学生爱好信息显示到窗口
     * (子类选择性实现)
     *
     * @param favorites 学生爱好信息
     */
    protected void putFavorite(List<String> favorites) {
    }

    // 底部按钮功能占位方法（子类实现）

    /**
     * 左按钮点击时的回调函数
     * (交给子类实现)
     */
    protected abstract void onClickLeftButton();

    /**
     * 右按钮点击时的回调函数
     * (交给子类实现)
     */
    protected abstract void onClickRightButton();

    // 子类可调用实用方法

    /**
     * 冻结可编辑区域
     *
     * @param isFrozen true - 冻结; false - 解除冻结
     */
    protected final void frozen(boolean isFrozen) {
        this.idText.setEditable(!isFrozen);
        this.nameText.setEditable(!isFrozen);
        this.cityText.setEditable(!isFrozen);
        this.manButton.setEnabled(!isFrozen);
        this.womanButton.setEnabled(!isFrozen);
        this.emptySexButton.setSelected(true);
    }

    /**
     * 清空显示区域
     */
    protected final void clear() {
        this.idText.setText("");
        this.nameText.setText("");
        this.emptySexButton.setSelected(true);
        this.collegeList.setSelectedIndex(-1);
        this.cityText.setText("");
        this.clearFavorite();
    }

    /**
     * 将学生展示到窗口
     *
     * @param student 学生对象
     */
    protected final void putStudentToView(Student student) {
        if (student == null) {
            this.collegeList.removeAllItems();
            return;
        }
        this.clear();
        this.idText.setText(student.getId());
        this.nameText.setText(student.getName());
        this.putSex(student.getSex());
        this.collegeList.removeAllItems();
        this.collegeList.addItem(student.getCollege());
        this.cityText.setText(student.getCity());
        putFavorite(student.getFavorite());
    }

    /**
     * 从窗口获取学生信息
     *
     * @param ignore 是否忽略错误信息
     * @return 学生对象
     */
    protected final Student getStudentFromView(boolean ignore) {
        String id = this.idText.getText().trim();
        String name = this.nameText.getText().trim();
        String college = (String) this.collegeList.getSelectedItem();
        String city = this.cityText.getText().trim();
        String sex = this.accessSex();
        List<String> favorite = this.accessFavorite();
        Student student = null;
        if (isValidStudentInfo(id) && isValidStudentInfo(name) && isValidStudentInfo(sex) &&
                isValidStudentInfo(college) && isValidStudentInfo(city)) {
            try {
                student = new Student(id, name, sex, college, city, favorite);
            } catch (RuntimeException e) {
                e.printStackTrace();
                JOptionPane.showMessageDialog(this,
                        e.getMessage(),
                        "保存异常",
                        JOptionPane.ERROR_MESSAGE);
            }
        } else {
            if (!ignore) {
                JOptionPane.showMessageDialog(this,
                        "学生信息不符合要求！\n学生信息中不允许出现'/'、','、空格字符；\n标 * 为必填项；\n文本框内容不得多于20字符。",
                        "请完善信息",
                        JOptionPane.ERROR_MESSAGE);
            }
        }
        return student;
    }

    /**
     * 设置底部标签显示内容
     *
     * @param text 显示内容
     */
    protected final void setBottomLabelText(String text) {
        this.bottomLabel.setText(text);
    }

    // 本类辅助函数

    /**
     * 获取学生性别
     *
     * @return 学生性别
     */
    private String accessSex() {
        if (this.manButton.isSelected()) {
            return Student.SEX_MAN;
        } else if (this.womanButton.isSelected()) {
            return Student.SEX_WOMAN;
        }
        return null;
    }

    /**
     * 显示学生性别
     *
     * @param sex 学生性别
     */
    private void putSex(String sex) {
        if (Student.SEX_MAN.equals(sex)) {
            this.manButton.setSelected(true);
        } else if (Student.SEX_WOMAN.equals(sex)) {
            this.womanButton.setSelected(true);
        } else {
            this.emptySexButton.setSelected(true);
        }
    }

    /**
     * 判断文本信息是否完整
     *
     * @param text 文本信息
     * @return 文本信息是否完整
     */
    private static boolean isValidStudentInfo(String text) {
        return text != null && text.length() >= 1 && text.length() <= TEXT_MAX_SIZE && !text.contains(Student.FAVORITE_SEPARATOR)
                && !text.contains(Student.FIELD_SEPARATOR) && !text.contains(" ");
    }

}
