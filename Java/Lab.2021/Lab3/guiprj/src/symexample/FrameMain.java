package symexample;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * 主窗口类
 *
 * @see FrameBase
 */
public class FrameMain extends FrameBase {

    private final JMenuBar menuBar; // 菜单栏
    private FrameRegister registerWindow;   // 学生注册类实例
    private FrameBrowse browseWindow;   // 学生查询类实例

    /**
     * 构造函数，用于初始化窗口属性
     */
    public FrameMain() {
        super("学生管理系统", WINDOW_LARGE);
        this.menuBar = new JMenuBar();
    }

    public static void main(String[] args) {
        new FrameMain().start();
    }

    // 交互逻辑覆盖

    /**
     * 实现窗口显示逻辑，显示窗口前被调用
     * 居中显示欢迎语，初始化菜单栏
     */
    @Override
    public void onStart() {
        super.onStart();
        JLabel label = new JLabel("欢迎使用学生管理系统！");
        label.setHorizontalAlignment(JLabel.CENTER);
        label.setFont(FONT_LARGE);
        this.content.add(label, BorderLayout.CENTER);
        this.initMenu();
    }

    /**
     * 询问是否退出系统
     *
     * @return 是否退出系统
     */
    @Override
    public boolean onFinish() {
        this.closeAllWindows();
        return JOptionPane.showConfirmDialog(this,
                "是否真要退出？",
                "退出系统",
                JOptionPane.YES_NO_OPTION) == JOptionPane.OK_OPTION;
    }

    // 辅助函数

    /**
     * 关闭所有窗口
     */
    private void closeAllWindows() {
        if (this.registerWindow != null && this.registerWindow.isVisible()) {
            this.registerWindow.finish();
            this.registerWindow = null;
        }
        if (this.browseWindow != null && this.browseWindow.isVisible()) {
            this.browseWindow.finish();
            this.browseWindow = null;
        }
    }

    // 组件初始化方法

    /**
     * 初始化菜单栏
     * 注册、查询、退出
     */
    private void initMenu() {
        this.setJMenuBar(menuBar);
        this.addMenu("注册", new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (FrameMain.this.registerWindow == null) {
                    FrameMain.this.registerWindow = new FrameRegister();
                    FrameMain.this.registerWindow.start();
                } else if (!FrameMain.this.registerWindow.isVisible()) {
                    FrameMain.this.registerWindow.refresh();
                } else if (FrameMain.this.registerWindow.getState() == Frame.ICONIFIED){
                    FrameMain.this.registerWindow.setExtendedState(Frame.NORMAL);
                    FrameMain.this.registerWindow.requestFocus();
                } else if (!FrameMain.this.registerWindow.isFocused()) {
                    FrameMain.this.registerWindow.requestFocus();
                }
            }
        });
        this.addMenu("查询", new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (FrameMain.this.browseWindow == null) {
                    FrameMain.this.browseWindow = new FrameBrowse();
                    FrameMain.this.browseWindow.start();
                } else if (!FrameMain.this.browseWindow.isVisible()) {
                    FrameMain.this.browseWindow.refresh();
                } else if (FrameMain.this.browseWindow.getState() == Frame.ICONIFIED){
                    FrameMain.this.browseWindow.setExtendedState(Frame.NORMAL);
                    FrameMain.this.browseWindow.requestFocus();
                } else if (!FrameMain.this.browseWindow.isFocused()) {
                    FrameMain.this.browseWindow.requestFocus();
                }
            }
        });
        this.addMenu("退出", event -> this.finish());
    }

    /**
     * 添加单个菜单
     *
     * @param menuName       菜单名
     * @param actionListener 监听点击
     */
    private void addMenu(String menuName, ActionListener actionListener) {
        JMenu menu = new JMenu(menuName);
        menu.setFont(FONT_NORMAL);
        this.menuBar.add(menu);
        JMenuItem item = new JMenuItem(menuName);
        item.setFont(FONT_PLAIN);
        menu.add(item);
        item.addActionListener(actionListener);
    }

}
