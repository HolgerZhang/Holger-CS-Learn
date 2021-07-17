package manager.devices;

import manager.devices.base.Lighting;

import java.awt.*;

/**
 * 吸顶灯类
 */
public class CeilingLamp extends Lighting {
    public static final String DEVICE_NAME = "Ceiling Lamp";
    private boolean connectStatue;

    public CeilingLamp(String name, String position) {
        super(name, position);
        this.connectStatue = false;
    }

    public CeilingLamp(String name) {
        this(name, POSITIONS[0]);
    }

    public CeilingLamp() {
        this(DEVICE_NAME);
        this.name = DEVICE_NAME + getDeviceID() + " at " + position;
    }

    @Override
    public Color getColor() {
        return Color.WHITE;
    }

    // 实现连接功能

    @Override
    public void connect() throws IllegalStateException {
        if (this.connectStatue) {
            throw new IllegalStateException("设备已经连接");
        }
        this.connectStatue = true;
    }

    @Override
    public void disconnect() throws IllegalStateException {
        if (!this.connectStatue) {
            throw new IllegalStateException("设备还未连接");
        }
        this.connectStatue = false;
    }

}
