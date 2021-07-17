package manager.devices.base;

import manager.devices.ability.Localizable;

/**
 * 家居设备基类
 */
public abstract class HouseholdDevice extends SmartDevice implements Localizable {
    public static final String DEVICE_NAME = "Household Device";

    protected String position;
    protected boolean openStatus;

    protected HouseholdDevice(String name, String position) {
        super();
        this.name = name;
        this.openStatus = false;
        this.position = position;
    }

    protected HouseholdDevice(String name) {
        this(name, POSITIONS[0]);
    }

    protected HouseholdDevice() {
        this(DEVICE_NAME);
    }

    /**
     * 打开家具设备
     */
    public void open() {
        if (this.openStatus) return;
        this.openStatus = true;
    }

    /**
     * 关闭家具设备
     */
    public void close() throws IllegalStateException {
        if (!this.openStatus) throw new IllegalStateException("还没有打开设备");
        this.openStatus = false;
    }

    public boolean isOpened() {
        return this.openStatus;
    }

    // 固定位置设备实现

    @Override
    public String getPosition() {
        return this.position;
    }

}
