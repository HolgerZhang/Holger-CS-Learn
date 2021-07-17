package punch.activity;

import java.text.DateFormat;
import java.util.Date;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

// 禅定模式打卡活动类
public class ZenModeActivity extends BasicActivity {
    // 活动类型
    public static final String TYPE = "ZEN";

    private int lasting;
    private long begin;

    public ZenModeActivity(String name, String description) {
        super(name, description);
        lasting = 0;
        begin = 0L;
    }

    public int getLasting() {
        return lasting;
    }

    public void setLasting(int lasting) {
        this.lasting = lasting;
        if (status.equals(FINISH_STATUS)) {
            status = READY_STATUS;
            begin = 0L;
        }
    }

    @Override
    public void punch() throws IllegalStateException {
        if (status.equals(READY_STATUS)) {
            status = EXEC_STATUS;
            begin = System.currentTimeMillis();
        } else if (status.equals(EXEC_STATUS)) {
            if (System.currentTimeMillis() - begin >= 1000L * lasting) {
                status = FINISH_STATUS;
            } else {
                throw new IllegalStateException("现在还不能结束打卡");
            }
        } else {
            throw new IllegalStateException("错误的活动状态");
        }
    }

    public String getBegin() {
        if (begin == 0L) {
            return "尚未开始";
        }
        return DateFormat.getDateTimeInstance().format(new Date(begin));
    }

    @Override
    public String getType() {
        return TYPE;
    }

    @Override
    public String getDetailInfo() {
        return String.format("LAST=%d; BEG=%d;", lasting, begin);
    }

    @Override
    public void setDetailInfo(String info) throws IllegalArgumentException {
        Matcher m = Pattern.compile("^LAST=(\\d+);\\s*BEG=(\\d+);$").matcher(info.trim());
        if (m.matches()) {
            lasting = Integer.parseInt(m.group(1));
            begin = Long.parseLong(m.group(2));
        } else {
            throw new IllegalArgumentException("不合法的附加信息");
        }
    }
}
