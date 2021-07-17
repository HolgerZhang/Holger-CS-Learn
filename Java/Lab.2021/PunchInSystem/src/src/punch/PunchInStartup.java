package punch;


import punch.ui.controller.UserAccountController;
import punch.ui.frame.UserAccountFrame;

// 启动类
public class PunchInStartup {
    public static void main(String[] args) {
        new UserAccountFrame(new UserAccountController()).start();
    }


}
