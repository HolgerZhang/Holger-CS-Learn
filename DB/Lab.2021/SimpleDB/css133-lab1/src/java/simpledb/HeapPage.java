package simpledb;

import java.util.*;
import java.io.*;

/**
 * Each instance of HeapPage stores data for one page of HeapFiles and 
 * implements the Page interface that is used by BufferPool.
 *
 * @see HeapFile
 * @see BufferPool
 *
 */
public class HeapPage implements Page {

    final HeapPageId pid;
    final TupleDesc td;
    final byte header[];
    final Tuple tuples[];
    final int numSlots;

    byte[] oldData;
    private final Byte oldDataLock=new Byte((byte)0);

    /**
     * Create a HeapPage from a set of bytes of data read from disk.
     * The format of a HeapPage is a set of header bytes indicating
     * the slots of the page that are in use, some number of tuple slots.
     *  Specifically, the number of tuples is equal to: <p>
     *          floor((BufferPool.getPageSize()*8) / (tuple size * 8 + 1))
     * <p> where tuple size is the size of tuples in this
     * database table, which can be determined via {@link Catalog#getTupleDesc}.
     * The number of 8-bit header words is equal to:
     * <p>
     *      ceiling(no. tuple slots / 8)
     * <p>
     * @see Database#getCatalog
     * @see Catalog#getTupleDesc
     * @see BufferPool#getPageSize()
     */
    public HeapPage(HeapPageId id, byte[] data) throws IOException {
        this.pid = id;
        this.td = Database.getCatalog().getTupleDesc(id.getTableId());
        this.numSlots = getNumTuples();
        DataInputStream dis = new DataInputStream(new ByteArrayInputStream(data));

        // allocate and read the header slots of this page
        header = new byte[getHeaderSize()];
        for (int i=0; i<header.length; i++)
            header[i] = dis.readByte();
        
        tuples = new Tuple[numSlots];
        try{
            // allocate and read the actual records of this page
            for (int i=0; i<tuples.length; i++)
                tuples[i] = readNextTuple(dis,i);
        }catch(NoSuchElementException e){
            e.printStackTrace();
        }
        dis.close();

        setBeforeImage();
    }
    // 构造函数的实现省略

    /** Retrieve the number of tuples that can be stored on this page.
        @return the number of tuple slots on this page
    */
    // 检索可存储在此页上的元组的数目
    private int getNumTuples() {
        // some code goes here
        // 根据构造函数的文档注释：元组的个数等于 floor((BufferPool.getPageSize()*8) / (tuple size * 8 + 1))
        return (int) Math.floor((BufferPool.getPageSize() * 8.0) / (this.td.getSizeInBytes() * 8 + 1));
    }

    /**
     * Computes the number of bytes in the header of a page in a HeapFile with each tuple occupying tupleSize bytes
     * @return the number of bytes in the header of a page in a HeapFile with each tuple occupying tupleSize bytes
     */
    // 计算HeapFile中header的字节数，每个元组占用tupleSize字节
    private int getHeaderSize() {
        // some code goes here
        // 根据构造函数的文档注释：8位header字的数目等于 ceiling(no. tuple slots / 8)
        return (int) Math.ceil(this.numSlots / 8.0);
    }
    
    /** Return a view of this page before it was modified
        -- used by recovery */
    public HeapPage getBeforeImage(){
        try {
            byte[] oldDataRef = null;
            synchronized(oldDataLock)
            {
                oldDataRef = oldData;
            }
            return new HeapPage(pid,oldDataRef);
        } catch (IOException e) {
            e.printStackTrace();
            //should never happen -- we parsed it OK before!
            System.exit(1);
        }
        return null;
    }
    
    public void setBeforeImage() {
        synchronized(oldDataLock)
        {
        oldData = getPageData().clone();
        }
    }

    /**
     * @return the PageId associated with this page.
     */
    public HeapPageId getId() {  // pid Getter
    // some code goes here
        return this.pid;
    }

    /**
     * Suck up tuples from the source file.
     */
    private Tuple readNextTuple(DataInputStream dis, int slotId) throws NoSuchElementException {
        // if associated bit is not set, read forward to the next tuple, and
        // return null.
        if (!isSlotUsed(slotId)) {
            for (int i=0; i<td.getSizeInBytes(); i++) {
                try {
                    dis.readByte();
                } catch (IOException e) {
                    throw new NoSuchElementException("error reading empty tuple");
                }
            }
            return null;
        }

        // read fields in the tuple
        Tuple t = new Tuple(td);
        RecordId rid = new RecordId(pid, slotId);
        t.setRecordId(rid);
        try {
            for (int j=0; j<td.numFields(); j++) {
                Field f = td.getFieldType(j).parse(dis);
                t.setField(j, f);
            }
        } catch (java.text.ParseException e) {
            e.printStackTrace();
            throw new NoSuchElementException("parsing error!");
        }

        return t;
    }

