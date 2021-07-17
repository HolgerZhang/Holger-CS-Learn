package manager.ui;

import manager.account.Manager;
import manager.account.User;
import manager.db.Database;
import manager.ui.frame.UserAccountFrame;

import javax.swing.*;
import java.sql.SQLException;

public class SignInActivity extends UserAccountFrame {

    protected SignInActivity(Manager manager) {
        super("用户登录", manager, "登录");
    }

    @Override
    protected void onClickMainButton() {
        if (manager.isLogin()) {
            JOptionPane.showMessageDialog(this,
                    "已经登录系统，请勿重复登录。",
                    "已经登录",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        String name = username.getText();
        String passwd = String.valueOf(password.getPassword());
        if (isInvalidNamePassword(name, passwd)) return;
        String md5;
        try {
            md5 = Database.selectUserPasswordMd5(name);
        } catch (SQLException e) {
            errorHandler(e, "数据库");
            return;
        }
        if (md5 == null) {
            JOptionPane.showMessageDialog(this,
                    "用户不存在，请检查用户名。",
                    "未知用户",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!User.md5Password(passwd).equals(md5)) {
            JOptionPane.showMessageDialog(this,
                    "密码错误，请检查。",
                    "密码错误",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        manager.login(new User(name));
        this.finish();
        new MainActivity(manager).start();
    }
}
