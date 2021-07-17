package manager.devices;

import manager.devices.base.KitchenAppliance;

import java.util.HashMap;
import java.util.Map;

/**
 * 智能冰箱类
 */
public class Fridge extends KitchenAppliance {
    public static final String DEVICE_NAME = "Fridge";

    private final Map<String, Food> foods;
    private int frozenTemperature;
    private boolean connectStatue;

    public Fridge(String name, String position) {
        super(name, position);
        this.foods = new HashMap<>();
        this.frozenTemperature = -18;
        this.connectStatue = false;
    }

    protected Fridge(String name) {
        this(name, POSITIONS[0]);
    }

    public Fridge() {
        this(DEVICE_NAME);
        this.name = DEVICE_NAME + getDeviceID() + " at " + position;
    }

    /**
     * 找食物
     *
     * @param name 食物名
     */
    @Override
    public Food find(String name) throws IllegalArgumentException {
        if (!openStatus) {
            throw new IllegalArgumentException("未开启电源");
        }if (!this.foods.containsKey(name)) {
            throw new IllegalArgumentException("未找到对应食品");
        }
        return this.foods.get(name);
    }

    /**
     * 放置食物
     */
    @Override
    public void put(Food food) {
        if (!openStatus) {
            throw new IllegalArgumentException("未开启电源");
        }this.foods.put(food.getName(), food);
    }

    /**
     * 获取冷冻室温度
     */
    public int getFrozenTemperature() {
        return this.frozenTemperature;
    }

    /**
     * 设置冷冻室温度
     */
    public void setFrozenTemperature(int temperature) throws IllegalArgumentException {
        if (temperature < -20 || temperature > 4) {
            throw new IllegalArgumentException("错误的温度值");
        }
        this.frozenTemperature = temperature;
    }

    // 实现连接功能

    @Override
    public void connect() throws IllegalStateException {
        if (this.connectStatue) {
            throw new IllegalStateException("设备已经连接");
        }
        this.connectStatue = true;
    }

    @Override
    public void disconnect() throws IllegalStateException {
        if (!this.connectStatue) {
            throw new IllegalStateException("设备还未连接");
        }
        this.connectStatue = false;
    }

}
