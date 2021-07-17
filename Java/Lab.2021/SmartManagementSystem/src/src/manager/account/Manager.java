package manager.account;

import manager.db.Database;
import manager.devices.ability.Localizable;
import manager.devices.base.SmartDevice;

import java.sql.SQLException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Manager {
    private final Map<String, User> userCache;
    public boolean managing;
    private User user;

    public Manager() {
        user = null;
        userCache = new HashMap<>();
        managing = false;
    }

    public void login(User user) {
        if (userCache.containsKey(user.getName())) {
            this.user = userCache.get(user.getName());
            return;
        }
        this.user = user;
        try {
            for (SmartDevice dev : Database.selectDevices(user.getName())) {
                this.user.getDevices().add(dev);
            }
        } catch (SQLException | IllegalArgumentException e) {
            e.printStackTrace();
            System.exit(1);
        }
        userCache.put(this.user.getName(), this.user);
    }

    public boolean isLogin() {
        return user != null;
    }

    public void logout() {
        user = null;
    }

    public void clearCache() {
        this.userCache.clear();
    }

    public void register(String name, String passwd)
            throws SQLException, IllegalArgumentException {
        Database.insertUser(name, User.md5Password(passwd));
    }

    public void addDevice(SmartDevice device)
            throws SQLException, IllegalArgumentException, IllegalStateException {
        if (!isLogin()) {
            throw new IllegalStateException("还没有登录");
        }
        long id = device.getDeviceID();
        String name = device.getName(), type = SmartDevice.getDeviceName(device), position = null;
        if (device instanceof Localizable) {
            position = ((Localizable) device).getPosition();
        }
        Database.insertDevice(id, name, type, position, user.getName());
        Database.insertDeviceLog(id, user.getName(), "设备初始化");
        this.user.getDevices().add(device);
    }

    public String getUserLog() throws SQLException, IllegalStateException {
        if (!isLogin()) {
            throw new IllegalStateException("还没有登录");
        }
        return Database.selectDeviceLog(user.getName());
    }


    public void reset() throws SQLException, IllegalStateException {
        if (isLogin()) {
            throw new IllegalStateException("用户已登录，请先注销");
        }
        clearCache();
        Database.resetDB();
        SmartDevice.setTotalDevicesNumber(0L);
    }

    public Set<Long> sceneDevices(String scene) throws SQLException, IllegalStateException {
        if (!isLogin()) {
            throw new IllegalStateException("还没有登录");
        }
        Set<Long> res;
        if (scene != null) {
            res = Database.selectSceneDevices(user.getName(), scene);
        } else {
            res = user.getDevices().listDeviceId();
        }
        return res;
    }

    public SmartDevice findDev(long id) throws IllegalStateException {
        if (!isLogin()) {
            throw new IllegalStateException("还没有登录");
        }
        return user.getDevices().find(id);
    }

    public List<String> listScene() throws SQLException, IllegalStateException {
        if (!isLogin()) {
            throw new IllegalStateException("还没有登录");
        }
        return Database.selectPositions(user.getName());
    }

    public void delDevice(SmartDevice device)
            throws SQLException, IllegalArgumentException, IllegalStateException {
        if (!isLogin()) {
            throw new IllegalStateException("还没有登录");
        }
        Database.deleteDevice(device.getDeviceID());
        Database.insertDeviceLog(device.getDeviceID(), user.getName(), "删除设备");
        user.getDevices().delete(device);
    }

    public String getDeviceLog(long id) throws SQLException, IllegalStateException {
        if (!isLogin()) {
            throw new IllegalStateException("还没有登录");
        }
        return Database.selectDeviceLog(id);
    }

    public void addDeviceLog(long deviceID, String log) throws SQLException, IllegalStateException {
        if (!isLogin()) {
            throw new IllegalStateException("还没有登录");
        }
        Database.insertDeviceLog(deviceID, user.getName(), log);
    }
}
