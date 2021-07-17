package manager.ui;

import manager.account.Manager;
import manager.devices.SmartBand;
import manager.devices.SmartDeviceFactory;
import manager.devices.SmartWatch;
import manager.devices.ability.Localizable;
import manager.devices.base.SmartDevice;
import manager.ui.frame.ActivityBaseFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import java.util.List;


public class MainActivity extends ActivityBaseFrame {
    private static final String OVERALL = "设备总览";
    private final JMenuBar menuBar;
    private final Container center;
    private final JLabel titleLabel;
    private final JButton addBtn;
    private final JButton sceneBtn;
    private String scene;

    public MainActivity(Manager manager) {
        super("控制中心", WINDOW_SMALL, manager);
        menuBar = new JMenuBar();
        center = Box.createVerticalBox();
        titleLabel = new JLabel();
        addBtn = new JButton("添加设备");
        sceneBtn = new JButton("选择场景");
        scene = null;
    }

    private void initMenu() {
        this.setJMenuBar(menuBar);
        JMenu userMenu = new JMenu("用户");
        userMenu.setFont(FONT_NORMAL);
        this.menuBar.add(userMenu);
        JMenuItem logItem = new JMenuItem("日志");
        logItem.setFont(FONT_PLAIN);
        userMenu.add(logItem);
        logItem.addActionListener(this::catUserLog);
        userMenu.addSeparator();
        JMenuItem logoutItem = new JMenuItem("注销");
        logoutItem.setFont(FONT_PLAIN);
        userMenu.add(logoutItem);
        logoutItem.addActionListener(event -> this.finish());
        JMenu devMenu = new JMenu("设备");
        devMenu.setFont(FONT_NORMAL);
        this.menuBar.add(devMenu);
        JMenuItem addItem = new JMenuItem("添加设备");
        addItem.setFont(FONT_PLAIN);
        devMenu.add(addItem);
        addItem.addActionListener(this::newDevice);
        devMenu.addSeparator();
        JMenuItem sceneItem = new JMenuItem("选择场景");
        sceneItem.setFont(FONT_PLAIN);
        devMenu.add(sceneItem);
        sceneItem.addActionListener(this::changeScene);
    }

