package punch.activity;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

// 消费记录（攒钱）活动类
public class MoneySavingActivity extends BasicActivity {
    // 活动类型
    public static final String TYPE = "MONEY";

    private int aim;
    private int used;

    public MoneySavingActivity(String name, String description) {
        super(name, description);
        aim = 0;
        used = 0;
    }

    // 打卡方法
    public void punch(int money) throws IllegalStateException {
        if (status.equals(READY_STATUS) || status.equals(EXEC_STATUS)) {
            status = EXEC_STATUS;
            if (money + used > aim) {
                throw new IllegalStateException("总花费超过目标金额");
            } else {
                used += money;
            }
            if (used == aim) {
                status = FINISH_STATUS;
            }
        } else {
            throw new IllegalStateException("错误的活动状态");
        }
    }

    // 打卡方法(默认)
    @Override
    public void punch() throws IllegalStateException {
        punch(Math.min(aim - used, 100));
    }

    // Getter/Setter

    public int getAim() {
        return aim;
    }

    public void setAim(int aim) {
        this.aim = aim;
        if (aim > used) {
            status = EXEC_STATUS;
        } else {
            status = FINISH_STATUS;
        }
    }

    public int getUsed() {
        return used;
    }

    @Override
    public String getType() {
        return TYPE;
    }

    @Override
    public String getDetailInfo() {
        return String.format("AIM=%d; USED=%d;", aim, used);
    }

    @Override
    public void setDetailInfo(String info) throws IllegalArgumentException {

        Matcher m = Pattern.compile("^AIM=(\\d+);\\s*USED=(\\d+);$").matcher(info.trim());
        if (m.matches()) {
            aim = Integer.parseInt(m.group(1));
            used = Integer.parseInt(m.group(2));
        } else {
            throw new IllegalArgumentException("不合法的附加信息");
        }
    }
}
