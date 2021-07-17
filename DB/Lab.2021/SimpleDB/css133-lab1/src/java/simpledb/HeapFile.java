package simpledb;

import java.io.*;
import java.util.*;

/**
 * HeapFile is an implementation of a DbFile that stores a collection of tuples
 * in no particular order. Tuples are stored on pages, each of which is a fixed
 * size, and the file is simply a collection of those pages. HeapFile works
 * closely with HeapPage. The format of HeapPages is described in the HeapPage
 * constructor.
 * 
 * @see simpledb.HeapPage#HeapPage
 * @author Sam Madden
 */
public class HeapFile implements DbFile {

    private final File file;
    private final TupleDesc tupleDesc;
    private final int numPage;

    /**
     * Constructs a heap file backed by the specified file.
     * 
     * @param f
     *            the file that stores the on-disk backing store for this heap
     *            file.
     */
    // 构造由指定文件支持的堆文件
    public HeapFile(File f, TupleDesc td) {
        // some code goes here
        this.file = f;
        this.tupleDesc = td;
        this.numPage = (int) (file.length() / BufferPool.PAGE_SIZE);
    }

    /**
     * Returns the File backing this HeapFile on disk.
     * 
     * @return the File backing this HeapFile on disk.
     */
    public File getFile() {  // File Getter
        // some code goes here
        return this.file;
    }

    /**
     * Returns an ID uniquely identifying this HeapFile. Implementation note:
     * you will need to generate this tableid somewhere to ensure that each
     * HeapFile has a "unique id," and that you always return the same value for
     * a particular HeapFile. We suggest hashing the absolute file name of the
     * file underlying the heapfile, i.e. f.getAbsoluteFile().hashCode().
     * 
     * @return an ID uniquely identifying this HeapFile.
     */
    // 返回唯一标识此堆文件的ID
    public int getId() {
        // some code goes here
        // 文档注释建议
        return this.file.getAbsoluteFile().hashCode();
    }

    /**
     * Returns the TupleDesc of the table stored in this DbFile.
     * 
     * @return TupleDesc of this DbFile.
     */
    public TupleDesc getTupleDesc() {  // tupleDesc Getter
        // some code goes here
        return this.tupleDesc;
    }

    // 从磁盘读取指定的页
    public Page readPage(PageId pid) throws IllegalArgumentException {
        // some code goes here
        Page page;
        byte[] data = new byte[BufferPool.PAGE_SIZE];  // 存放数据
        // 使用 RandomAccessFile ，try-with-resource 方式读取
        try (RandomAccessFile file = new RandomAccessFile(this.file, "r")) {
            // 计算文件所在页面文件的位置
            int pos = pid.getPageNumber() * BufferPool.PAGE_SIZE;
            file.seek(pos); // 移动文件指针，读取数据
            file.read(data, 0, data.length);
            page = new HeapPage((HeapPageId) pid, data); // 创建页面
        } catch (IOException e) {
            throw new IllegalArgumentException(e);
        }
        return page;
    }

    // see DbFile.java for javadocs
    public void writePage(Page page) throws IOException {
        // some code goes here
        // not necessary for lab1
    }

    /**
     * Returns the number of pages in this HeapFile.
     */
    public int numPages() {  // numPage Getter
        // some code goes here
        return this.numPage;
    }

    // see DbFile.java for javadocs
    public ArrayList<Page> insertTuple(TransactionId tid, Tuple t)
            throws DbException, IOException, TransactionAbortedException {
        // some code goes here
        return null;
        // not necessary for lab1
    }

    // see DbFile.java for javadocs
    public ArrayList<Page> deleteTuple(TransactionId tid, Tuple t) throws DbException,
            TransactionAbortedException {
        // some code goes here
        return null;
        // not necessary for lab1
    }

    // 返回存储在这个DbFile中的所有元组的迭代器。
    // 迭代器必须使用BufferPool.getPage而不是readPage来遍历页面。
    public DbFileIterator iterator(TransactionId tid) {
        // some code goes here
        return new DbFileIterator() {
            private int pagePos = 0;
            private Iterator<Tuple> tuplesInPage = null;
            // 为 tuplesInPage 提供页面的迭代器
            public Iterator<Tuple> getTuplesInPage(HeapPageId pid) throws TransactionAbortedException, DbException {
                // HeapPage page = (HeapPage) readPage(pid);  // 错误
                // 不能直接使用HeapFile的readPage方法，而是通过BufferPool来获得page
                // readPage方法只应该在BufferPool类被直接调用，在其他需要page的地方需要通过BufferPool访问
                // 这样才能实现缓存功能
                HeapPage page = (HeapPage) Database.getBufferPool().getPage(tid, pid, Permissions.READ_ONLY);
                return page.iterator();
            }

            @Override
            public void open() throws DbException, TransactionAbortedException {
                this.pagePos = 0;
                int tableId = getId();
                HeapPageId pid = new HeapPageId(tableId, this.pagePos);
                this.tuplesInPage = this.getTuplesInPage(pid);
            }

            @Override
            public boolean hasNext() throws DbException, TransactionAbortedException {
                if (this.tuplesInPage == null) {    // 迭代器已关闭或还未打开
                    throw new IllegalStateException();
                }
                if (this.tuplesInPage.hasNext()) {   // 页面中还有元组某一遍历
                    return true;
                }
                // 检查是否还有其他的页面
                if (this.pagePos < numPages() - 1) {
                    this.pagePos++;
                    HeapPageId pid = new HeapPageId(getId(), this.pagePos);
                    // 转到新的页面
                    this.tuplesInPage = this.getTuplesInPage(pid);
                    return this.tuplesInPage.hasNext();  // 确保该页面也有元组
                }
                return false;
            }

            @Override
            public Tuple next() throws DbException, TransactionAbortedException, NoSuchElementException {
                if (!this.hasNext()) {
                    throw new NoSuchElementException();
                }
                return this.tuplesInPage.next();
            }

            @Override
            public void rewind() throws DbException, TransactionAbortedException {
                this.open();
            }

            @Override
            public void close() {
                this.pagePos = 0;
                this.tuplesInPage = null;
            }
        };
    }

}

