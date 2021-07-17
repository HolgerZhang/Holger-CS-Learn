package lottery;

import java.util.Date;
import java.util.Random;

/**
 * 员工抽象类
 */
public abstract class Staff {
    private static final Random RANDOM_GENERATOR = new Random(new Date().getTime());  // 随机数生成器
    private static final int LOWER_BOUND = 200;   // 随机标签下界
    private static final int UPPER_BOUND = 3000; // 随机标签上界
    private final String level;  // 自身的级别信息

    /**
     * 统一构造方法
     *
     * @param level 提供自身的级别信息
     */
    protected Staff(String level) {
        this.level = level;
    }

    /**
     * 抽取多个随机标签
     *
     * @param size 标签个数
     * @return size 个 200 ~ 3000 间的随机整数作为标签数组
     */
    protected static int[] extractRandomLabels(int size) {
        int[] numbers = new int[size];
        for (int i = 0; i < size; i++) {
            numbers[i] = LOWER_BOUND + RANDOM_GENERATOR.nextInt(UPPER_BOUND - LOWER_BOUND + 1);
        }
        return numbers;
    }

    /**
     * [抽象方法] 生成抽取到的最终的标签
     *
     * @return 最终抽取到的标签
     */
    public abstract int extract();

    /**
     * 统一的获取自身的级别信息方法
     *
     * @return 自身的级别信息
     */
    public final String getLevel() {
        return this.level;
    }

}
