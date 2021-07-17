package punch.ui.controller;

import punch.db.Database;
import punch.user.User;

import java.sql.SQLException;

public class UserAccountController {

    Database db = Database.getInstance();

    public User login(String username, String password, String role) throws SQLException {
        User user = db.selectUser(username);
        System.out.println(user);
        System.out.println(user.getId());
        System.out.println(user.getName());
        String validPasswordMD5 = db.selectUserPasswordMd5(user.getId());
        String givenPasswordMD5 = User.md5Password(password);
        if (!validPasswordMD5.equals(givenPasswordMD5)) {
            throw new SQLException("密码不正确");
        }
        if (!role.equals(user.getRole())) {
            throw new SQLException("角色不正确");
        }
        return user;
    }

    public User signup(String username, String password, String role) throws SQLException {
        User user = new User(username, role);
        db.insertUser(user, password);
        return user;
    }

    public void clearDbCache() {
        db.clearCache();
    }

    public void dbReset() throws SQLException {
        db.reset();
    }
}
