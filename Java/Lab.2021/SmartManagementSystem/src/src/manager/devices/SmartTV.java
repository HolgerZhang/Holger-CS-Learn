package manager.devices;

import manager.devices.ability.Displayable;
import manager.devices.base.EntertainmentDevice;

/**
 * 智能电视类
 */
public class SmartTV extends EntertainmentDevice
        implements Displayable {
    public static final String DEVICE_NAME = "Smart TV";
    private boolean videoStatue;
    private boolean connectStatue;

    public SmartTV(String name, String position) {
        super(name, position);
        this.videoStatue = false;
        this.connectStatue = false;
    }

    public SmartTV(String name) {
        this(name, POSITIONS[0]);
    }

    public SmartTV() {
        this(null);
    }

    // 可显示设备能力实现

    @Override
    public void startPlayingVideo() {
        if (!openStatus) {
            throw new IllegalArgumentException("未开启电源");
        }
        this.videoStatue = true;
    }

    @Override
    public void stopPlayingVideo() throws IllegalStateException {
        if (!openStatus) {
            throw new IllegalArgumentException("未开启电源");
        }
        if (!videoStatue) throw new IllegalStateException("还没有播放");
        this.videoStatue = false;
    }

    @Override
    public boolean isPlayingVideo() {
        if (!openStatus) {
            return false;
        }
        return this.videoStatue;
    }

    // 实现连接功能

    @Override
    public void connect() throws IllegalStateException {
        if (this.connectStatue) {
            throw new IllegalStateException("设备已经连接");
        }
        this.connectStatue = true;
        this.videoStatue = false;
    }

    @Override
    public void disconnect() throws IllegalStateException {
        if (!this.connectStatue) {
            throw new IllegalStateException("设备还未连接");
        }
        this.connectStatue = false;
        this.videoStatue = false;
    }

}
