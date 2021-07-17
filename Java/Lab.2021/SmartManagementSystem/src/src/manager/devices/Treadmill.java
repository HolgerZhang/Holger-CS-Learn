package manager.devices;

import manager.devices.ability.Localizable;
import manager.devices.base.SportDevice;


/**
 * 跑步机类
 */
public class Treadmill extends SportDevice implements Localizable {
    public static final String DEVICE_NAME = "Treadmill";

    private final String position;
    private boolean connectStatue;

    public Treadmill(String name, String position) {
        super(name);
        this.position = position;
        this.connectStatue = false;
    }

    public Treadmill(String name) {
        this(name, POSITIONS[0]);
    }

    public Treadmill() {
        this(DEVICE_NAME);
        this.name = DEVICE_NAME + getDeviceID();
    }

    // 固定位置设备实现

    @Override
    public String getPosition() {
        return this.position;
    }

    // 实现连接功能

    @Override
    public void connect() throws IllegalStateException {
        if (this.connectStatue) {
            throw new IllegalStateException("设备已经连接");
        }
        this.connectStatue = true;
        this.steps = 0;
    }

    @Override
    public void disconnect() throws IllegalStateException {
        if (!this.connectStatue) {
            throw new IllegalStateException("设备还未连接");
        }
        this.connectStatue = false;
        this.steps = 0;
    }
}
