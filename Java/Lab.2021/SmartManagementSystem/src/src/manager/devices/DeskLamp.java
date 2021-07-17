package manager.devices;

import manager.devices.base.Lighting;

import java.awt.*;

/**
 * 台灯类
 */
public class DeskLamp extends Lighting {
    public static final String DEVICE_NAME = "Desk Lamp";
    public Color color;
    private boolean connectStatue;

    public DeskLamp(String name, String position) {
        super(name, position);
        this.color = Color.WHITE;
        this.connectStatue = false;
    }

    public DeskLamp(String name) {
        this(name, POSITIONS[0]);
    }

    public DeskLamp() {
        this(DEVICE_NAME);
        this.name = DEVICE_NAME + getDeviceID() + " at " + position;
    }

    @Override
    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    // 实现连接功能

    @Override
    public void connect() throws IllegalStateException {
        if (this.connectStatue) {
            throw new IllegalStateException("设备已经连接");
        }
        this.connectStatue = true;
        this.color = Color.WHITE;
    }

    @Override
    public void disconnect() throws IllegalStateException {
        if (!this.connectStatue) {
            throw new IllegalStateException("设备还未连接");
        }
        this.connectStatue = false;
        this.color = Color.WHITE;
    }

}
