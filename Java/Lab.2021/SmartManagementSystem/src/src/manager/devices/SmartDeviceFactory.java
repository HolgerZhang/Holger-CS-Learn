package manager.devices;

import manager.devices.ability.Localizable;
import manager.devices.base.SmartDevice;

import java.io.File;


public class SmartDeviceFactory {
    public static final String[] DEVICE_TYPES = {
            SmartBand.DEVICE_NAME, SmartWatch.DEVICE_NAME, SmartTV.DEVICE_NAME,
            Treadmill.DEVICE_NAME, Fridge.DEVICE_NAME, CeilingLamp.DEVICE_NAME, DeskLamp.DEVICE_NAME
    };

    public static SmartDevice createDevice(long dev_id, String name, String type, String position)
            throws IllegalArgumentException {
        SmartDevice dev = createDeviceAutomatically(name, type, position);
        dev.setDeviceID(dev_id);
        SmartDevice.setTotalDevicesNumber(SmartDevice.getTotalDevicesNumber() - 1);
        return dev;
    }

    public static SmartDevice createDeviceAutomatically(String name, String type, String position)
            throws IllegalArgumentException {
        SmartDevice dev;
        if (position == null) {
            position = Localizable.POSITIONS[0];
        }
        switch (type) {
            case SmartBand.DEVICE_NAME:
                dev = new SmartBand(name);
                break;
            case SmartWatch.DEVICE_NAME:
                dev = new SmartWatch(name);
                break;
            case SmartTV.DEVICE_NAME:
                dev = new SmartTV(name, position);
                break;
            case Treadmill.DEVICE_NAME:
                dev = new Treadmill(name, position);
                break;
            case Fridge.DEVICE_NAME:
                dev = new Fridge(name, position);
                break;
            case CeilingLamp.DEVICE_NAME:
                dev = new CeilingLamp(name, position);
                break;
            case DeskLamp.DEVICE_NAME:
                dev = new DeskLamp(name, position);
                break;
            default:
                throw new IllegalArgumentException("未知的设备类型");
        }
        return dev;
    }

    public static String getDevicePhoto(String type) {
        String path = System.getProperty("user.dir") + File.separator;
        switch (type) {
            case SmartBand.DEVICE_NAME:
                path += "data/img/band.jpg";
                break;
            case SmartWatch.DEVICE_NAME:
                path += "data/img/watch.jpg";
                break;
            case SmartTV.DEVICE_NAME:
                path += "data/img/tv.jpg";
                break;
            case Treadmill.DEVICE_NAME:
                path += "data/img/treadmill.jpg";
                break;
            case Fridge.DEVICE_NAME:
                path += "data/img/fridge.jpg";
                break;
            case CeilingLamp.DEVICE_NAME:
                path += "data/img/ceil_lamp.jpg";
                break;
            case DeskLamp.DEVICE_NAME:
                path += "data/img/desk_lamp.jpg";
                break;
            default:
                throw new IllegalArgumentException("未知的设备类型");
        }
        return path;
    }

}
