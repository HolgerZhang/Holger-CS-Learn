package manager.devices.base;

import manager.devices.ability.Enjoyable;

/**
 * 娱乐设备基类
 */
public abstract class EntertainmentDevice extends HouseholdDevice implements Enjoyable {
    public static final String DEVICE_NAME = "Entertainment Device";
    protected boolean musicStatue;
    private String music;

    protected EntertainmentDevice(String name, String position) {
        super(name, position);
    }

    protected EntertainmentDevice(String name) {
        this(name, POSITIONS[0]);
    }

    protected EntertainmentDevice() {
        this(DEVICE_NAME);
    }

    // 娱乐能力实现

    @Override
    public void setMusic(String music) {
        this.music = music;
    }

    @Override
    public String getMusic() {
        if (!openStatus) {
            throw new IllegalArgumentException("未开启电源");
        }
        if (music == null) {
            throw new IllegalArgumentException("未设置音乐");
        }
        return this.music;
    }

    @Override
    public void startPlayingMusic() throws IllegalArgumentException {
        if (!openStatus) {
            throw new IllegalArgumentException("未开启电源");
        }
        if (music == null) {
            throw new IllegalArgumentException("未设置音乐");
        }
        this.musicStatue = true;
    }

    @Override
    public void stopPlayingMusic() throws IllegalArgumentException, IllegalStateException {
        if (!openStatus) {
            throw new IllegalArgumentException("未开启电源");
        }
        if (music == null) {
            throw new IllegalArgumentException("未设置音乐");
        } else if (!musicStatue) {
            throw new IllegalStateException("还没有播放音乐");
        }
        this.musicStatue = false;
    }

    @Override
    public boolean isPlayingMusic() {
        if (!openStatus) {
            return false;
        }
        return this.musicStatue;
    }

}
