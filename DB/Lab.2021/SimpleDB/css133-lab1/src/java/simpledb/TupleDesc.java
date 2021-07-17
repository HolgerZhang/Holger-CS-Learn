package simpledb;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * TupleDesc describes the schema of a tuple.
 */
public class TupleDesc implements Serializable {

    /**
     * A help class to facilitate organizing the information of each field
     */
    public static class TDItem implements Serializable {

        private static final long serialVersionUID = 1L;

        /**
         * The type of the field
         */
        public final Type fieldType;

        /**
         * The name of the field
         */
        public final String fieldName;

        public TDItem(Type t, String n) {
            this.fieldName = n;
            this.fieldType = t;
        }

        public String toString() {
            return fieldName + "(" + fieldType + ")";
        }
    }


    private final TDItem[] items;  // 特定类型的字段

    /**
     * @return
     *        An iterator which iterates over all the field TDItems
     *        that are included in this TupleDesc
     * */
    // 返回字段的迭代器
    public Iterator<TDItem> iterator() {
        // 使用 Java8 流来获取各字段的迭代器
        return Arrays.stream(this.items).iterator();
    }

    /**
     * Create a new TupleDesc with typeAr.length fields with fields of the
     * specified types, with associated named fields.
     *
     * @param typeAr
     *            array specifying the number of and types of fields in this
     *            TupleDesc. It must contain at least one entry.
     * @param fieldAr
     *            array specifying the names of the fields. Note that names may
     *            be null.
     */
    // 构造函数，使用字段类型数组+字段名数组初始化
    public TupleDesc(Type[] typeAr, String[] fieldAr) {
        // some code goes here
        // 判断参数是否合法
        if (typeAr.length <= 0) {
            throw new IllegalArgumentException("typeAr 的长度应大于0");
        }
        if (typeAr.length != fieldAr.length) {
            throw new IllegalArgumentException("typeAr 和 fieldAr 大小应相同");
        }
        // 构造各字段并初始化
        this.items = new TDItem[typeAr.length];
        for (int i = 0; i < typeAr.length; ++i) {
            this.items[i] = new TDItem(typeAr[i], fieldAr[i]);
        }
    }

    /**
     * Constructor. Create a new tuple desc with typeAr.length fields with
     * fields of the specified types, with anonymous (unnamed) fields.
     *
     * @param typeAr
     *            array specifying the number of and types of fields in this
     *            TupleDesc. It must contain at least one entry.
     */
    // 构造函数，使用字段类型数组初始化
    public TupleDesc(Type[] typeAr) {
        // some code goes here
        this(typeAr, new String[typeAr.length]);
    }

    /**
     * @return the number of fields in this TupleDesc
     */
    // 返回字段数量
    public int numFields() {
        // some code goes here
        return this.items.length;
    }

    /**
     * Gets the (possibly null) field name of the ith field of this TupleDesc.
     *
     * @param i
     *            index of the field name to return. It must be a valid index.
     * @return the name of the ith field
     * @throws NoSuchElementException
     *             if i is not a valid field reference.
     */
    // 获取指定索引的字段名，不存在抛出 NoSuchElementException
    public String getFieldName(int i) throws NoSuchElementException {
        // some code goes here
        this.checkIndex(i); // 检查是否存在，若不存在抛异常
        return this.items[i].fieldName;
    }

    /**
     * Check index
     * @param i index
     */
    // 检查索引值i是否合法
    private void checkIndex(int i) throws NoSuchElementException {
        if (i < 0 || i >= this.items.length) {
            throw new NoSuchElementException(String.format("索引值 %d 不合法", i));
        }
    }

    /**
     * Gets the type of the ith field of this TupleDesc.
     *
     * @param i
     *            The index of the field to get the type of. It must be a valid
     *            index.
     * @return the type of the ith field
     * @throws NoSuchElementException
     *             if i is not a valid field reference.
     */
        // 获取指定索引的字段类型，不存在抛出 NoSuchElementException
    public Type getFieldType(int i) throws NoSuchElementException {
        // some code goes here
        this.checkIndex(i);
        return this.items[i].fieldType;
    }

