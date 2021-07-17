package punch.ui.controller;

import punch.activity.BasicActivity;
import punch.activity.MoneySavingActivity;
import punch.db.Database;
import punch.user.User;

import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MainController {

    final User user;
    final Map<Long, String> selfActivityMode;
    final Map<Long, BasicActivity> activities;
    Database db = Database.getInstance();

    public MainController(User user) throws SQLException {
        this.user = user;
        selfActivityMode = db.selectUserActivityIdWithMode(user.getId());
        activities = new HashMap<>();
        for (Map.Entry<Long, String> entry : selfActivityMode.entrySet()) {
            BasicActivity activity = db.selectActivity(entry.getKey());
            activities.put(activity.getId(), activity);
        }
    }

    public Set<Long> listActivities() {
        return activities.keySet();
    }

    public BasicActivity getActivity(long aid) {
        return activities.get(aid);
    }

    public String getActivityMode(long aid) {
        return selfActivityMode.get(aid);
    }

    public void newActivity(BasicActivity activity, Map<Long, String> grantUsers) throws SQLException {
        db.insertActivity(activity);
        activities.put(activity.getId(), activity);
        db.insertLog(activity.getId(), user.getId(), String.format("创建活动'%s'(no.%x)", activity.getName(), activity.getId()));
        db.insertActivityMode(user.getId(), activity.getId(), BasicActivity.OWN_A_MODE);
        selfActivityMode.put(activity.getId(), BasicActivity.OWN_A_MODE);
        if (grantUsers == null) return;
        for (Map.Entry<Long, String> entry : grantUsers.entrySet()) {
            db.insertActivityMode(entry.getKey(), activity.getId(), entry.getValue());
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            db.insertLog(activity.getId(),
                    user.getId(),
                    String.format("授予用户(no.%x)对活动'%s'(no.%x)的%s权限", entry.getKey(), activity.getName(), activity.getId(), entry.getValue()));
        }
    }

    public void activityPunchIn(long aid, Integer i) throws SQLException, IllegalStateException {
        BasicActivity activity = activities.get(aid);
        if (i != null && activity instanceof MoneySavingActivity) {
            ((MoneySavingActivity) activity).punch(i);
        } else {
            activity.punch();
        }
        db.updateActivityStatus(aid, activity.getStatus());
        db.updateActivityDetail(aid, activity.getDetailInfo());
        db.insertLog(aid, user.getId(), String.format("设备(no.%x)执行打卡，结束状态：%s", aid, activity.getStatus()));
    }

    public String getLog() throws SQLException {
        return String.join("\n", db.selectUserLog(user.getId()));
    }

    public long getUserId(String username) throws SQLException {
        return db.selectUser(username).getId();
    }

    public String getUserRole() {
        return user.getRole();
    }
}
