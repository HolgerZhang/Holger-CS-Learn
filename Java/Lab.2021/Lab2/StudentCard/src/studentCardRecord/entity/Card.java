package studentCardRecord.entity;

import java.util.LinkedList;
import java.util.List;

public class Card {
    private final String cardId;        // 10 位一卡通卡号
    private final List<Record> records; // 一卡通的用卡情况
    private double balance;             // 余额
    private double consume;             // 消费总金额
    private double deposit;             // 存款总金额

    public Card(String id) {
        this.cardId = id;
        this.records = new LinkedList<>();
        this.balance = 0.0;
        this.consume = 0.0;
        this.deposit = 0.0;
    }

    /**
     * 新增一条用卡信息
     *
     * @param record 用卡信息（消费记录类实例）
     */
    public void insert(Record record) {
        this.records.add(record);
        switch (record.getType()) {
            case DEPOSIT:
                this.balance += record.getAmount();
                this.deposit += record.getAmount();
                break;
            case CONSUME:
                this.balance -= record.getAmount();
                this.consume += record.getAmount();
                break;
        }
    }

    public String getCardId() {
        return this.cardId;
    }

    /**
     * 获取消费总金额
     *
     * @return 消费总金额
     */
    public double getConsume() {
        return this.consume;
    }

    /**
     * 获取存款总金额
     *
     * @return 存款总金额
     */
    public double getDeposit() {
        return this.deposit;
    }

    /**
     * 获取余额
     *
     * @return 余额
     */
    public double getBalance() {
        return this.balance;
    }

    public String briefInformation() {
        return "卡号：" + this.cardId + System.lineSeparator() +
                String.format("余额：%.2f", this.balance) + System.lineSeparator() +
                String.format("该卡共消费：%.2f", this.consume);
    }

    public String detailedInformation() {
        StringBuilder str = new StringBuilder();
        str.append("卡号：")
                .append(this.cardId)
                .append(System.lineSeparator())
                .append(String.format("余额：%.2f", this.balance))
                .append(System.lineSeparator());
        for (Record record : this.records) {
            str.append(record.consumptionInformation())
                    .append(System.lineSeparator());
        }
        str.append(String.format("该卡共消费：%.2f", this.consume));
        return str.toString();
    }
}
