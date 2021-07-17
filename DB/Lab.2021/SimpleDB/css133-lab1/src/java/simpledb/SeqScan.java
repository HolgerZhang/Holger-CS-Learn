package simpledb;

import java.util.*;

/**
 * SeqScan is an implementation of a sequential scan access method that reads
 * each tuple of a table in no particular order (e.g., as they are laid out on
 * disk).
 */
public class SeqScan implements DbIterator {

    private static final long serialVersionUID = 1L;

    private TransactionId tid;  // 事务id
    private int tableId;   // 表号
    private String alias;  // 别名
    private DbFileIterator iterator;  // 文件迭代器，遍历DB文件用

    /**
     * Creates a sequential scan over the specified table as a part of the
     * specified transaction.
     * 
     * @param tid
     *            The transaction this scan is running as a part of.
     * @param tableid
     *            the table to scan.
     * @param tableAlias
     *            the alias of this table (needed by the parser); the returned
     *            tupleDesc should have fields with name tableAlias.fieldName
     *            (note: this class is not responsible for handling a case where
     *            tableAlias or fieldName are null. It shouldn't crash if they
     *            are, but the resulting name can be null.fieldName,
     *            tableAlias.null, or null.null).
     */
    // 作为指定事务的一部分，在指定表上创建顺序扫描。
    // 参数为事务id，表号，该表的别名（tableAlias，可以为空）
    // 返回的 tupleDesc 应该有名称为tableAlias.fieldName的字段
    public SeqScan(TransactionId tid, int tableid, String tableAlias) {
        // some code goes here
        this.tid = tid;
        this.tableId  = tableid;
        if (tableAlias != null){
            this.alias = tableAlias;
        } else {
            this.alias = "null";
        }
        this.iterator = Database.getCatalog().getDatabaseFile(tableid).iterator(tid);
    }

    /**
     * @return
     *       return the table name of the table the operator scans. This should
     *       be the actual name of the table in the catalog of the database
     * */
    public String getTableName() {
        return Database.getCatalog().getTableName(this.tableId);
    }
    
    /**
     * @return Return the alias of the table this operator scans. 
     * */
    public String getAlias()    {  // alias Getter
        // some code goes here
        return this.alias;
    }

    /**
     * Reset the tableid, and tableAlias of this operator.
     * @param tableid
     *            the table to scan.
     * @param tableAlias
     *            the alias of this table (needed by the parser); the returned
     *            tupleDesc should have fields with name tableAlias.fieldName
     *            (note: this class is not responsible for handling a case where
     *            tableAlias or fieldName are null. It shouldn't crash if they
     *            are, but the resulting name can be null.fieldName,
     *            tableAlias.null, or null.null).
     */
    // 重置表号和别名
    public void reset(int tableid, String tableAlias) {
        // some code goes here
        this.tableId = tableid;
        if (tableAlias != null){
            this.alias = tableAlias;
        } else {
            this.alias = "null";
        }
        this.iterator = Database.getCatalog().getDatabaseFile(tableid).iterator(tid);
    }

    public SeqScan(TransactionId tid, int tableid) {
        this(tid, tableid, Database.getCatalog().getTableName(tableid));
    }

    public void open() throws DbException, TransactionAbortedException {
        // some code goes here
        this.iterator.open();
    }

    /**
     * Returns the TupleDesc with field names from the underlying HeapFile,
     * prefixed with the tableAlias string from the constructor. This prefix
     * becomes useful when joining tables containing a field(s) with the same
     * name. The alias and name should be separated with a "." character
     * (e.g., "alias.fieldName").
     * 
     * @return the TupleDesc with field names from the underlying HeapFile,
     *         prefixed with the tableAlias string from the constructor.
     */
    // 返回TupleDesc，其中包含来自底层HeapFile的字段名，并以来自构造函数的tableAlias字符串作为前缀。
    public TupleDesc getTupleDesc() {
        // some code goes here
        // 获取原始TupleDesc
        TupleDesc desc = Database.getCatalog().getTupleDesc(this.tableId);
        int numFields = desc.numFields();
        Type[] types = new Type[numFields];
        String[] names = new String[numFields];
        for (int i = 0; i < numFields; i++) {
            // 添加前缀
            types[i] = desc.getFieldType(i);
            String fieldName = desc.getFieldName(i);
            if (fieldName == null) {
                fieldName = "null";
            }
            names[i] = this.alias + "." + fieldName;
        }
        return new TupleDesc(types, names);
    }

    public boolean hasNext() throws TransactionAbortedException, DbException {
        // some code goes here
        return this.iterator.hasNext();
    }

    public Tuple next() throws NoSuchElementException,
            TransactionAbortedException, DbException {
        // some code goes here
        return this.iterator.next();
    }

    public void close() {
        // some code goes here
        this.iterator.close();
    }

    public void rewind() throws DbException, NoSuchElementException,
            TransactionAbortedException {
        // some code goes here
        this.iterator.rewind();
    }
}
