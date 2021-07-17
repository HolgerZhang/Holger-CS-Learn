package simpledb;

import java.io.Serializable;

/**
 * A RecordId is a reference to a specific tuple on a specific page of a
 * specific table.
 */
public class RecordId implements Serializable {

    private static final long serialVersionUID = 1L;

    private final PageId pageId;  // 特定页
    private final int tupleNumber;  // 特定元组

    /**
     * Creates a new RecordId referring to the specified PageId and tuple
     * number.
     * 
     * @param pid
     *            the pageid of the page on which the tuple resides
     * @param tupleno
     *            the tuple number within the page.
     */
    // 构造方法，为特定页的特定元组创建一个记录id。根据传入的页号和元组号构造
    public RecordId(PageId pid, int tupleno) {
        // some code goes here
        this.pageId = pid;
        this.tupleNumber = tupleno;
    }

    /**
     * @return the tuple number this RecordId references.
     */
    public int getTupleNumber() {  // tupleNumber Getter
        // some code goes here
        return this.tupleNumber;
    }

    /**
     * @return the page id this RecordId references.
     */
    public PageId getPageId() {  // pageId Getter
        // some code goes here
        return this.pageId;
    }

    /**
     * Two RecordId objects are considered equal if they represent the same
     * tuple.
     * 
     * @return True if this and o represent the same tuple
     */
    @Override
    public boolean equals(Object o) {  // 判断相等
        // some code goes here
        if (this == o) {  // 同一对象
            return true;
        } else if (o instanceof RecordId) {
            // 相同类型，页号和元组号都相同才相等
            RecordId other = (RecordId) o;
            return this.pageId.equals(other.pageId) && this.tupleNumber == other.tupleNumber;
        }
        return false;
    }

    /**
     * You should implement the hashCode() so that two equal RecordId instances
     * (with respect to equals()) have the same hashCode().
     * 
     * @return An int that is the same for equal RecordId objects.
     */
    // 记录的哈希代码，由页号和元组的连接表示
    @Override
    public int hashCode() {
        // some code goes here
        // 使用质数31*页号+元组号实现
        return 31 * this.pageId.hashCode() + this.tupleNumber;
    }

}
