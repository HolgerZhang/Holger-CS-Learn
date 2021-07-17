package manager.ui;

import manager.devices.DeskLamp;
import manager.devices.Fridge;
import manager.devices.SmartDeviceFactory;
import manager.devices.ability.*;
import manager.devices.base.HouseholdDevice;
import manager.devices.base.KitchenAppliance;
import manager.devices.base.Lighting;
import manager.devices.base.SmartDevice;
import manager.ui.frame.ActivityBaseFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.List;

public class DeviceManageActivity extends ActivityBaseFrame {

    private final SmartDevice dev;
    private final Container bottomButtonsContainer;
    private final MainActivity activity;
    private final JTextArea centerInfo;
    private final List<String> devInfo;

    protected DeviceManageActivity(SmartDevice device, MainActivity activity) {
        super(device.getName(), WINDOW_SMALLER, activity.getManager());
        dev = device;
        manager.managing = true;
        this.activity = activity;
        bottomButtonsContainer = new JPanel();
        centerInfo = new JTextArea();
        devInfo = new LinkedList<>();
    }

    @Override
    protected void onStart() {
        super.onStart();
        JLabel dev_name_label = new JLabel(String.format("[%d] %s", dev.getDeviceID(), dev.getName()), JLabel.CENTER);
        dev_name_label.setFont(FONT_LARGE);
        content.add(dev_name_label, BorderLayout.NORTH);
        ImageIcon icon = new ImageIcon(SmartDeviceFactory.getDevicePhoto(SmartDevice.getDeviceName(dev)));
        JLabel iconLabel = new JLabel(icon);
        centerInfo.setEditable(false);
        centerInfo.setFont(FONT_NORMAL);
        content.add(iconLabel, BorderLayout.WEST);
        content.add(centerInfo, BorderLayout.CENTER);
        content.add(bottomButtonsContainer, BorderLayout.SOUTH);
        initBottomButtonsContainer();
    }

    private void initBottomButtonsContainer() {
        bottomButtonsContainer.setLayout(new GridLayout(2, 0, 15, 15));
        JButton delete = new JButton("删除设备");
        delete.setFont(FONT_PLAIN);
        bottomButtonsContainer.add(delete);
        delete.addActionListener(this::deleteDevice);
        JButton logs = new JButton("设备日志");
        logs.setFont(FONT_PLAIN);
        bottomButtonsContainer.add(logs);
        logs.addActionListener(this::showDeviceLog);
        initDeviceFeatureFunctionsButtons();
    }