    /**
     * Find the index of the field with a given name.
     * No match if name is null.
     *
     * @param name
     *            name of the field.
     * @return the index of the field that is first to have the given name.
     * @throws NoSuchElementException
     *             if no field with a matching name is found.
     */
    // 根据字段名找其索引，不存在抛出 NoSuchElementException
    public int fieldNameToIndex(String name) throws NoSuchElementException {
        // some code goes here
        for (int index = 0; index < this.items.length; ++index) {
            String fieldName = this.items[index].fieldName;
            if (fieldName != null && fieldName.equals(name)) { // 注意：fieldName可能为空
                return index;
            }
        }
        throw new NoSuchElementException("字段'" + name + "'未找到");
    }

    /**
     * @return The size (in bytes) of tuples corresponding to this TupleDesc.
     *         Note that tuples from a given TupleDesc are of a fixed size.
     * @see Type#getSizeInBytes
     */
    // 返回TupleDesc所占字节数
    public int getSizeInBytes() {
        // some code goes here
        int total = 0;
        for (TDItem item : this.items) {
            total += item.fieldType.getSizeInBytes();
        }
        return total;
    }

    /**
     * Merge two TupleDescs into one, with td1.numFields + td2.numFields fields,
     * with the first td1.numFields coming from td1 and the remaining from td2.
     *
     * @param td1
     *            The TupleDesc with the first fields of the new TupleDesc
     * @param td2
     *            The TupleDesc with the last fields of the TupleDesc
     * @return the new TupleDesc
     */
    // 合并两个TupleDesc td1+td2
    public static TupleDesc merge(TupleDesc td1, TupleDesc td2) {
        // some code goes here
        int length1 = td1.items.length;
        int length2 = td2.items.length;
        int length = length1 + length2;
        Type[] types = new Type[length];
        String[] names = new String[length];
        for (int i = 0; i < length1; ++i) {
            types[i] = td1.items[i].fieldType;
            names[i] = td1.items[i].fieldName;
        }
        for (int i = 0; i < length2; ++i) {
            types[length1 + i] = td2.items[i].fieldType;
            names[length1 + i] = td2.items[i].fieldName;
        }
        return new TupleDesc(types, names);
    }

    /**
     * Compares the specified object with this TupleDesc for equality. Two
     * TupleDescs are considered equal if they have the same number of items
     * and if the i-th type in this TupleDesc is equal to the i-th type in o
     * for every i. It does not matter if the field names are equal.
     *
     * @param o the Object to be compared for equality with this TupleDesc.
     * @return true if the object is equal to this TupleDesc.
     */
    // 判断是否相等
    public boolean equals(Object o) {
        // some code goes here
        if (this == o) {  // 同一对象
            return true;
        }
        if (o instanceof TupleDesc) {  // 类型相同才比较
            // 根据文档注释：Two TupleDescs are considered equal if they have the same number of items
            // and the i-th type in this TupleDesc is equal to the i-th type in o for every i.
            // 即相等的条件是：两者字段数相同，对应位置上的字段类型相同
            TupleDesc other = (TupleDesc) o;
            if (this.items.length != other.items.length) {
                return false;
            }
            for (int i = 0; i < this.items.length; ++i) {
                if (!(this.items[i].fieldType.equals(other.items[i].fieldType))) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    public int hashCode() {
        // If you want to use TupleDesc as keys for HashMap, implement this so
        // that equal objects have equals hashCode() results
        throw new UnsupportedOperationException("unimplemented");
    }

    /**
     * Returns a String describing this descriptor. It should be of the form
     * "fieldName[0](fieldType[0]), ..., fieldName[M](fieldType[M])", although
     * the exact format does not matter.
     *
     * @return String describing this descriptor.
     */
    public String toString() {  // 格式化为字符串
        // some code goes here
        StringBuilder str = new StringBuilder("TupleDesc: ");
        for (int i = 0; i < this.items.length; i++) {
            str.append(this.items[i]);
            if (this.items.length - 1 != i) {
                str.append(", ");
            }
        }
        return str.toString();
    }
}
