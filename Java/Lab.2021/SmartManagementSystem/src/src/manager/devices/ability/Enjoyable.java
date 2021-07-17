package manager.devices.ability;

/**
 * 娱乐能力接口
 * 音乐播放
 */
public interface Enjoyable {
    void setMusic(String music);

    String getMusic();

    void startPlayingMusic() throws IllegalArgumentException;

    void stopPlayingMusic() throws IllegalArgumentException, IllegalStateException;

    boolean isPlayingMusic();

}
