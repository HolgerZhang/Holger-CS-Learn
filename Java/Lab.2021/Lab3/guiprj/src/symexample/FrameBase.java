package symexample;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * 基础显示框架基类（抽象类）
 * 不可直接实例化，需要根据需求重写方法：
 * - protected void onStart();      实现窗口显示逻辑
 * - protected boolean onFinish();  窗口关闭时的操作
 *
 * @see javax.swing.JFrame
 */
public abstract class FrameBase extends JFrame {

    // 通用属性
    public static final Font FONT_LARGE = new Font("", Font.BOLD, 26);  // 大字体
    public static final Font FONT_NORMAL = new Font("", Font.BOLD, 18); // 标准字体
    public static final Font FONT_PLAIN = new Font("", Font.PLAIN, 16); // 普通字体
    public static final Dimension WINDOW_LARGE = new Dimension(1200, 800);  // 大窗口
    public static final Dimension WINDOW_SMALL = new Dimension(450, 730);   // 小窗口

    protected final Container content;    // 默认底层容器

    /**
     * 构造函数，用于初始化窗口属性
     *
     * @param title 窗口标题
     * @param size  窗口大小 WINDOW_SMALL | WINDOW_LARGE
     */
    protected FrameBase(String title, Dimension size) {
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
                FrameBase.this.finish();   // 调用 finish 方法关闭窗口
            }
        });
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

}
