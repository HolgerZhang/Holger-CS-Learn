package lottery;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * 模拟主类
 */
public class Imitate {

    List<Staff> company;

    public Imitate() {
        this.company = new ArrayList<>();
        this.initStaff();
    }

    /**
     * 模拟员工进场和标签抽取
     *
     * @param stf 员工对象
     */
    static void play(Staff stf) {
        System.out.println("员工进场，身份级别为：" + stf.getLevel());
        System.out.println("员工抽取到的标签为：" + stf.extract());
    }

    /**
     * 初始化企业员工
     */
    private void initStaff() {
        Scanner scn = new Scanner(System.in);
        System.out.print("请输入企业高管数量：");
        int seniorNumber = scn.nextInt();
        if (seniorNumber < 0) seniorNumber = 0;
        System.out.print("请输入部门主管数量：");
        int departmentNumber = scn.nextInt();
        if (departmentNumber < 0) departmentNumber = 0;
        System.out.print("请输入杰出员工数量：");
        int outstandingNumber = scn.nextInt();
        if (outstandingNumber < 0) outstandingNumber = 0;
        System.out.print("请输入普通员工数量：");
        int commonNumber = scn.nextInt();
        if (commonNumber < 0) commonNumber = 0;
        scn.close();
        for (int i = 0; i < seniorNumber; i++) {
            this.company.add(new SeniorManager());
        }
        for (int i = 0; i < departmentNumber; i++) {
            this.company.add(new DepManager());
        }
        for (int i = 0; i < outstandingNumber; i++) {
            this.company.add(new OutstandingStaff());
        }
        for (int i = 0; i < commonNumber; i++) {
            this.company.add(new CommStaff());
        }
        System.out.printf("公司有%d名企业高管，%d名部门主管，%d名杰出员工，%d名普通员工\n",
                seniorNumber, departmentNumber, outstandingNumber, commonNumber);
    }

    public static void main(String[] args) {
        Imitate imitate = new Imitate();
        for (Staff stf : imitate.company) {
            System.out.println("--------------------------------------------------");
            play(stf);
        }
    }

}
