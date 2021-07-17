package punch.activity;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

// 可重复打卡活动类
public class RepeatActivity extends BasicActivity {
    // 活动类型
    public static final String TYPE = "REPEAT";

    private int count;

    public RepeatActivity(String name, String description) {
        super(name, description);
        count = 1;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
        if (count > 0) {
            status = EXEC_STATUS;
        }
    }

    @Override
    public void punch() throws IllegalStateException {
        if (status.equals(READY_STATUS)) {
            count--;
            status = EXEC_STATUS;
        } else if (status.equals(EXEC_STATUS)) {
            count--;
        } else {
            throw new IllegalStateException("错误的活动状态");
        }
        if (count <= 0) {
            count = 0;
            status = FINISH_STATUS;
        }
    }

    @Override
    public String getType() {
        return TYPE;
    }

    @Override
    public String getDetailInfo() {
        return String.format("COUNT=%d;", count);
    }

    @Override
    public void setDetailInfo(String info) throws IllegalArgumentException {
        Matcher m = Pattern.compile("^COUNT=(\\d+);$").matcher(info.trim());
        if (m.matches()) {
            count = Integer.parseInt(m.group(1));
        } else {
            throw new IllegalArgumentException("不合法的附加信息");
        }
    }
}
