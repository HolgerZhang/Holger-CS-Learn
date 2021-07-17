package manager.devices.base;

/**
 * 智能设备基类
 */
public abstract class SmartDevice {
    public static final String DEVICE_NAME = "Smart Device";
    static long totalDevicesNumber = 0L;
    protected String name;
    long deviceID;

    protected SmartDevice() {
        this.deviceID = totalDevicesNumber;
        totalDevicesNumber++;
        this.name = DEVICE_NAME;
    }

    public static String getDeviceName(SmartDevice device) {
        String type = DEVICE_NAME;
        try {
            type = (String) device.getClass().getField("DEVICE_NAME").get(null);
        } catch (IllegalAccessException | NoSuchFieldException e) {
            e.printStackTrace();
            System.exit(1);
        }
        return type;
    }

    public static long getTotalDevicesNumber() {
        return totalDevicesNumber;
    }

    public static void setTotalDevicesNumber(long totalDevicesNumber) {
        SmartDevice.totalDevicesNumber = totalDevicesNumber;
    }

    /**
     * 获取设备 id
     */
    public final long getDeviceID() {
        return this.deviceID;
    }

    public final void setDeviceID(long deviceID) {
        this.deviceID = deviceID;
    }

    /**
     * 连接到设备
     */
    public abstract void connect() throws IllegalStateException;

    /**
     * 断开连接
     */
    public abstract void disconnect() throws IllegalStateException;

    public String getName() {
        return name;
    }
}
