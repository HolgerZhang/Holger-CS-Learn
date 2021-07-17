package manager.ui.frame;

import manager.account.Manager;

import javax.swing.*;
import java.awt.*;

public abstract class UserAccountFrame extends ActivityBaseFrame {

    protected final JButton mainBtn;
    protected final JButton clearBtn;
    protected final JTextField username;
    protected final JPasswordField password;
    protected final Container centerContent;    // 中央信息面板


    protected UserAccountFrame(String title, Manager manager, String label) {
        super(title, WINDOW_SMALLER, manager);
        this.setResizable(false);    // 不可改变大小
        mainBtn = new JButton(label);
        clearBtn = new JButton("清空");
        username = new JTextField();
        password = new JPasswordField();
        centerContent = new JPanel();
    }

    @Override
    protected void onStart() {
        centerContent.setLayout(new BoxLayout(centerContent, BoxLayout.PAGE_AXIS));
        content.add(centerContent, BorderLayout.CENTER);
        this.centerContent.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        this.centerContent.add(Box.createVerticalGlue());
        initNowPosition();
        initTextField("账号：", username);
        initTextField("密码：", password);
        initButton();
    }

    private void initNowPosition() {
        JLabel titleLabel = new JLabel("当前位置：" + this.getTitle());
        titleLabel.setHorizontalAlignment(JLabel.LEFT);
        titleLabel.setFont(FONT_PLAIN);
        this.content.add(titleLabel, BorderLayout.NORTH);
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

    private void initButton() {
        Box box = Box.createHorizontalBox();
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.clearBtn.setFont(FONT_NORMAL);
        box.add(this.clearBtn);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.mainBtn.setFont(FONT_NORMAL);
        box.add(this.mainBtn);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.centerContent.add(box);
        this.centerContent.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        this.mainBtn.addActionListener(event -> onClickMainButton());
        this.clearBtn.addActionListener(event -> onClickClearButton());
    }

    private void onClickClearButton() {
        username.setText("");
        password.setText("");
    }

    protected abstract void onClickMainButton();

    protected boolean isInvalidNamePassword(String name, String passwd) {
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
        return false;
    }
}
