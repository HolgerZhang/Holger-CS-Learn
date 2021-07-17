package manager.ui;

import manager.account.Manager;
import manager.ui.frame.ActivityBaseFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class WelcomeActivity extends ActivityBaseFrame {
    public static final String LOGIN = "登录";
    public static final String REG = "注册";
    private final JMenuBar menuBar; // 菜单栏
    JButton signIn;
    JButton signUp;

    public WelcomeActivity(Manager manager) {
        super("欢迎使用智能设备统一管理系统！", WINDOW_LARGE, manager);
        signIn = new JButton(LOGIN);
        signUp = new JButton(REG);
        menuBar = new JMenuBar();
    }

    public static void main(String[] args) {
        new WelcomeActivity(new Manager()).start();
    }

    @Override
    protected void onStart() {
        super.onStart();
        JLabel centerLabel = new JLabel("欢迎使用智能设备统一管理系统！");
        centerLabel.setFont(FONT_LARGE);
        centerLabel.setHorizontalAlignment(JLabel.CENTER);
        content.add(centerLabel, BorderLayout.CENTER);
        initButton();
    }

    private void initButton() {
        Box box = Box.createHorizontalBox();
        box.add(Box.createVerticalStrut(2 * VERTICAL_STRUT_HEIGHT));
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.signIn.setFont(FONT_NORMAL);
        box.add(this.signIn);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.signUp.setFont(FONT_NORMAL);
        box.add(this.signUp);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        box.add(Box.createVerticalStrut(3 * VERTICAL_STRUT_HEIGHT));
        this.content.add(box, BorderLayout.SOUTH);
        signIn.addActionListener(this::doSignIn);
        signUp.addActionListener(this::doSignUp);
        // menu
        this.setJMenuBar(menuBar);
        JMenu menu = new JMenu("用户");
        menu.setFont(FONT_NORMAL);
        this.menuBar.add(menu);
        JMenuItem loginItem = new JMenuItem(LOGIN);
        loginItem.setFont(FONT_PLAIN);
        menu.add(loginItem);
        loginItem.addActionListener(this::doSignIn);
        JMenuItem regItem = new JMenuItem(REG);
        regItem.setFont(FONT_PLAIN);
        menu.add(regItem);
        regItem.addActionListener(this::doSignUp);
        JMenu sys = new JMenu("系统");
        sys.setFont(FONT_NORMAL);
        this.menuBar.add(sys);
        JMenuItem clr = new JMenuItem("清空缓存");
        clr.setFont(FONT_PLAIN);
        sys.add(clr);
        clr.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                manager.clearCache();
                JOptionPane.showMessageDialog(WelcomeActivity.this,
                        "用户缓存清空成功。",
                        clr.getText(),
                        JOptionPane.INFORMATION_MESSAGE);
            }
        });
        JMenuItem rm = new JMenuItem("抹掉所有数据");
        rm.setFont(FONT_PLAIN);
        sys.add(rm);
        rm.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(WelcomeActivity.this,
                        "即将抹掉系统中所有数据，这会导致所有已保存的数据丢失且不可恢复，请谨慎考虑！\n" +
                                "请问是否执行？",
                        rm.getText(),
                        JOptionPane.YES_NO_OPTION,
                        JOptionPane.WARNING_MESSAGE)) {
                    try {
                        manager.reset();
                    } catch (SQLException | IllegalStateException e) {
                        WelcomeActivity.this.errorHandler(e, "抹掉数据");
                        return;
                    }
                    JOptionPane.showMessageDialog(WelcomeActivity.this,
                            "系统数据清除成功。",
                            rm.getText(),
                            JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        sys.addSeparator();
        JMenuItem quitItem = new JMenuItem("退出");
        quitItem.setFont(FONT_PLAIN);
        sys.add(quitItem);
        quitItem.addActionListener(event -> this.finish());
    }


    private void doSignIn(ActionEvent event) {
        if (manager.isLogin()) {
            JOptionPane.showMessageDialog(WelcomeActivity.this,
                    "已经登录系统，如需更换用户请先注销。",
                    "已经登录",
                    JOptionPane.ERROR_MESSAGE);
        } else {
            new SignInActivity(manager).start();
        }
    }

    private void doSignUp(ActionEvent event) {
        new SignUpActivity(manager).start();
    }
}
