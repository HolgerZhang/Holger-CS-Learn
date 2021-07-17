package manager.ui;

import manager.account.Manager;
import manager.ui.frame.UserAccountFrame;

import javax.swing.*;
import java.sql.SQLException;

public class SignUpActivity extends UserAccountFrame {

    protected SignUpActivity(Manager manager) {
        super("用户注册", manager, "注册");
    }

    @Override
    protected void onClickMainButton() {
        String name = username.getText();
        String passwd = String.valueOf(password.getPassword());
        if (isInvalidNamePassword(name, passwd)) return;
        try {
            manager.register(name, passwd);
        } catch (SQLException | IllegalArgumentException e) {
            errorHandler(e, "注册");
            return;
        }
        JOptionPane.showMessageDialog(this,
                "注册成功，请登录。",
                "用户注册成功",
                JOptionPane.INFORMATION_MESSAGE);
        this.finish();
    }

}
