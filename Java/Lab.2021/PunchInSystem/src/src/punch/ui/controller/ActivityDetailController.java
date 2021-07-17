package punch.ui.controller;

import punch.activity.BasicActivity;
import punch.activity.MoneySavingActivity;
import punch.activity.RepeatActivity;
import punch.activity.ZenModeActivity;
import punch.db.Database;

import java.sql.SQLException;
import java.util.LinkedList;
import java.util.List;

public class ActivityDetailController {
    private final MainController ownerController;
    private BasicActivity activity;
    private final String mode;
    Database db = Database.getInstance();

    public ActivityDetailController(MainController ownerController, BasicActivity activity, String mode) {
        this.ownerController = ownerController;
        this.activity = activity;
        this.mode = mode;
    }

    public void punchIn(Integer i) throws SQLException, IllegalStateException {
        ownerController.activityPunchIn(activity.getId(), i);
    }

    public boolean isMoneySavingActivity() {
        return activity instanceof MoneySavingActivity;
    }

    public boolean isRepeatActivity() {
        return activity instanceof RepeatActivity;
    }

    public boolean isZenModeActivity() {
        return activity instanceof ZenModeActivity;
    }

    public void deleteActivity() throws SQLException {
        long aid = activity.getId();
        db.deleteActivityModes(aid);
        ownerController.selfActivityMode.remove(aid);
        db.deleteActivity(aid);
        activity = null; // help gc
        ownerController.activities.remove(aid);
        db.insertLog(aid, ownerController.user.getId(), String.format("撤销活动(no.%x)被授予的所有权限并删除活动", aid));
    }

    public void setDescription(String description) throws SQLException {
        db.updateActivityDescription(activity.getId(), description);
        activity.setDescription(description);
        db.insertLog(activity.getId(), ownerController.user.getId(), String.format("修改活动(no.%x)详情为：%s", activity.getId(), description));
    }

    public void setMoneyAim(int aim) throws AssertionError, SQLException {
        assert activity instanceof MoneySavingActivity;
        MoneySavingActivity activity = (MoneySavingActivity) this.activity;
        activity.setAim(aim);
        db.updateActivityStatus(activity.getId(), activity.getStatus());
        db.updateActivityDetail(activity.getId(), activity.getDetailInfo());
        db.insertLog(activity.getId(), ownerController.user.getId(), String.format("活动(no.%x)设置目标%d", activity.getId(), aim));
    }

    public void setRepeatCount(int count) throws AssertionError, SQLException {
        assert activity instanceof RepeatActivity;
        RepeatActivity activity = (RepeatActivity) this.activity;
        activity.setCount(count);
        db.updateActivityStatus(activity.getId(), activity.getStatus());
        db.updateActivityDetail(activity.getId(), activity.getDetailInfo());
        db.insertLog(activity.getId(), ownerController.user.getId(), String.format("活动(no.%x)设置次数%d", activity.getId(), count));
    }

    public void setZenLasting(int lasting) throws AssertionError, SQLException {
        assert activity instanceof ZenModeActivity;
        ZenModeActivity activity = (ZenModeActivity) this.activity;
        activity.setLasting(lasting);
        db.updateActivityDetail(activity.getId(), activity.getDetailInfo());
        db.insertLog(activity.getId(), ownerController.user.getId(), String.format("活动(no.%x)设置时长%d s", activity.getId(), lasting));
    }

    public List<String> getDetail() {
        List<String> result = new LinkedList<>();
        result.add("活动类型：" + activity.getType());
        result.add("详细信息：" + activity.getDescription());
        result.add("活动状态：" + activity.getStatus());
        if (activity instanceof MoneySavingActivity) {
            MoneySavingActivity activity = (MoneySavingActivity) this.activity;
            result.add(String.format("目标金额：%d，已用金额：%d", activity.getAim(), activity.getUsed()));
        } else if (activity instanceof RepeatActivity) {
            RepeatActivity activity = (RepeatActivity) this.activity;
            result.add(String.format("剩余执行次数：%d", activity.getCount()));
        } else if (activity instanceof ZenModeActivity) {
            ZenModeActivity activity = (ZenModeActivity) this.activity;
            result.add(String.format("禅定模式持续时间：%d", activity.getLasting()));
            result.add(String.format("禅定模式开始时间：%s", activity.getBegin()));
        }
        return result;
    }

    public String getTitle() {
        return activity.getName();
    }

    public boolean canPunchIn() {
        return !activity.getStatus().equals(BasicActivity.FINISH_STATUS);
    }

    public String getLog() throws SQLException {
        return String.join("\n", db.selectActivityLog(activity.getId()));
    }

    public String getMode() {
        return mode;
    }
}
