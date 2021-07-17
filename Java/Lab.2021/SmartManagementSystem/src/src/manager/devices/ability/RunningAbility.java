package manager.devices.ability;

/**
 * 跑步能力接口
 */
public interface RunningAbility {
    void startRunning();

    double stopRunning() throws IllegalStateException;

    boolean isRunning();
}
