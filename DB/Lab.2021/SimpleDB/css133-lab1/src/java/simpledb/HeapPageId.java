package simpledb;

/** Unique identifier for HeapPage objects. */
public class HeapPageId implements PageId {

    private final int tableId;  // 特定表
    private final int pageNumber;  // 特定页

    /**
     * Constructor. Create a page id structure for a specific page of a
     * specific table.
     *
     * @param tableId The table that is being referenced
     * @param pgNo The page number in that table.
     */
    // 构造方法，为特定表的特定页创建一个堆页面id。根据传入的表id和页面号构造
    public HeapPageId(int tableId, int pgNo) {
        // some code goes here
        this.tableId = tableId;
        this.pageNumber = pgNo;
    }

    /** @return the table associated with this PageId */
    public int getTableId() {  // tableId Getter
        // some code goes here
        return this.tableId;
    }

    /**
     * @return the page number in the table getTableId() associated with
     *   this PageId
     */
    public int getPageNumber() {  // pageNumber Getter
        // some code goes here
        return this.pageNumber;
    }

    /**
     * @return a hash code for this page, represented by the concatenation of
     *   the table number and the page number (needed if a PageId is used as a
     *   key in a hash table in the BufferPool, for example.). You may want to 
     *   parse the concatenation as a long (Long.parseLong()) before casting to int.
     * @see BufferPool
     */

    // 页面的哈希代码，由表号和页号的连接表示
    public int hashCode() {
        // some code goes here
        // 使用质数31*表号+页号实现
        return 31 * this.tableId + this.pageNumber;
    }

    /**
     * Compares one PageId to another.
     *
     * @param o The object to compare against (must be a PageId)
     * @return true if the objects are equal (e.g., page numbers and table
     *   ids are the same)
     */
    public boolean equals(Object o) {  // 判断相等
        // some code goes here
        if (this == o) {  // 同一对象
            return true;
        } else if (o instanceof HeapPageId) {
            // 相同类型，表号和页号都相同才相等
            HeapPageId other = (HeapPageId) o;
            return this.pageNumber == other.pageNumber && this.tableId == other.tableId;
        }
        return false;
    }

    /**
     *  Return a representation of this object as an array of
     *  integers, for writing to disk.  Size of returned array must contain
     *  number of integers that corresponds to number of args to one of the
     *  constructors.
     */
    public int[] serialize() {
        int data[] = new int[2];

        data[0] = getTableId();
        data[1] = getPageNumber();

        return data;
    }

}
