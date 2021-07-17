package punch.ui.frame;

import punch.user.User;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;

// 基础UI框架模板
public abstract class BasicTemplate extends JFrame {
    // 通用属性
    public static final Font FONT_LARGE = new Font("", Font.BOLD, 26);  // 大字体
    public static final Font FONT_NORMAL = new Font("", Font.BOLD, 18); // 标准字体
    public static final Font FONT_PLAIN = new Font("", Font.PLAIN, 16); // 普通字体
    public static final Dimension WINDOW_LARGE = new Dimension(1200, 800);  // 大窗口
    public static final Dimension WINDOW_MIDDLE = new Dimension(1200, 600);   // 种窗口
    public static final Dimension WINDOW_SMALL = new Dimension(500, 350);   // 小窗口
    public static final Dimension WINDOW_SMALLER = new Dimension(500, 450);   // 小窗口
    public static final int TEXT_MAX_SIZE = 20; // 文本框最大大小
    public static final int HORIZONTAL_STRUT_WIDTH = 40;   // 水平支柱大小
    public static final int VERTICAL_STRUT_HEIGHT = 50;    // 垂直支柱大小

    protected final Container content;    // 默认底层容器

    protected BasicTemplate(String title, Dimension size) {
        super(title);
        try {   // 保持与操作系统原生UI一致的感官
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }
        this.content = this.getContentPane();
        this.setSize(size);
        this.setLocationRelativeTo(null);    // 居中显示
        // 点击 X 按钮时不做任何事情
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        // 监听窗口关闭事件（点击 X 按钮时）
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                BasicTemplate.this.finish();   // 调用 finish 方法关闭窗口
            }
        });
        try {
            Image image = ImageIO.read(new File(System.getProperty("user.dir") + File.separator + "data/img/icon.jpeg"));
            this.setIconImage(image);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 交互逻辑公共方法

    /**
     * 显示窗口，构造窗口后显式调用
     * 不得重写，如需修改窗口显示需要重写 onStart 方法
     */
    public final void start() {
        this.onStart();
        this.refresh();
    }

    /**
     * 关闭窗口，窗口被关闭时自动触发
     * 不得重写，窗口被关闭时如需修改逻辑需要重写 onFinish 方法
     */
    public final void finish() {
        if (this.onFinish()) {
            this.dispose();
        }
    }

    /**
     * 刷新显示区域的内容
     * 不得重写，如需修改刷新显示区域的内容的逻辑需要重写 onRefresh 方法
     */
    public final void refresh() {
        this.onRefresh();
        this.setVisible(true);
    }

    // 交互逻辑子类覆盖方法

    /**
     * 实现窗口显示逻辑，显示窗口前被调用
     */
    protected void onStart() {
        this.content.setLayout(new BorderLayout());
    }

    /**
     * 窗口关闭时的操作，关闭窗口前被调用
     * 默认不做任何操作，返回 true
     *
     * @return true - 窗口退出; false - 窗口不退出
     */
    protected boolean onFinish() {
        return true;
    }

    /**
     * 刷新显示区域的内容
     */
    protected void onRefresh() {
    }

    protected <ErrType extends Throwable> void errorHandler(ErrType err, String when) {
        err.printStackTrace();
        JOptionPane.showMessageDialog(this,
                err.getClass().getName() + ": " + err.getMessage(),
                when + "错误",
                JOptionPane.ERROR_MESSAGE);
    }

    protected void cancelDialog() {
        JOptionPane.showMessageDialog(this,
                "用户取消了操作。",
                "取消",
                JOptionPane.INFORMATION_MESSAGE);
    }

}
