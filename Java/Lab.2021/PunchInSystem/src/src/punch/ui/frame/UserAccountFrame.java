package punch.ui.frame;

import punch.ui.controller.MainController;
import punch.ui.controller.UserAccountController;
import punch.user.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

// 用户登录UI模板
public class UserAccountFrame extends BasicTemplate {

    private final UserAccountController controller;

    private final JMenuBar menuBar; // 菜单栏
    private final JButton loginBtn;
    private final JButton signupBtn;
    private final JTextField username;
    private final JPasswordField password;
    private final JComboBox<String> role;
    private final Container centerContent;    // 中央信息面板


    public UserAccountFrame(UserAccountController controller) {
        super("欢迎使用个人自律打卡系统！请登录！", WINDOW_SMALLER);
        this.controller = controller;
        this.setResizable(false);    // 不可改变大小
        loginBtn = new JButton("登录");
        signupBtn = new JButton("注册");
        username = new JTextField();
        password = new JPasswordField();
        role = new JComboBox<>();
        centerContent = new JPanel();
        menuBar = new JMenuBar();
    }

    @Override
    protected void onStart() {
        centerContent.setLayout(new BoxLayout(centerContent, BoxLayout.PAGE_AXIS));
        content.add(centerContent, BorderLayout.CENTER);
        this.centerContent.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        this.centerContent.add(Box.createVerticalGlue());
        initMenu();
        initTextField("账号：", username);
        initTextField("密码：", password);
        initComboBox("角色：", role);
        initButton();
    }

    private void initMenu() {
        this.setJMenuBar(menuBar);
        JMenu menu = new JMenu("系统");
        this.menuBar.add(menu);
        JMenuItem clr = new JMenuItem("清空数据库缓存");
        menu.add(clr);
        clr.addActionListener(e -> {
            controller.clearDbCache();
            JOptionPane.showMessageDialog(UserAccountFrame.this,
                    "用户缓存清空成功。",
                    clr.getText(),
                    JOptionPane.INFORMATION_MESSAGE);
        });
        JMenuItem rm = new JMenuItem("抹掉所有数据");
        menu.add(rm);
        rm.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(UserAccountFrame.this,
                        "即将抹掉系统中所有数据，这会导致所有已保存的数据丢失且不可恢复，请谨慎考虑！\n" +
                                "请问是否执行？",
                        rm.getText(),
                        JOptionPane.YES_NO_OPTION,
                        JOptionPane.WARNING_MESSAGE)) {
                    try {
                        controller.dbReset();
                    } catch (SQLException err) {
                        UserAccountFrame.this.errorHandler(err, "抹掉数据");
                        return;
                    }
                    JOptionPane.showMessageDialog(UserAccountFrame.this,
                            "系统数据清除成功。",
                            rm.getText(),
                            JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        menu.addSeparator();
        JMenuItem quit = new JMenuItem("退出");
        menu.add(quit);
        quit.addActionListener(e -> finish());
    }

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

    private void initTextField(String labelString, JTextField textField) {
        textField.setFont(FONT_PLAIN);
        textField.setColumns(TEXT_MAX_SIZE);
        this.normalInitialize(labelString, textField);
    }

    private void initComboBox(String label, JComboBox<String> box) {
        box.setFont(FONT_PLAIN);
        box.setModel(new DefaultComboBoxModel<>(User.ROLES));
        box.setSelectedIndex(-1);
        this.normalInitialize(label, box);
    }

    private void initButton() {
        Box box = Box.createHorizontalBox();
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.signupBtn.setFont(FONT_NORMAL);
        box.add(this.signupBtn);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.loginBtn.setFont(FONT_NORMAL);
        box.add(this.loginBtn);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.centerContent.add(box);
        this.centerContent.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        ActionListener listener = new UserAccountButtonListener();
        this.loginBtn.addActionListener(listener);
        this.signupBtn.addActionListener(listener);
    }

    private boolean isInvalidNamePassword(String name, String passwd, String role) {
        if (name.length() > 60 || name.length() <= 3) {
            JOptionPane.showMessageDialog(this,
                    "用户名长度需大于3字符小于60字符。",
                    "用户名不合法",
                    JOptionPane.ERROR_MESSAGE);
            return true;
        }
        if (passwd.length() > 20 || passwd.length() < 6) {
            JOptionPane.showMessageDialog(this,
                    "密码长度需大于等于6字符小于20字符。",
                    "密码不合法",
                    JOptionPane.ERROR_MESSAGE);
            return true;
        }
        if (role == null || role.length() == 0) {
            JOptionPane.showMessageDialog(this,
                    "未选择用户角色。",
                    "未选择角色",
                    JOptionPane.ERROR_MESSAGE);
            return true;
        }
        return false;
    }

    public class UserAccountButtonListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            String username = UserAccountFrame.this.username.getText().trim();
            String password = String.valueOf(UserAccountFrame.this.password.getPassword()).trim();
            String role = (String) UserAccountFrame.this.role.getSelectedItem();
            if (isInvalidNamePassword(username, password, role)) return;
            User user;
            if (e.getSource() instanceof JButton) {
                try {
                    if (e.getSource() == UserAccountFrame.this.loginBtn)
                        user = UserAccountFrame.this.controller.login(username, password, role);
                    else if (e.getSource() == UserAccountFrame.this.signupBtn) {
                        user = UserAccountFrame.this.controller.signup(username, password, role);
                        JOptionPane.showMessageDialog(UserAccountFrame.this,
                                "注册成功，将以该身份登录。",
                                "用户注册成功",
                                JOptionPane.INFORMATION_MESSAGE);
                    }
                    else return;
                    new MainFrame(new MainController(user)).start();
                    UserAccountFrame.this.finish();
                } catch (SQLException err) {
                    errorHandler(err, ((JButton) e.getSource()).getText());
                }
            }
        }
    }

}
