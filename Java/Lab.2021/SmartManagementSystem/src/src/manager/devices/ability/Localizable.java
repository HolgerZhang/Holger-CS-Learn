package manager.devices.ability;

/**
 * 固定位置设备接口
 */
public interface Localizable {
    String[] POSITIONS = {"客厅", "厨房", "主卧", "次卧"};

    String getPosition();
}
