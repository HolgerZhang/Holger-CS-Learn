package studentCardRecord.entity;

public class Record {
    /**
     * 用卡类型枚举
     */
    public enum RecordType {
        DEPOSIT,    // 存钱操作
        CONSUME     // 消费操作
    }

    private final String cardId;        // 卡号
    private final RecordType type;      // 用卡类型
    private final double amount;        // 发生金额
    private final int place;            // 发生地点编号

    public Record(String cardId, RecordType type, double amount, int place) {
        this.cardId = cardId;
        this.type = type;
        this.amount = amount;
        this.place = place;
    }

    public String getCardId() {
        return cardId;
    }

    public RecordType getType() {
        return this.type;
    }

    public double getAmount() {
        return this.amount;
    }

    public int getPlace() {
        return this.place;
    }

    public String consumptionInformation() {
        String typeString = "";
        switch (this.type) {
            case DEPOSIT:
                typeString = "存钱";
                break;
            case CONSUME:
                typeString = "消费";
                break;
        }
        return String.format("%s 金额：%.2f 消费地点：%d", typeString, this.amount, this.place);
    }

}
