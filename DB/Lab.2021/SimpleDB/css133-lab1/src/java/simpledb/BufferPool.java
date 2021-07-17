package simpledb;

import java.io.*;

import java.util.HashMap;
import java.util.Map;

/**
 * BufferPool manages the reading and writing of pages into memory from
 * disk. Access methods call into it to retrieve pages, and it fetches
 * pages from the appropriate location.
 * <p>
 * The BufferPool is also responsible for locking;  when a transaction fetches
 * a page, BufferPool checks that the transaction has the appropriate
 * locks to read/write the page.
 * 
 * @Threadsafe, all fields are final
 */
public class BufferPool {
    /** Bytes per page, including header. */
    public static final int PAGE_SIZE = 4096;

    private static int pageSize = PAGE_SIZE;

    /** Default number of pages passed to the constructor. This is used by
    other classes. BufferPool should use the numPages argument to the
    constructor instead. */
    public static final int DEFAULT_PAGES = 50;

    /** TODO for Lab 4: create instance of Lock Manager class. 
	Be sure to instantiate it in the constructor. */

    // 页面缓冲池，至多numPages个页面（numPages由构造函数提供）
    private final Map<PageId, Page> pageCache;
    // 缓冲池中最大页面数量
    private final int PAGES_MAX_NUM;

    /**
     * Creates a BufferPool that caches up to numPages pages.
     *
     * @param numPages maximum number of pages in this buffer pool.
     */
    public BufferPool(int numPages) {
        // some code goes here
        this.PAGES_MAX_NUM = numPages;
        this.pageCache = new HashMap<>(numPages);
    }
    
    public static int getPageSize() {
      return pageSize;
    }

    /**
     * Helper: this should be used for testing only!!!
     */
    public static void setPageSize(int pageSize) {
	BufferPool.pageSize = pageSize;
    }
    /**
     * Helper: this should be used for testing only!!!
     */
    public static void resetPageSize(int pageSize) {
	BufferPool.pageSize = PAGE_SIZE;
    }

    /**
     * Retrieve the specified page with the associated permissions.
     * Will acquire a lock and may block if that lock is held by another
     * transaction.
     * <p>
     * The retrieved page should be looked up in the buffer pool.  If it
     * is present, it should be returned.  If it is not present, it should
     * be added to the buffer pool and returned.  If there is insufficient
     * space in the buffer pool, a page should be evicted and the new page
     * should be added in its place.
     *
     * @param tid the ID of the transaction requesting the page
     * @param pid the ID of the requested page
     * @param perm the requested permissions on the page
     */
    // 检索指定页，提供事务id，页面id和读写权限perm
    // 在Lab1中只关心请求的页面id：pid，其他两个参数暂时用不到
    public  Page getPage(TransactionId tid, PageId pid, Permissions perm)
        throws TransactionAbortedException, DbException {
        // some code goes here
        // 首先检索缓冲池中是否已经存在该页面，若存在（命中）直接返回
        if (this.pageCache.containsKey(pid)) {
            return this.pageCache.get(pid);
        }
        // 若没有命中，需要根据请求的pid寻找该页面
        // 首先根据pid到目录中获取DB文件（表）
        DbFile table = Database.getCatalog().getDatabaseFile(pid.getTableId());
        // 之后从DB文件（表）中读取相应的页面
        Page newPage = table.readPage(pid);
        this.addNewPage(pid, newPage);  // 最后将页面添加到缓冲池
        return newPage;
    }

    /**
     * Add new page to the buffer pool.
     * If there is insufficient space in the buffer pool,
     * a page should be evicted and the new page should be added in its place.
     *
     * @param pid the ID of the page to be added
     * @param newPage the page of the page to be added
     */
    // 添加页面到缓冲池，如果缓冲池已满需要使用替换算法替换
    // Lab1中不要求实现替换策略，只需缓冲池已满时抛出DbException
    private void addNewPage(PageId pid, Page newPage) throws DbException {
        if (this.pageCache.size() < this.PAGES_MAX_NUM) { // 缓冲池空间充足
            this.pageCache.put(pid, newPage);
        } else {  // TODO: 2021-05-21  实现替换策略 (当前为抛出异常)
            throw new DbException("缓冲池空间不足");
        }
    }

