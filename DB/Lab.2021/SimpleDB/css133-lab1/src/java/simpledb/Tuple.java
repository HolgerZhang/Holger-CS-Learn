package simpledb;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Tuple maintains information about the contents of a tuple. Tuples have a
 * specified schema specified by a TupleDesc object and contain Field objects
 * with the data for each field.
 */
public class Tuple implements Serializable {

    private static final long serialVersionUID = 1L;

    private TupleDesc desc;   // 关系模式
    private final Field[] fields;  // 元组字段数组
    private RecordId id;    // 该元组的记录编号信息
    /**
     * Create a new tuple with the specified schema (type).
     *
     * @param td
     *            the schema of this tuple. It must be a valid TupleDesc
     *            instance with at least one field.
     */
    // 构造函数，使用模式（TupleDesc）创建
    public Tuple(TupleDesc td) {
        // some code goes here
        this.desc = td;
        this.fields = new Field[td.numFields()];    // 生成对应长度的字段数组
        this.id = null;
    }

    /**
     * @return The TupleDesc representing the schema of this tuple.
     */
    public TupleDesc getTupleDesc() {  // 获取模式
        // some code goes here
        return this.desc;
    }

    /**
     * @return The RecordId representing the location of this tuple on disk.
     * Should return RecordId that was set with setRecordId(). May be null.
     */
    public RecordId getRecordId() {  // 获取记录编号信息
        // some code goes here
        return this.id;
    }

    /**
     * Set the RecordId information for this tuple.
     *
     * @param rid the new RecordId for this tuple.
     */
    public void setRecordId(RecordId rid) {  // 设置获取记录编号信息
        // some code goes here
        this.id = rid;
    }

    /**
     * Change the value of the ith field of this tuple.
     *
     * @param i index of the field to change. It must be a valid index.
     * @param f new value for the field.
     */
     // 通过索引插入字段，索引不存在报错
    public void setField(int i, Field f) {
        // some code goes here
        if (i < 0 || i >= this.fields.length) {
            throw new NoSuchElementException(i + " is not a valid index.");
        }
        this.fields[i] = f;
    }

    /**
     * @param i field index to return. Must be a valid index.
     * @return the value of the ith field, or null if it has not been set.
     */
     // 通过索引获取字段，索引不存在报错
    public Field getField(int i) {
        // some code goes here
        if (i < 0 || i >= this.fields.length) {
            throw new NoSuchElementException(i + " is not a valid index.");
        }
        return this.fields[i];
    }

    /**
     * Returns the contents of this Tuple as a string. Note that to pass the
     * system tests, the format needs to be as follows:
     * <p>
     * column1\tcolumn2\tcolumn3\t...\tcolumnN\n
     * <p>
     * where \t is any whitespace, except newline, and \n is a newline
     */
    public String toString() {  // 格式化为字符串
        // some code goes here
        // 各行格式：column1\tcolumn2\tcolumn3\t...\tcolumnN\n
        StringBuilder str = new StringBuilder();
        for (int i = 0; i < this.fields.length; i++) {
            str.append(fields[i]).append((this.fields.length - 1 == i) ? '\n' : '\t');
        }
        return str.toString();
    }

    /**
     * @return An iterator which iterates over all the fields of this tuple
     */
    // 获取字段迭代器
    public Iterator<Field> fields() {
        // some code goes here
        return Arrays.stream(this.fields).iterator();  // Java8 stream
    }

    /**
     * Reset the TupleDesc of this tuple
     * (Only affecting the TupleDesc, does not need to worry about fields inside the Tuple)
     */
    // 重置元组模式，仅影响模式，不影响字段
    public void resetTupleDesc(TupleDesc td) {
        // some code goes here
        this.desc = td;
    }
}
