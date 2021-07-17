package lottery;

/**
 * 杰出员工类
 */
public class OutstandingStaff extends Staff {

    public OutstandingStaff() {
        super("Outstanding Staff");
    }

    /**
     * 判断是否构成数字的阶乘之和恰好等于该数数字（即是否为水仙花数）
     *
     * @param number 要判断的数字
     * @return 是否为水仙花数
     */
    private static boolean isNarcissisticNumber(int number) {
        int sum = 0;
        for (char ch : Integer.toString(number).toCharArray()) {
            sum += factorial(Character.getNumericValue(ch));
        }
        return sum == number;
    }

    /**
     * 计算阶乘
     *
     * @param number 非负整数
     * @return 该数字的阶乘
     */
    private static int factorial(int number) {
        if (number <= 1) {
            return 1;
        }
        return number * factorial(number - 1);
    }

    /**
     * 生成抽取到的最终的标签
     * 抽 20 次，每次抽到的是偶数，则记为正数，是奇数，则记为相反数（负数），
     * 但若抽中标签的构成数字的阶乘之和恰好等于该标签数（为水仙花数），则记为 0。
     * 最终求得 20 次结果之和的绝对值作为最终标签。
     *
     * @return 最终抽取到的标签
     */
    @Override
    public int extract() {
        int label = 0;  // 最终抽取到的标签
        for (int number : extractRandomLabels(20)) {
            if (isNarcissisticNumber(number)) {
                label += 0;
            } else if (number % 2 != 0) {
                label += -number;
            } else {
                label += number;
            }
        }
        return Math.abs(label);
    }
}
