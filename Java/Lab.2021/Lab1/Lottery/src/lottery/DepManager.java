package lottery;

/**
 * 部门主管类
 */
public class DepManager extends Staff {

    public DepManager() {
        super("Department Manager");
    }

    /**
     * 生成抽取到的最终的标签
     * 抽 30 次，每次抽到的是偶数，则记为正数，是奇数，则记为相反数（负数）。
     * 最终求得 30 次结果之和的绝对值作为最终标签。
     *
     * @return 最终抽取到的标签
     */
    @Override
    public int extract() {
        int label = 0;  // 最终抽取到的标签
        for (int number : extractRandomLabels(30)) {
            if (number % 2 != 0) {
                label += -number;
            } else {
                label += number;
            }
        }
        return Math.abs(label);
    }
}
