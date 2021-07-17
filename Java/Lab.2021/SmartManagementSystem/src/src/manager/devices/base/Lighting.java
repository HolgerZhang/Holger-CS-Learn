package manager.devices.base;

import java.awt.*;

/**
 * 照明电器基类
 */
public abstract class Lighting extends HouseholdDevice {
    public static final String DEVICE_NAME = "Lighting";

    protected boolean lightStatue;

    protected Lighting(String name, String position) {
        super();
        this.name = name;
        this.openStatus = false;
        this.position = position;
    }

    protected Lighting(String name) {
        this(name, POSITIONS[0]);
    }

    protected Lighting() {
        this(DEVICE_NAME);
    }

    // 获取灯的颜色
    public abstract Color getColor();

    // 重写开关

    @Override
    public void open() {
        super.open();
        this.lightStatue = true;
    }

    @Override
    public void close() throws IllegalStateException {
        super.close();
        this.lightStatue = false;
    }
}
