package lottery;

/**
 * 普通员工类
 */
public class CommStaff extends Staff {

    public CommStaff() {
        super("Common Staff");
    }

    /**
     * 生成抽取到的最终的标签
     * 可以抽 10 次，取 10 次间的差值（第 i 次的值减去第 i-1 次的值称为一次差值）之和为最终的标签。
     * @return 最终抽取到的标签
     */
    @Override
    public int extract() {
        int label = 0;  // 最终抽取到的标签
        int[] labels = extractRandomLabels(10);
        for (int i = 1; i < 10; i++) {
            label += labels[i] - labels[i - 1];
        }
        return label;
    }
}
