package punch.activity;

import java.util.UUID;

// 基础活动类
public class BasicActivity {

    // 用户活动拥有模式
    public static final String OWN_A_MODE = "OWN";
    public static final String VISIBLE_A_MODE = "VISIBLE";
    public static final String EDITABLE_A_MODE = "EDITABLE";
    public static final String[] A_MODES = {VISIBLE_A_MODE, EDITABLE_A_MODE};
    public static final String[] A_MODES_WITH_ALL = {"ALL", OWN_A_MODE, VISIBLE_A_MODE, EDITABLE_A_MODE};
    // 活动状态
    public static final String READY_STATUS = "READY";
    public static final String EXEC_STATUS = "EXEC";
    public static final String FINISH_STATUS = "FINISH";
    // 活动类型
    public static final String TYPE = "BASIC";

    protected long id;
    protected String name;
    protected String status;
    protected String description;

    public BasicActivity(String name, String description) {
        this.id = UUID.randomUUID().getMostSignificantBits() & Long.MAX_VALUE;
        this.name = name;
        this.status = READY_STATUS;
        this.description = description;
    }

    // 打卡方法
    public void punch() throws IllegalStateException {
        if (status.equals(READY_STATUS)) {
            this.status = FINISH_STATUS;
        } else {
            throw new IllegalStateException("错误的状态");
        }
    }

    // Getter/Setter

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getType() {
        return TYPE;
    }

    public String getDetailInfo() {
        return "";
    }

    public void setDetailInfo(String info) throws IllegalArgumentException {
    }
}
