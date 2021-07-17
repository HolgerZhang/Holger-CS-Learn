package manager.account;

import manager.devices.base.SmartDevice;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class DevicesTable {
    private final Map<Long, SmartDevice> devices;

    public DevicesTable() {
        devices = new HashMap<>();
    }

    public SmartDevice find(long deviceID) {
        return devices.getOrDefault(deviceID, null);
    }

    public <T extends SmartDevice> void add(T device) throws IllegalArgumentException {
        if (devices.containsKey(device.getDeviceID()))
            throw new IllegalArgumentException("设备id已存在");
        devices.put(device.getDeviceID(), device);
        device.connect();
    }

    public <T extends SmartDevice> void delete(T device) throws IllegalArgumentException {
        if (!devices.containsKey(device.getDeviceID()))
            throw new IllegalArgumentException("设备id不存在");
        devices.remove(device.getDeviceID());
        device.disconnect();
    }

    public Set<Long> listDeviceId() {
        return devices.keySet();
    }
}
