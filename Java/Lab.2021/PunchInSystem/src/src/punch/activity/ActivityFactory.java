package punch.activity;

// 活动类工厂
public class ActivityFactory {
    public static final String[] ACTIVITY_TYPES = {BasicActivity.TYPE, RepeatActivity.TYPE, ZenModeActivity.TYPE, MoneySavingActivity.TYPE};
    public static String[] ACTIVITY_TYPES_WITH_ALL = {"ALL", BasicActivity.TYPE, RepeatActivity.TYPE, ZenModeActivity.TYPE, MoneySavingActivity.TYPE};

    public static BasicActivity createActivity(long id,
                                               String name,
                                               String type,
                                               String statue,
                                               String description,
                                               String detailInfo)
            throws IllegalArgumentException {
        BasicActivity activity = createSimpleActivity(type, name, description);
        activity.setId(id);
        activity.setStatus(statue);
        activity.setDetailInfo(detailInfo);
        return activity;
    }

    public static BasicActivity createSimpleActivity(String type, String name, String description)
            throws IllegalArgumentException {
        BasicActivity activity;
        switch (type) {
            case BasicActivity.TYPE:
                activity = new BasicActivity(name, description);
                break;
            case RepeatActivity.TYPE:
                activity = new RepeatActivity(name, description);
                break;
            case ZenModeActivity.TYPE:
                activity = new ZenModeActivity(name, description);
                break;
            case MoneySavingActivity.TYPE:
                activity = new MoneySavingActivity(name, description);
                break;
            default:
                throw new IllegalArgumentException("未知的活动类型");
        }
        return activity;
    }

}
