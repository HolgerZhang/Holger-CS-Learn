package manager.devices.base;

/**
 * 厨房电器基类
 */
public abstract class KitchenAppliance extends HouseholdDevice {
    public static final String DEVICE_NAME = "Kitchen Appliance";

    protected KitchenAppliance(String name, String position) {
        super(name, position);
    }

    protected KitchenAppliance(String name) {
        this(name, POSITIONS[0]);
    }

    protected KitchenAppliance() {
        this(DEVICE_NAME);
    }

    public abstract Food find(String name) throws IllegalArgumentException;

    public abstract void put(Food food);

    /**
     * 食物类
     */
    public static class Food {
        private final String name;

        public Food(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }

    }

}
