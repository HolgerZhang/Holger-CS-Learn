package punch.ui.frame;

import punch.activity.BasicActivity;
import punch.ui.controller.ActivityDetailController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class ActivityDetailFrame extends BasicTemplate {

    private final Container bottomButtonsContainer;
    private final JTextArea centerInfo;
    private final MainFrame before;
    ActivityDetailController controller;

    public ActivityDetailFrame(ActivityDetailController controller, MainFrame before) {
        super("活动管理", WINDOW_SMALL);
        this.controller = controller;
        bottomButtonsContainer = new JPanel();
        centerInfo = new JTextArea();
        this.before = before;
    }

    @Override
    protected void onStart() {
        super.onStart();
        String title = controller.getTitle();
        setTitle("管理：" + title);
        JLabel activity_name_label = new JLabel(String.format("<html>活动 %s</html>", title), JLabel.CENTER);
        activity_name_label.setFont(FONT_LARGE);
        content.add(activity_name_label, BorderLayout.NORTH);
        centerInfo.setEditable(false);
        centerInfo.setFont(FONT_NORMAL);
        content.add(centerInfo, BorderLayout.CENTER);
        content.add(bottomButtonsContainer, BorderLayout.SOUTH);
        if (controller.getMode().equals(BasicActivity.VISIBLE_A_MODE)) return;
        initBottomButtonsContainer();
    }

    private void initBottomButtonsContainer() {
        bottomButtonsContainer.setLayout(new GridLayout(2, 0, 15, 15));
        JButton punch = new JButton("打卡");
        punch.setFont(FONT_PLAIN);
        bottomButtonsContainer.add(punch);
        punch.setEnabled(controller.canPunchIn());
        punch.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                Integer i = null;
                if (controller.isMoneySavingActivity()) {
                    String temp = JOptionPane.showInputDialog(ActivityDetailFrame.this,
                            "请输入消费金额：",
                            punch.getText(),
                            JOptionPane.INFORMATION_MESSAGE);
                    if (temp == null || temp.length() == 0) {
                        cancelDialog();
                        return;
                    }
                    i = Integer.parseInt(temp);
                }
                try {
                    controller.punchIn(i);
                } catch (SQLException | IllegalStateException e) {
                    ActivityDetailFrame.this.errorHandler(e, punch.getText());
                }
                ActivityDetailFrame.this.refresh();
                punch.setEnabled(controller.canPunchIn());
            }
        });

        JButton logs = new JButton("活动日志");
        logs.setFont(FONT_PLAIN);
        bottomButtonsContainer.add(logs);
        logs.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                String log;
                try {
                    log = controller.getLog();
                } catch (SQLException | IllegalStateException e) {
                    errorHandler(e, logs.getText());
                    return;
                }
                if (log.isEmpty()) log = "无日志";
                JOptionPane.showMessageDialog(ActivityDetailFrame.this,
                        log,
                        String.format("活动 %s 日志", ActivityDetailFrame.this.getTitle()),
                        JOptionPane.PLAIN_MESSAGE);
            }
        });

        if (controller.getMode().equals(BasicActivity.EDITABLE_A_MODE)) return;

        JButton desc = new JButton("修改详情");
        desc.setFont(FONT_PLAIN);
        bottomButtonsContainer.add(desc);
        desc.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                String temp = JOptionPane.showInputDialog(ActivityDetailFrame.this,
                        "请输入活动详情：",
                        desc.getText(),
                        JOptionPane.INFORMATION_MESSAGE);
                if (temp == null || temp.length() == 0) {
                    cancelDialog();
                    return;
                }
                try {
                    controller.setDescription(temp);
                } catch (SQLException e) {
                    ActivityDetailFrame.this.errorHandler(e, desc.getText());
                }
                ActivityDetailFrame.this.refresh();
                before.refresh();
            }
        });

        JButton delete = new JButton("删除活动");
        delete.setFont(FONT_PLAIN);
        bottomButtonsContainer.add(delete);
        delete.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                try {
                    controller.deleteActivity();
                } catch (SQLException e) {
                    ActivityDetailFrame.this.errorHandler(e, delete.getText());
                    return;
                }
                JOptionPane.showMessageDialog(ActivityDetailFrame.this,
                        "活动成功删除。",
                        delete.getText(),
                        JOptionPane.WARNING_MESSAGE);
                ActivityDetailFrame.this.finish();
                before.refresh();
            }
        });

        if (controller.isMoneySavingActivity()) {
            JButton setAim = new JButton("设置目标");
            setAim.setFont(FONT_PLAIN);
            bottomButtonsContainer.add(setAim);
            setAim.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    String temp = JOptionPane.showInputDialog(ActivityDetailFrame.this,
                            "请输入目标金额：",
                            setAim.getText(),
                            JOptionPane.INFORMATION_MESSAGE);
                    if (temp == null || temp.length() == 0) {
                        cancelDialog();
                        return;
                    }
                    int i = Integer.parseInt(temp);
                    try {
                        controller.setMoneyAim(i);
                    } catch (SQLException e) {
                        errorHandler(e, setAim.getText());
                    }
                    ActivityDetailFrame.this.refresh();
                    punch.setEnabled(controller.canPunchIn());
                }
            });
        } else if (controller.isRepeatActivity()) {
            JButton setCount = new JButton("设置次数");
            setCount.setFont(FONT_PLAIN);
            bottomButtonsContainer.add(setCount);
            setCount.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    String temp = JOptionPane.showInputDialog(ActivityDetailFrame.this,
                            "请输入目标次数：",
                            setCount.getText(),
                            JOptionPane.INFORMATION_MESSAGE);
                    if (temp == null || temp.length() == 0) {
                        cancelDialog();
                        return;
                    }
                    int i = Integer.parseInt(temp);
                    try {
                        controller.setRepeatCount(i);
                    } catch (SQLException e) {
                        errorHandler(e, setCount.getText());
                    }
                    ActivityDetailFrame.this.refresh();
                    punch.setEnabled(controller.canPunchIn());
                }
            });
        } else if (controller.isZenModeActivity()) {
            JButton setLasting = new JButton("设置时长");
            setLasting.setFont(FONT_PLAIN);
            bottomButtonsContainer.add(setLasting);
            setLasting.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    String temp = JOptionPane.showInputDialog(ActivityDetailFrame.this,
                            "请输入禅定模式持续时长：",
                            setLasting.getText(),
                            JOptionPane.INFORMATION_MESSAGE);
                    if (temp == null || temp.length() == 0) {
                        cancelDialog();
                        return;
                    }
                    int i = Integer.parseInt(temp);
                    try {
                        controller.setZenLasting(i);
                    } catch (SQLException e) {
                        errorHandler(e, setLasting.getText());
                    }
                    ActivityDetailFrame.this.refresh();
                    punch.setEnabled(controller.canPunchIn());
                }
            });
        }
    }

    @Override
    protected void onRefresh() {
        centerInfo.setText(String.join("\n", controller.getDetail()));
    }

}
