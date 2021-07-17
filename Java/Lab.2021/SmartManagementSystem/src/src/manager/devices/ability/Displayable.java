package manager.devices.ability;

/**
 * 可显示设备能力接口
 */
public interface Displayable {
    void startPlayingVideo();

    void stopPlayingVideo() throws IllegalStateException;

    boolean isPlayingVideo();
}
