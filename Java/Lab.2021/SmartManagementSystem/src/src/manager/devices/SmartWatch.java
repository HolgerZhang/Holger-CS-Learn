package manager.devices;

import manager.devices.ability.Displayable;
import manager.devices.ability.Enjoyable;
import manager.devices.ability.Wearable;
import manager.devices.base.SportDevice;

import java.util.Random;

/**
 * 智能手表类
 */
public class SmartWatch extends SportDevice
        implements Wearable, Enjoyable, Displayable {
    public static final String DEVICE_NAME = "Smart Watch";
    private final Random heartDevice;
    private boolean connectStatue;
    private String music;
    private boolean musicStatue;
    private boolean videoStatue;

    public SmartWatch(String name) {
        super(name);
        this.music = null;
        this.musicStatue = false;
        this.connectStatue = false;
        this.heartDevice = new Random();
        this.videoStatue = false;
    }

    public SmartWatch() {
        this(DEVICE_NAME);
        this.name = DEVICE_NAME + getDeviceID();
    }

    // 娱乐能力实现

    @Override
    public void setMusic(String music) {
        this.music = music;
    }

    @Override
    public String getMusic() throws IllegalArgumentException {
        if (music == null) {
            throw new IllegalArgumentException("未设置音乐");
        }
        return this.music;
    }

    @Override
    public void startPlayingMusic() throws IllegalArgumentException {
        if (music == null) {
            throw new IllegalArgumentException("未设置音乐");
        }
        this.musicStatue = true;
    }

    @Override
    public void stopPlayingMusic() throws IllegalArgumentException, IllegalStateException {
        if (music == null) {
            throw new IllegalArgumentException("未设置音乐");
        } else if (!musicStatue) {
            throw new IllegalStateException("还没有播放音乐");
        }
        this.musicStatue = false;
    }

    @Override
    public boolean isPlayingMusic() {
        return this.musicStatue;
    }

    // 可穿戴设备功能实现

    @Override
    public double sleepQuality() {
        double score = 9 * (this.steps / 10000.0) + (this.realTimeHeartRate() * 0.618);
        if (score >= 120) score = 120;
        return score;
    }

    @Override
    public int realTimeHeartRate() {
        return this.heartDevice.nextInt(55) + 60;
    }

    // 可现实设备能力实现

    @Override
    public void startPlayingVideo() {
        this.videoStatue = true;
    }

    @Override
    public void stopPlayingVideo() throws IllegalStateException {
        if (!videoStatue) throw new IllegalStateException("还没有播放");
        this.videoStatue = false;
    }

    @Override
    public boolean isPlayingVideo() {
        return this.videoStatue;
    }

    // 实现连接功能

    @Override
    public void connect() throws IllegalStateException {
        if (this.connectStatue) {
            throw new IllegalStateException("设备已经连接");
        }
        this.connectStatue = true;
        this.musicStatue = false;
        this.music = null;
        this.videoStatue = false;
    }

    @Override
    public void disconnect() throws IllegalStateException {
        if (!this.connectStatue) {
            throw new IllegalStateException("设备还未连接");
        }
        this.connectStatue = false;
        this.musicStatue = false;
        this.music = null;
        this.videoStatue = false;
    }
}