    private void initDeviceFeatureFunctionsButtons() {
        if (dev instanceof RunningAbility) {
            RunningAbility runDev = (RunningAbility) dev;
            JButton running = new JButton(runDev.isRunning() ? "结束跑步" : "开始跑步");
            running.setFont(FONT_PLAIN);
            bottomButtonsContainer.add(running);
            running.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    try {
                        if (runDev.isRunning()) {
                            double time = runDev.stopRunning();
                            running.setText("开始跑步");
                            manager.addDeviceLog(dev.getDeviceID(), "结束跑步");
                            JOptionPane.showMessageDialog(DeviceManageActivity.this,
                                    "本次跑步共用 " + time + "秒。",
                                    "跑步结束",
                                    JOptionPane.PLAIN_MESSAGE);
                        } else {
                            runDev.startRunning();
                            running.setText("结束跑步");
                            manager.addDeviceLog(dev.getDeviceID(), "开始跑步");
                        }
                    } catch (SQLException | IllegalStateException e) {
                        DeviceManageActivity.this.errorHandler(e, running.getText());
                        return;
                    }
                    DeviceManageActivity.this.refresh();
                }
            });
        }
        if (dev instanceof StepCountable) {
            StepCountable s = (StepCountable) dev;
            JButton clearStep = new JButton("清除步数");
            clearStep.setFont(FONT_PLAIN);
            bottomButtonsContainer.add(clearStep);
            clearStep.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    s.resetStepCounter();
                    try {
                        manager.addDeviceLog(dev.getDeviceID(), "计步器重置");
                    } catch (SQLException | IllegalStateException e) {
                        DeviceManageActivity.this.errorHandler(e, clearStep.getText());
                        return;
                    }
                    DeviceManageActivity.this.refresh();
                }
            });
        }
        if (dev instanceof Enjoyable) {
            Enjoyable en = (Enjoyable) dev;
            JButton setMusic = new JButton("设置音乐");
            JButton play = new JButton(en.isPlayingMusic() ? "停止音乐" : "播放音乐");
            setMusic.setFont(FONT_PLAIN);
            play.setFont(FONT_PLAIN);
            bottomButtonsContainer.add(setMusic);
            bottomButtonsContainer.add(play);
            setMusic.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    String music = JOptionPane.showInputDialog(DeviceManageActivity.this,
                            "请输入音乐名：",
                            setMusic.getText(),
                            JOptionPane.PLAIN_MESSAGE);
                    if (music != null && music.trim().length() != 0) {
                        en.setMusic(music);
                        try {
                            manager.addDeviceLog(dev.getDeviceID(), "设置音乐" + music);
                        } catch (SQLException | IllegalStateException e) {
                            DeviceManageActivity.this.errorHandler(e, setMusic.getText());
                            return;
                        }
                        DeviceManageActivity.this.refresh();
                    }
                }
            });
            play.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    try {
                        if (en.isPlayingMusic()) {
                            en.stopPlayingMusic();
                            play.setText("播放音乐");
                            manager.addDeviceLog(dev.getDeviceID(), "停止播放音乐");
                        } else {
                            en.startPlayingMusic();
                            play.setText("停止音乐");
                            manager.addDeviceLog(dev.getDeviceID(), "开始播放音乐");
                        }
                    } catch (SQLException | IllegalStateException | IllegalArgumentException e) {
                        DeviceManageActivity.this.errorHandler(e, play.getText());
                        return;
                    }
                    DeviceManageActivity.this.refresh();
                }
            });
        }
        if (dev instanceof Displayable) {
            Displayable d = (Displayable) dev;
            JButton play = new JButton(d.isPlayingVideo() ? "停止视频" : "播放视频");
            play.setFont(FONT_PLAIN);
            bottomButtonsContainer.add(play);
            play.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    try {
                        if (d.isPlayingVideo()) {
                            d.stopPlayingVideo();
                            play.setText("播放视频");
                            manager.addDeviceLog(dev.getDeviceID(), "停止播放视频");
                        } else {
                            d.startPlayingVideo();
                            play.setText("停止视频");
                            manager.addDeviceLog(dev.getDeviceID(), "开始播放视频");
                        }
                    } catch (SQLException | IllegalStateException | IllegalArgumentException e) {
                        DeviceManageActivity.this.errorHandler(e, play.getText());
                        return;
                    }
                    DeviceManageActivity.this.refresh();
                }
            });
        }
        if (dev instanceof HouseholdDevice) {
            HouseholdDevice device = (HouseholdDevice) dev;
            JButton open = new JButton(device.isOpened() ? "关闭电源" : "打开电源");
            open.setFont(FONT_PLAIN);
            bottomButtonsContainer.add(open);
            open.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent event) {
                    try {
                        if (device.isOpened()) {
                            device.close();
                            open.setText("打开电源");
                            manager.addDeviceLog(dev.getDeviceID(), "设备已关机");
                        } else {
                            device.open();
                            open.setText("关闭电源");
                            manager.addDeviceLog(dev.getDeviceID(), "设备已开机");
                        }
                    } catch (SQLException | IllegalStateException | IllegalArgumentException e) {
                        DeviceManageActivity.this.errorHandler(e, open.getText());
                        return;
                    }
                    DeviceManageActivity.this.refresh();
                }
            });
            if (device instanceof KitchenAppliance) {
                KitchenAppliance appliance = (KitchenAppliance) device;
                JButton find = new JButton("检索食物");
                JButton put = new JButton("添加食物");
                find.setFont(FONT_PLAIN);
                put.setFont(FONT_PLAIN);
                bottomButtonsContainer.add(find);
                bottomButtonsContainer.add(put);
                find.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent event) {
                        String foodName = JOptionPane.showInputDialog(DeviceManageActivity.this,
                                "请输入食物名称：",
                                find.getText(),
                                JOptionPane.PLAIN_MESSAGE);
                        if (foodName != null) {
                            try {
                                KitchenAppliance.Food food = appliance.find(foodName);
                                manager.addDeviceLog(dev.getDeviceID(), "找到食物 " + food.getName());
                            } catch (SQLException | IllegalStateException | IllegalArgumentException e) {
                                DeviceManageActivity.this.errorHandler(e, find.getText());
                                return;
                            }
                            JOptionPane.showMessageDialog(DeviceManageActivity.this,
                                    "找到食物 " + foodName,
                                    find.getText(),
                                    JOptionPane.INFORMATION_MESSAGE);
                        }
                    }
                });
                put.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent event) {
                        String foodName = JOptionPane.showInputDialog(DeviceManageActivity.this,
                                "请输入食物名称：",
                                put.getText(),
                                JOptionPane.PLAIN_MESSAGE);
                        if (foodName != null) {
                            try {
                                KitchenAppliance.Food food = new KitchenAppliance.Food(foodName);
                                appliance.put(food);
                                manager.addDeviceLog(dev.getDeviceID(), "装入食物 " + food.getName());
                            } catch (SQLException | IllegalStateException | IllegalArgumentException e) {
                                DeviceManageActivity.this.errorHandler(e, put.getText());
                                return;
                            }
                            JOptionPane.showMessageDialog(DeviceManageActivity.this,
                                    "装入食物 " + foodName,
                                    put.getText(),
                                    JOptionPane.INFORMATION_MESSAGE);
                        }
                    }
                });
                if (device instanceof Fridge) {
                    JButton setTemp = new JButton("设置温度");
                    setTemp.setFont(FONT_PLAIN);
                    bottomButtonsContainer.add(setTemp);
                    setTemp.addActionListener(new ActionListener() {
                        @Override
                        public void actionPerformed(ActionEvent e) {
                            String tempStr = JOptionPane.showInputDialog(DeviceManageActivity.this,
                                    setTemp.getText(),
                                    setTemp.getText(),
                                    JOptionPane.INFORMATION_MESSAGE);
                            int temp = Integer.parseInt(tempStr);
                            try {
                                ((Fridge) device).setFrozenTemperature(temp);
                            } catch (IllegalArgumentException err) {
                                DeviceManageActivity.this.errorHandler(err, setTemp.getText());
                            }
                            DeviceManageActivity.this.refresh();
                        }
                    });
                }
            }
            if (device instanceof DeskLamp) {
                DeskLamp lamp = (DeskLamp) device;
                JButton setColor = new JButton("设置颜色");
                setColor.setFont(FONT_PLAIN);
                bottomButtonsContainer.add(setColor);
                setColor.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent event) {
                        Color color = JColorChooser.showDialog(DeviceManageActivity.this, setColor.getText(), lamp.getColor());
                        if (color != null) {
                            lamp.setColor(color);
                            try {
                                manager.addDeviceLog(dev.getDeviceID(), setColor.getText());
                            } catch (SQLException | IllegalStateException | IllegalArgumentException e) {
                                DeviceManageActivity.this.errorHandler(e, setColor.getText());
                            }
                        }
                        DeviceManageActivity.this.refresh();
                    }
                });
            }
        }
    }

    private void fillDeviceInfo() {
        if (dev instanceof Localizable) {
            devInfo.add("位置：" + ((Localizable) dev).getPosition());
        }
        if (dev instanceof HouseholdDevice) {
            devInfo.add("设备电源：" + (((HouseholdDevice) dev).isOpened() ? "开启" : "关闭"));
            if (dev instanceof Lighting) {
                Color color = ((Lighting) dev).getColor();
                devInfo.add(String.format("灯光颜色：RGB(%d, %d, %d)", color.getRed(), color.getGreen(), color.getBlue()));
            }
            if (dev instanceof Fridge) {
                devInfo.add(String.format("冰箱冷藏室温度：%d", ((Fridge) dev).getFrozenTemperature()));
            }
        }
        if (dev instanceof StepCountable) {
            devInfo.add("步数：" + ((StepCountable) dev).getSteps());
        }
        if (dev instanceof Wearable) {
            Wearable dev = (Wearable) this.dev;
            devInfo.add("实时心率：" + dev.realTimeHeartRate());
            devInfo.add("睡眠评分：" + dev.sleepQuality());
        }
        if (dev instanceof RunningAbility) {
            devInfo.add("运动状态：" + (((RunningAbility) dev).isRunning() ? "跑步中" : "未在运动"));
        }
        if (dev instanceof Enjoyable) {
            Enjoyable dev = (Enjoyable) this.dev;
            String music;
            try {
                music = dev.getMusic();
            } catch (IllegalArgumentException e) {
                music = "<未知>";
            }
            devInfo.add("音乐：" + music + "， 播放状态：" + (dev.isPlayingMusic() ? "正在播放" : "未在播放"));
        }
        if (dev instanceof Displayable) {
            devInfo.add("视频播放状态：" + (((Displayable) dev).isPlayingVideo() ? "正在播放" : "未在播放"));
        }
    }

    @Override
    protected void onRefresh() {
        fillDeviceInfo();
        centerInfo.setText(String.join("\n", devInfo));
        devInfo.clear();
    }

    @Override
    protected boolean onFinish() {
        manager.managing = false;
        return super.onFinish();
    }

    private void deleteDevice(ActionEvent event) {
        String when = "删除设备";
        if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(this,
                "即将删除该设备，这会导致设备断开连接，使用时需要再次连接。\n" +
                        "请问是否执行？",
                when,
                JOptionPane.YES_NO_OPTION,
                JOptionPane.WARNING_MESSAGE)) {
            try {
                manager.delDevice(dev);
            } catch (SQLException | IllegalArgumentException | IllegalStateException err) {
                errorHandler(err, when);
                return;
            }
            JOptionPane.showMessageDialog(DeviceManageActivity.this,
                    "设备成功删除。",
                    when,
                    JOptionPane.WARNING_MESSAGE);
            DeviceManageActivity.this.finish();
            activity.refresh();
        }
    }

    private void showDeviceLog(ActionEvent event) {
        String log;
        try {
            log = manager.getDeviceLog(dev.getDeviceID());
        } catch (SQLException | IllegalStateException e) {
            errorHandler(e, "设备日志");
            return;
        }
        JOptionPane.showMessageDialog(DeviceManageActivity.this,
                log,
                String.format("设备日志 id=%06d", dev.getDeviceID()),
                JOptionPane.PLAIN_MESSAGE);
    }
}
