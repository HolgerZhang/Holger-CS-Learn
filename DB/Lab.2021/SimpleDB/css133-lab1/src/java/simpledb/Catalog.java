package simpledb;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * The Catalog keeps track of all available tables in the database and their
 * associated schemas.
 * For now, this is a stub catalog that must be populated with tables by a
 * user program before it can be used -- eventually, this should be converted
 * to a catalog that reads a catalog table from disk.
 *
 * @Threadsafe
 */
public class Catalog {
    // 为目录建立映射
    private final Map<Integer, DbFile> idFileMap;   // map from 表id到DB文件的映射
    private final Map<Integer, String> idNameMap;   // map from 表id到表名的映射
    private final Map<Integer, String> idPKeyMap;   // map from 表id到主键的映射
    private final Map<String, Integer> nameIdMap;   // map from 表名到表id的映射

    /**
     * Constructor.
     * Creates a new, empty catalog.
     */
    // 创建一个新的空目录
    public Catalog() {
        // some code goes here
        this.idFileMap = new HashMap<>();
        this.idNameMap = new HashMap<>();
        this.idPKeyMap = new HashMap<>();
        this.nameIdMap = new HashMap<>();
    }

    /**
     * Add a new table to the catalog.
     * This table's contents are stored in the specified DbFile.
     * @param file the contents of the table to add;  file.getId() is the identfier of
     *    this file/tupledesc param for the calls getTupleDesc and getFile
     * @param name the name of the table -- may be an empty string.  May not be null.  If a name
     * conflict exists, use the last table to be added as the table for a given name.
     * @param pkeyField the name of the primary key field
     */
    //向目录中添加一张新的表，表的详情存储在DbFile中，指定表的名称和主键
    public void addTable(DbFile file, String name, String pkeyField) {
        // some code goes here
        // 空指针检查
        if (file == null || name == null || pkeyField == null) {
            throw new IllegalArgumentException("invalid argument.");
        }
        if (this.nameIdMap.containsKey(name)) {  // 表名已经存在，删除
            int existedId = this.nameIdMap.get(name);
            this.idFileMap.remove(existedId);
            this.idNameMap.remove(existedId);
            this.idPKeyMap.remove(existedId);
            this.nameIdMap.remove(name);
        }
        int tableId = file.getId();  // 获取表id并插入
        this.idFileMap.put(tableId, file);
        this.idNameMap.put(tableId, name);
        this.idPKeyMap.put(tableId, pkeyField);
        this.nameIdMap.put(name, tableId);
    }

    public void addTable(DbFile file, String name) {
        addTable(file, name, "");
    }

    /**
     * Add a new table to the catalog.
     * This table has tuples formatted using the specified TupleDesc and its
     * contents are stored in the specified DbFile.
     * @param file the contents of the table to add;  file.getId() is the identfier of
     *    this file/tupledesc param for the calls getTupleDesc and getFile
     */
    public void addTable(DbFile file) {
        addTable(file, (UUID.randomUUID()).toString());
    }

    /**
     * Return the id of the table with a specified name,
     * @throws NoSuchElementException if the table doesn't exist
     */
    // 根据表名找表id，不存在报错
    public int getTableId(String name) throws NoSuchElementException {
        // some code goes here
        if (name == null || !this.nameIdMap.containsKey(name)) {
            throw new NoSuchElementException("表名'" + name + "'未找到");
        }
        return this.nameIdMap.get(name);
    }

    /**
     * Returns the tuple descriptor (schema) of the specified table
     * @param tableid The id of the table, as specified by the DbFile.getId()
     *     function passed to addTable
     * @throws NoSuchElementException if the table doesn't exist
     */
    // 根据表id找模式，不存在报错
    public TupleDesc getTupleDesc(int tableid) throws NoSuchElementException {
        // some code goes here
        if (!this.idFileMap.containsKey(tableid)) {
            throw new NoSuchElementException("表id=" + tableid + "未找到");
        }
        return this.idFileMap.get(tableid).getTupleDesc();
    }

    /**
     * Returns the DbFile that can be used to read the contents of the
     * specified table.
     * @param tableid The id of the table, as specified by the DbFile.getId()
     *     function passed to addTable
     */
    // 根据表id找DB文件，不存在报错
    public DbFile getDatabaseFile(int tableid) throws NoSuchElementException {
        // some code goes here
        if (!this.idFileMap.containsKey(tableid)) {
            throw new NoSuchElementException("表id=" + tableid + "未找到");
        }
        return this.idFileMap.get(tableid);
    }

    // 根据表id找主键，不存在报错
    public String getPrimaryKey(int tableid) {
        // some code goes here
        if (!this.idPKeyMap.containsKey(tableid)) {
            throw new NoSuchElementException("表id=" + tableid + "未找到");
        }
        return this.idPKeyMap.get(tableid);
    }

    // 表id迭代器，使用HashMap中ketSet的迭代器实现
    public Iterator<Integer> tableIdIterator() {
        // some code goes here
        return this.idNameMap.keySet().iterator();
    }

    // 根据表id找表名，不存在报错
    public String getTableName(int tableid) {
        // some code goes here
        if (!this.idNameMap.containsKey(tableid)) {
            throw new NoSuchElementException("表id=" + tableid + "未找到");
        }
        return this.idNameMap.get(tableid);
    }

    /** Delete all tables from the catalog */
    public void clear() {  // 清空目录，即清空四个映射
        // some code goes here
        this.idNameMap.clear();
        this.idFileMap.clear();
        this.idPKeyMap.clear();
        this.nameIdMap.clear();
    }

    /**
     * Reads the schema from a file and creates the appropriate tables in the database.
     * @param catalogFile
     */
    public void loadSchema(String catalogFile) {
        String line = "";
        String baseFolder=new File(new File(catalogFile).getAbsolutePath()).getParent();
        try {
            BufferedReader br = new BufferedReader(new FileReader(new File(catalogFile)));

            while ((line = br.readLine()) != null) {
                //assume line is of the format name (field type, field type, ...)
                String name = line.substring(0, line.indexOf("(")).trim();
                //System.out.println("TABLE NAME: " + name);
                String fields = line.substring(line.indexOf("(") + 1, line.indexOf(")")).trim();
                String[] els = fields.split(",");
                ArrayList<String> names = new ArrayList<String>();
                ArrayList<Type> types = new ArrayList<Type>();
                String primaryKey = "";
                for (String e : els) {
                    String[] els2 = e.trim().split(" ");
                    names.add(els2[0].trim());
                    if (els2[1].trim().toLowerCase().equals("int"))
                        types.add(Type.INT_TYPE);
                    else if (els2[1].trim().toLowerCase().equals("string"))
                        types.add(Type.STRING_TYPE);
                    else {
                        System.out.println("Unknown type " + els2[1]);
                        System.exit(0);
                    }
                    if (els2.length == 3) {
                        if (els2[2].trim().equals("pk"))
                            primaryKey = els2[0].trim();
                        else {
                            System.out.println("Unknown annotation " + els2[2]);
                            System.exit(0);
                        }
                    }
                }
                Type[] typeAr = types.toArray(new Type[0]);
                String[] namesAr = names.toArray(new String[0]);
                TupleDesc t = new TupleDesc(typeAr, namesAr);
                HeapFile tabHf = new HeapFile(new File(baseFolder+"/"+name + ".dat"), t);
                addTable(tabHf,name,primaryKey);
                System.out.println("Added table : " + name + " with schema " + t);
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(0);
        } catch (IndexOutOfBoundsException e) {
            System.out.println ("Invalid catalog entry : " + line);
            System.exit(0);
        }
    }
}

