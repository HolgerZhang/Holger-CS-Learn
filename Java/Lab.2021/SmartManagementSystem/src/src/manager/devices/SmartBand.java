package manager.devices;

import manager.devices.ability.Wearable;
import manager.devices.base.SportDevice;

import java.util.Random;

/**
 * 智能手环类
 */
public class SmartBand extends SportDevice implements Wearable {
    public static final String DEVICE_NAME = "Smart Band";
    private final Random heartDevice;
    private boolean connectStatue;

    public SmartBand(String name) {
        super(name);
        this.connectStatue = false;
        this.heartDevice = new Random();
    }

    public SmartBand() {
        this(DEVICE_NAME);
        this.name = DEVICE_NAME + getDeviceID();
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

    // 可穿戴设备功能实现

    @Override
    public double sleepQuality() {
        double score = 8 * (this.steps / 10000.0) + (this.realTimeHeartRate() * 0.618);
        if (score >= 100) score = 100;
        return score;
    }

    @Override
    public int realTimeHeartRate() {
        return this.heartDevice.nextInt(60) + 60;
    }
}