    @Override
    protected void onStart() {
        super.onStart();
        initMenu();
        JScrollPane scrollPane = new JScrollPane(center);
        scrollPane.getVerticalScrollBar().setUnitIncrement(30);
        scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        content.add(scrollPane, BorderLayout.CENTER);
        titleLabel.setHorizontalAlignment(JLabel.LEFT);
        titleLabel.setFont(FONT_PLAIN);
        this.content.add(titleLabel, BorderLayout.NORTH);
        initButtons();
        content.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH), BorderLayout.EAST);
        content.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH), BorderLayout.WEST);
    }

    private void initButtons() {
        Box box = Box.createHorizontalBox();
        box.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.addBtn.setFont(FONT_NORMAL);
        box.add(this.addBtn);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        this.sceneBtn.setFont(FONT_NORMAL);
        box.add(this.sceneBtn);
        box.add(Box.createHorizontalGlue());
        box.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH));
        box.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        this.content.add(box, BorderLayout.SOUTH);
        addBtn.addActionListener(this::newDevice);
        sceneBtn.addActionListener(this::changeScene);
    }

    @Override
    protected void onRefresh() {
        setNowScene(scene);
    }

    private void setNowScene(String scene) {
        center.removeAll();
        center.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
        try {
            for (long id : manager.sceneDevices(scene)) {
                SmartDevice dev = manager.findDev(id);
                center.add(createDeviceTag(dev));
                center.add(Box.createVerticalStrut(VERTICAL_STRUT_HEIGHT));
            }
        } catch (SQLException | IllegalStateException e) {
            e.printStackTrace();
        }
        this.scene = scene;
        if (scene == null) {
            scene = OVERALL;
        }
        titleLabel.setText("当前场景：" + scene);
    }

    private JPanel createDeviceTag(SmartDevice dev) {
        JPanel jpl = new JPanel();
        System.out.println(dev.getName());
        jpl.setLayout(new BorderLayout());
        JLabel dev_name_label = new JLabel(String.format("[%d] %s", dev.getDeviceID(), dev.getName()));
        dev_name_label.setFont(FONT_NORMAL);
        jpl.add(dev_name_label, BorderLayout.NORTH);
        JLabel dev_type_label = new JLabel(SmartDevice.getDeviceName(dev));
        dev_type_label.setFont(FONT_PLAIN);
        jpl.add(dev_type_label, BorderLayout.CENTER);
        JButton button = new JButton("管理");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                if (manager.managing) {
                    JOptionPane.showMessageDialog(MainActivity.this,
                            "有其他设备处于管理状态，请关闭后重试。",
                            "其他设备管理中",
                            JOptionPane.WARNING_MESSAGE);
                    return;
                }
                DeviceManageActivity activity = new DeviceManageActivity(dev, MainActivity.this);
                activity.start();
            }
        });
        jpl.add(button, BorderLayout.SOUTH);
        ImageIcon icon = new ImageIcon(SmartDeviceFactory.getDevicePhoto(SmartDevice.getDeviceName(dev)));
        JLabel iconLabel = new JLabel(icon);
        jpl.add(iconLabel, BorderLayout.WEST);
        return jpl;
    }

    @Override
    protected boolean onFinish() {
        manager.logout();
        return super.onFinish();
    }

    private void newDevice(ActionEvent event) {
        String type = (String) JOptionPane.showInputDialog(
                this,
                "请选择设备类型",
                "设备类型",
                JOptionPane.PLAIN_MESSAGE,
                null,
                SmartDeviceFactory.DEVICE_TYPES,
                SmartDeviceFactory.DEVICE_TYPES[0]);
        if (type == null) {
            cancelDialog();
            return;
        }
        String name = JOptionPane.showInputDialog(
                this,
                "输入设备名称",
                "My " + type);
        if (name == null) {
            cancelDialog();
            return;
        }
        name = name.trim();
        if (name.length() == 0) {
            JOptionPane.showMessageDialog(this,
                    "设备名不能为空。",
                    "设备名错误",
                    JOptionPane.ERROR_MESSAGE);
        }
        String position;
        boolean isNonLocation = type.equals(SmartBand.DEVICE_NAME) || type.equals(SmartWatch.DEVICE_NAME);
        if (isNonLocation) {
            position = null;
        } else {
            position = (String) JOptionPane.showInputDialog(
                    this,
                    "选择设备位置",
                    "设备位置",
                    JOptionPane.PLAIN_MESSAGE,
                    null,
                    Localizable.POSITIONS,
                    Localizable.POSITIONS[0]);
            if (position == null) {
                cancelDialog();
                return;
            }
        }
        SmartDevice device = SmartDeviceFactory.createDeviceAutomatically(name, type, position);
        try {
            manager.addDevice(device);
        } catch (SQLException | IllegalArgumentException | IllegalStateException e) {
            errorHandler(e, "设备插入");
            return;
        }
        String dev_info;
        if (isNonLocation) {
            dev_info = String.format("设备信息：%s (%s)，设备 ID = %06d", device.getName(), type, device.getDeviceID());
        } else {
            dev_info = String.format("设备信息：%s (%s)，设备 ID = %06d，位于 %s", device.getName(), type, device.getDeviceID(), position);
        }
        JOptionPane.showMessageDialog(this,
                dev_info,
                "设备添加成功",
                JOptionPane.INFORMATION_MESSAGE);
        refresh();
    }

    private void cancelDialog() {
        JOptionPane.showMessageDialog(this,
                "用户取消了操作。",
                "取消",
                JOptionPane.INFORMATION_MESSAGE);
    }

    private void catUserLog(ActionEvent event) {
        String log;
        String when = "用户日志";
        try {
            log = manager.getUserLog();
        } catch (SQLException | IllegalStateException e) {
            errorHandler(e, when);
            return;
        }
        JOptionPane.showMessageDialog(MainActivity.this,
                log,
                when,
                JOptionPane.PLAIN_MESSAGE);
    }

    private void changeScene(ActionEvent event) {
        String[] scenes;
        List<String> _scenes;
        try {
            _scenes = manager.listScene();
            _scenes.add(OVERALL);
            scenes = _scenes.toArray(new String[0]);
        } catch (SQLException | IllegalStateException e) {
            errorHandler(e, "场景");
            return;
        }
        String scene = (String) JOptionPane.showInputDialog(
                this,
                "选择设备场景",
                "选择场景",
                JOptionPane.PLAIN_MESSAGE,
                null,
                scenes,
                OVERALL);
        if (scene == null) {
            cancelDialog();
            return;
        }
        if (scene.equals(OVERALL)) scene = null;
        setNowScene(scene);
    }

}
