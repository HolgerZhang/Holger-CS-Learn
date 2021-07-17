package manager.devices.base;

import manager.devices.ability.RunningAbility;
import manager.devices.ability.StepCountable;

/**
 * 运动健身设备基类
 */
public abstract class SportDevice extends SmartDevice
        implements StepCountable, RunningAbility {
    public static final String DEVICE_NAME = "Sport Device";
    protected boolean runningState;
    protected int steps;
    private long runningTime;

    protected SportDevice(String name) {
        super();
        this.name = name;
        this.runningState = false;
        this.runningTime = 0L;
        this.steps = 0;
    }

    protected SportDevice() {
        this(DEVICE_NAME);
    }

    // 实现计步能力

    @Override
    public int getSteps() {
        return this.steps;
    }

    @Override
    public void resetStepCounter() {
        this.steps = 0;
    }

    // 实现跑步能力

    @Override
    public void startRunning() {
        if (this.runningState) {
            return;
        }
        this.runningState = true;
        this.runningTime = System.currentTimeMillis();
    }

    @Override
    public double stopRunning() throws IllegalStateException {
        if (!this.runningState) {
            throw new IllegalStateException("还没有开始跑步！");
        }
        this.runningState = false;
        double useTime = (System.currentTimeMillis() - this.runningTime) / 1000.0;
        this.runningTime = 0L;
        this.steps += (int) (useTime * 2);
        return useTime;
    }

    @Override
    public boolean isRunning() {
        return this.runningState;
    }

}