    /**
     * Generates a byte array representing the contents of this page.
     * Used to serialize this page to disk.
     * <p>
     * The invariant here is that it should be possible to pass the byte
     * array generated by getPageData to the HeapPage constructor and
     * have it produce an identical HeapPage object.
     *
     * @see #HeapPage
     * @return A byte array correspond to the bytes of this page.
     */
    public byte[] getPageData() {
        int len = BufferPool.getPageSize();
        ByteArrayOutputStream baos = new ByteArrayOutputStream(len);
        DataOutputStream dos = new DataOutputStream(baos);

        // create the header of the page
        for (int i=0; i<header.length; i++) {
            try {
                dos.writeByte(header[i]);
            } catch (IOException e) {
                // this really shouldn't happen
                e.printStackTrace();
            }
        }

        // create the tuples
        for (int i=0; i<tuples.length; i++) {

            // empty slot
            if (!isSlotUsed(i)) {
                for (int j=0; j<td.getSizeInBytes(); j++) {
                    try {
                        dos.writeByte(0);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                }
                continue;
            }

            // non-empty slot
            for (int j=0; j<td.numFields(); j++) {
                Field f = tuples[i].getField(j);
                try {
                    f.serialize(dos);
                
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        // padding
        int zerolen = BufferPool.getPageSize() - (header.length + td.getSizeInBytes() * tuples.length); //- numSlots * td.getSizeInBytes();
        byte[] zeroes = new byte[zerolen];
        try {
            dos.write(zeroes, 0, zerolen);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            dos.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return baos.toByteArray();
    }

    /**
     * Static method to generate a byte array corresponding to an empty
     * HeapPage.
     * Used to add new, empty pages to the file. Passing the results of
     * this method to the HeapPage constructor will create a HeapPage with
     * no valid tuples in it.
     *
     * @return The returned ByteArray.
     */
    public static byte[] createEmptyPageData() {
        int len = BufferPool.getPageSize();
        return new byte[len]; //all 0
    }

    /**
     * Delete the specified tuple from the page;  the corresponding header bit should be updated to reflect
     *   that it is no longer stored on any page.
     * @throws DbException if this tuple is not on this page, or tuple slot is
     *         already empty.
     * @param t The tuple to delete
     */
    public void deleteTuple(Tuple t) throws DbException {
        // some code goes here
        // not necessary for lab1
    }

    /**
     * Adds the specified tuple to the page;  the tuple should be updated to reflect
     *  that it is now stored on this page.
     * @throws DbException if the page is full (no empty slots) or tupledesc
     *         is mismatch.
     * @param t The tuple to add.
     */
    public void insertTuple(Tuple t) throws DbException {
        // some code goes here
        // not necessary for lab1
    }

    /**
     * Marks this page as dirty/not dirty and record that transaction
     * that did the dirtying.
     * Note: this method is called by BufferPool; a HeapPage should not 
     * mark itself as dirty or not.
     */
    public void markDirty(boolean dirty, TransactionId tid) {
        // some code goes here
	// not necessary for lab1
    }

    /**
     * Returns the tid of the transaction that last dirtied this page, or null if the page is not dirty
     */
    public TransactionId isDirty() {
        // some code goes here
	// Not necessary for lab1
        return null;      
    }

    /**
     * Returns the number of empty slots on this page.
     */
    // 返回此页上的空槽数
    public int getNumEmptySlots() {
        // some code goes here
        int slots = 0;
        for (int i = 0; i < this.numSlots; i++) {
            // 逐个槽判断是否为空
            if (!this.isSlotUsed(i)) {
                slots++;
            }
        }
        return slots;
    }

    /**
     * Returns true if associated slot on this page is filled.
     */
    // 判断此页上的相关槽位是否已填满
    public boolean isSlotUsed(int i) {
        // some code goes here
        // 根据guideline：
        // 1. The low bits of each byte represents the status of the slots that are earlier in the file.
        // （每个字节的低位表示文件中较早的槽的状态）
        // 2. JVM is big-endian （高位编址，高序字节存储在起始地址）
        // 例如：18 个槽，全部填满，header为（下面的'.'为分隔符）
        // header:    [1.1.1.1.1.1.1.1,  1. 1. 1. 1. 1. 1.1.1, 0.0.0.0.0.0. 1. 1]
        // 槽中bit标号: [7.6.5.4.3.2.1.0, 15.14.13.12.11.10.9.8, x.x.x.x.x.x.17.16]
        int idx = i / 8;  // 该槽位在header中的分量的下标
        int pos = i % 8;  // 该槽位在这一分量中为第几位
        // 判断bit所在的byte（idx位置）右起第pos位是否为1 (即是否占用)
        return ((this.header[idx] >> pos) & 0x01) != 0x00;
    }

    /**
     * Abstraction to fill or clear a slot on this page.
     * @param i The slot to mark as used or not
     * @param value true indicates used, false indicates unused
     */
    private void markSlotUsed(int i, boolean value) {
        // some code goes here
        // not necessary for lab1
    }

    /**
     * @return an iterator over all tuples on this page (calling remove on this iterator throws an UnsupportedOperationException)
     * (note that this iterator shouldn't return tuples in empty slots!)
     */
    // 遍历本页上所有元组的迭代器，不返回空槽中的元组
    public Iterator<Tuple> iterator() {
        // some code goes here
        return new Iterator<Tuple>() {
            private int usedTuplesCount = 0;    // 遍历过的计数器
            private int index = 0;  // 槽位
            // 所有使用了的槽位总数：槽数-空槽数
            private final int usedTuplesNumber = HeapPage.this.numSlots - HeapPage.this.getNumEmptySlots();
            @Override
            public boolean hasNext() {
                // 有后继：槽位小于总槽数 且 遍历过的计数器小于所有使用了的槽位总数
                return this.index < HeapPage.this.numSlots && this.usedTuplesCount < this.usedTuplesNumber;
            }

            @Override
            public Tuple next() {
                if (!this.hasNext()) {
                    throw new NoSuchElementException();
                }
                while (!isSlotUsed(this.index)) { // 找到非空槽元组
                    this.index++;
                }
                // 返回一个使用过的元组，并更新遍历过的计数器
                this.usedTuplesCount++;
                return tuples[this.index++];
            }
        };
    }

}