    /**
     * Releases the lock on a page.
     * Calling this is very risky, and may result in wrong behavior. Think hard
     * about who needs to call this and why, and why they can run the risk of
     * calling it.
     *
     * @param tid the ID of the transaction requesting the unlock
     * @param pid the ID of the page to unlock
     */
    public  void releasePage(TransactionId tid, PageId pid) {
        // some code goes here
        // not necessary for lab1|lab2

	//lockmgr.releaseLock(tid,pid); // Uncomment for Lab 4
    }

    /**
     * Release all locks associated with a given transaction.
     *
     * @param tid the ID of the transaction requesting the unlock
     */
    public void transactionComplete(TransactionId tid) throws IOException {
        transactionComplete(tid,true);
    }

    /** Return true if the specified transaction has a lock on the specified page */
    public boolean holdsLock(TransactionId tid, PageId p) {
        // some code goes here
        // not necessary for lab1|lab2

	//return lockmgr.holdsLock(tid, p); // Uncomment for Lab 4 (remove "return false");
        return false;
    }

    /**
     * Commit or abort a given transaction; release all locks associated to
     * the transaction.
     *
     * @param tid the ID of the transaction requesting the unlock
     * @param commit a flag indicating whether we should commit or abort
     */
    public void transactionComplete(TransactionId tid, boolean commit)
        throws IOException {
        // some code goes here
        // not necessary for lab1|lab2

	// After dealing with commit/abort actions, ask lock manager to release locks
	//lockmgr.releaseAllLocks(tid); // Uncomment for Lab 4

    }

    /**
     * Add a tuple to the specified table on behalf of transaction tid.  Will
     * acquire a write lock on the page the tuple is added to and any other 
     * pages that are updated (Lock acquisition is not needed for lab2). 
     * May block if the lock(s) cannot be acquired.
     * 
     * Marks any pages that were dirtied by the operation as dirty by calling
     * their markDirty bit, and adds versions of any pages that have 
     * been dirtied to the cache (replacing any existing versions of those pages) so
     * that future requests see up-to-date pages. 
     *
     * @param tid the transaction adding the tuple
     * @param tableId the table to add the tuple to
     * @param t the tuple to add
     */
    public void insertTuple(TransactionId tid, int tableId, Tuple t)
        throws DbException, IOException, TransactionAbortedException {
        // some code goes here
        // not necessary for lab1
    }

    /**
     * Remove the specified tuple from the buffer pool.
     * Will acquire a write lock on the page the tuple is removed from and any
     * other pages that are updated. May block if the lock(s) cannot be acquired.
     *
     * Marks any pages that were dirtied by the operation as dirty by calling
     * their markDirty bit, and adds versions of any pages that have 
     * been dirtied to the cache (replacing any existing versions of those pages) so
     * that future requests see up-to-date pages. 
     *
     * @param tid the transaction deleting the tuple.
     * @param t the tuple to delete
     */
    public void deleteTuple(TransactionId tid, Tuple t)
        throws DbException, IOException, TransactionAbortedException {
        // some code goes here
        // not necessary for lab1
    }

    /**
     * Flush all dirty pages to disk.
     * Be careful using this routine -- it writes dirty data to disk so will
     *     break simpledb if running in NO STEAL mode.
     */
    public synchronized void flushAllPages() throws IOException {
        // some code goes here
        // not necessary for lab1

    }

    /** Remove the specific page id from the buffer pool.
        Needed by the recovery manager to ensure that the
        buffer pool doesn't keep a rolled back page in its
        cache.
    */
    public synchronized void discardPage(PageId pid) {
        // some code goes here
        // not necessary for labs 1--4
    }

    /**
     * Flushes (i.e., writes) a certain page to disk by asking 
     * the correct HeapFile to write the page
     * @param pid an ID indicating the page to flush
     */
    private synchronized void flushPage(PageId pid) throws IOException {
        // some code goes here
        // not necessary for lab1
    }

    /** Write all pages of the specified transaction to disk.
     */
    public synchronized void flushPages(TransactionId tid) throws IOException {
        // some code goes here
        // not necessary for labs 1--4
    }

    /**
     * Discards a page from the buffer pool.
     * Flushes the page to disk to ensure dirty pages are updated on disk.
     */
    private synchronized void evictPage() throws DbException {
        // some code goes here
        // not necessary for lab1
    }

}
