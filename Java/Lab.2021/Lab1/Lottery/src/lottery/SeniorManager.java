package lottery;

/**
 * 企业高管类
 */
public class SeniorManager extends Staff {

    public SeniorManager() {
        super("Senior Manager");
    }

    /**
     * 生成抽取到的最终的标签
     * 抽 50 次，取其中构成数字之和最大的数作为最终标签。
     *
     * @return 最终抽取到的标签
     */
    @Override
    public int extract() {
        int label = 0;  // 最终抽取到的标签
        for (int number : extractRandomLabels(50)) {
            int sum = 0;
            for (char ch : Integer.toString(number).toCharArray()) {
                sum += Character.getNumericValue(ch);
            }
            label = Math.max(sum, label);
        }
        return label;
    }
}
