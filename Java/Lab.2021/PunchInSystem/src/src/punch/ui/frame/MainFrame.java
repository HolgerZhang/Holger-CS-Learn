package punch.ui.frame;

import punch.activity.ActivityFactory;
import punch.activity.BasicActivity;
import punch.ui.component.ActivityViewer;
import punch.ui.controller.MainController;
import punch.user.User;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.sql.SQLException;
import java.text.DateFormat;
import java.util.*;

public class MainFrame extends BasicTemplate {
    private final MainController controller;
    private final Container center;
    Set<Long> ids;
    String showType, showMode;

    public MainFrame(MainController controller) {
        super("活动列表", WINDOW_MIDDLE);
        this.controller = controller;
        center = new JPanel();
        center.setLayout(new GridLayout(0 ,2, 15, 15));
        ids = new HashSet<>();
        showType = "ALL";
        showMode = "ALL";
    }

    @Override
    protected void onStart() {
        super.onStart();
        JPanel menu = new JPanel();
        JButton addButton = new JButton("新增活动");
        addButton.setIcon(new ImageIcon(System.getProperty("user.dir") + File.separator + "data/img/add.png"));
        addButton.setContentAreaFilled(false);
        addButton.setFocusPainted(false);
        addButton.setRolloverIcon(new ImageIcon(System.getProperty("user.dir") + File.separator + "data/img/add_on.png"));
        addButton.addActionListener(e -> addActivity());
        menu.add(addButton);
        JButton filterButton = new JButton("筛选活动");
        filterButton.setIcon(new ImageIcon(System.getProperty("user.dir") + File.separator + "data/img/filter.png"));
        filterButton.setContentAreaFilled(false);
        filterButton.setFocusPainted(false);
        filterButton.setRolloverIcon(new ImageIcon(System.getProperty("user.dir") + File.separator + "data/img/filter_on.png"));
        filterButton.addActionListener(e -> filterActivity());
        menu.add(filterButton);
        JButton visibleButton = new JButton("可见范围");
        visibleButton.setIcon(new ImageIcon(System.getProperty("user.dir") + File.separator + "data/img/visible.png"));
        visibleButton.setContentAreaFilled(false);
        visibleButton.setFocusPainted(false);
        visibleButton.setRolloverIcon(new ImageIcon(System.getProperty("user.dir") + File.separator + "data/img/visible_on.png"));
        visibleButton.addActionListener(e -> visibleActivity());
        menu.add(visibleButton);
        JButton logButton = new JButton("用户日志");
        logButton.setIcon(new ImageIcon(System.getProperty("user.dir") + File.separator + "data/img/log.png"));
        logButton.setContentAreaFilled(false);
        logButton.setFocusPainted(false);
        logButton.setRolloverIcon(new ImageIcon(System.getProperty("user.dir") + File.separator + "data/img/log_on.png"));
        logButton.addActionListener(e -> showUserLog());
        menu.add(logButton);
        content.add(menu, BorderLayout.NORTH);
        JScrollPane scrollPane = new JScrollPane(center);
        scrollPane.getVerticalScrollBar().setUnitIncrement(30);
        scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        content.add(scrollPane, BorderLayout.CENTER);
        content.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH), BorderLayout.EAST);
        content.add(Box.createHorizontalStrut(HORIZONTAL_STRUT_WIDTH), BorderLayout.WEST);
    }

    @Override
    protected void onRefresh() {
        center.removeAll();
        center.repaint();
        setShowActivities(null, null);
        if (ids.isEmpty()) {
            center.add(new JLabel("还没有活动，点击“新增活动”以添加相关活动。"));
            return;
        }
        for (long id : ids) {
            ActivityViewer viewer = new ActivityViewer(this, controller.getActivity(id), controller.getActivityMode(id));
            center.add(viewer);
        }
    }

    public void setShowActivities(String type, String mode) {
        ids.clear();
        if (type != null) showType = type;
        if (mode != null) showMode = mode;
        for (long id : controller.listActivities()) {
            if ((showType.equals("ALL") || controller.getActivity(id).getType().equals(showType)) &&
                    (showMode.equals("ALL") || controller.getActivityMode(id).equals(showMode))) {
                ids.add(id);
            }
        }
    }

    public MainController getController() {
        return controller;
    }

    private void addActivity() {
        String type = (String) JOptionPane.showInputDialog(
                this,
                "请选择活动类型：",
                "活动类型",
                JOptionPane.PLAIN_MESSAGE,
                null,
                ActivityFactory.ACTIVITY_TYPES,
                ActivityFactory.ACTIVITY_TYPES[0]
        );
        if (type == null) {
            cancelDialog();
            return;
        }
        String name = JOptionPane.showInputDialog(
                this,
                "输入活动名称",
                type + " @ " + DateFormat.getInstance().format(new Date()));
        if (name == null) {
            cancelDialog();
            return;
        }
        String description = JOptionPane.showInputDialog(
                this,
                "输入活动内容",
                "    创建于 " + DateFormat.getInstance().format(new Date()));
        if (description == null) {
            cancelDialog();
            return;
        }
        BasicActivity activity = ActivityFactory.createSimpleActivity(type, name, description);
        Map<Long, String> grantUsers = null;
        if (controller.getUserRole().equals(User.ADMIN_ROLE)) {
            grantUsers = new HashMap<>();
            int count = 0;
            while (JOptionPane.showConfirmDialog(this,
                    String.format("是否还需授予其他人权限？（已授予人数:%d）", count),
                    "授予他人权限",
                    JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
                String username = JOptionPane.showInputDialog(this, "请输入对方用户名：");
                if (username == null) {
                    cancelDialog();
                    continue;
                }
                long id;
                try {
                    id = controller.getUserId(username);
                } catch (SQLException e) {
                    errorHandler(e, "授予他人权限");
                    continue;
                }
                String mode = (String) JOptionPane.showInputDialog(
                        this,
                        String.format("请选择要授予 %s 的权限：", username),
                        "授予他人权限",
                        JOptionPane.PLAIN_MESSAGE,
                        null,
                        BasicActivity.A_MODES,
                        BasicActivity.A_MODES[0]
                );
                if (mode == null) {
                    cancelDialog();
                    continue;
                }
                grantUsers.put(id, mode);
                count++;
            }
        }
        try {
            controller.newActivity(activity, grantUsers);
        } catch (SQLException e) {
            errorHandler(e, "新建活动");
        }
        refresh();
    }

    private void filterActivity() {
        String type = (String) JOptionPane.showInputDialog(
                this,
                "请选择活动类型：",
                "活动类型",
                JOptionPane.PLAIN_MESSAGE,
                null,
                ActivityFactory.ACTIVITY_TYPES_WITH_ALL,
                ActivityFactory.ACTIVITY_TYPES_WITH_ALL[0]
        );
        if (type == null) {
            cancelDialog();
            return;
        }
        setShowActivities(type, null);
        refresh();
    }

    private void visibleActivity() {
        // A_MODES_WITH_ALL
        String mode = (String) JOptionPane.showInputDialog(
                this,
                "请选择可见范围：",
                "可见范围",
                JOptionPane.PLAIN_MESSAGE,
                null,
                BasicActivity.A_MODES_WITH_ALL,
                BasicActivity.A_MODES_WITH_ALL[0]
        );
        if (mode == null) {
            cancelDialog();
            return;
        }
        setShowActivities(null, mode);
        refresh();
    }

    private void showUserLog() {
        String log;
        try {
            log = controller.getLog();
        } catch (SQLException | IllegalStateException e) {
            errorHandler(e, "用户日志");
            return;
        }
        if (log.isEmpty()) log = "无日志";
        JOptionPane.showMessageDialog(this,
                log, "用户日志",
                JOptionPane.PLAIN_MESSAGE);
    }
}
