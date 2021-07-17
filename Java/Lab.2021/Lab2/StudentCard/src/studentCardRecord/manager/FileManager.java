package studentCardRecord.manager;

import java.io.*;
import java.util.function.Consumer;

public class FileManager {
    public enum IOMode {READ, WRITE}

    public static final IOMode defaultIOMode = IOMode.READ;

    private String filePath;
    private IOMode mode;

    public FileManager(String filePath, IOMode mode) {
        this.open(filePath, mode);
    }

    public FileManager(String filePath) {
        this.open(filePath);
    }

    public FileManager() {
        this(null, defaultIOMode);
    }

    public void open(String filePath, IOMode mode) {
        this.filePath = filePath;
        this.mode = mode;
    }

    public void open(String filePath) {
        this.open(filePath, defaultIOMode);
    }

    public void setMode(IOMode mode) {
        this.mode = mode;
    }

    /**
     * 文件读取方法，从指定文件中一行一行读取
     * 使用接口 WriteLineHandler 中的 handle 方法处理各行
     * 仅支持打开类型为 IOMode.READ 的对象调用
     *
     * @param action 处理各行的动作
     */
    public void readLines(Consumer<String> action) throws IOException {
        if (this.filePath == null || this.mode != IOMode.READ) {
            throw new IOException("读文件被拒绝，FILE: " + this.filePath + "; MODE: " + this.mode);
        }
        try (FileInputStream in = new FileInputStream(this.filePath);
             BufferedReader reader = new BufferedReader(new InputStreamReader(in))) {  // try-with-resources 结构管理文件对象
            reader.lines().forEachOrdered(action);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 保存对象至目标文件（调用 toString 方法）
     * 仅支持打开类型为 IOMode.WRITE 的对象调用
     *
     * @param strings (不定长参数) 要保存的（多个）对象
     */
    public void writeLines(String... strings) throws IOException {
        if (this.filePath == null || mode != IOMode.WRITE) {
            throw new IOException("写文件被拒绝，FILE: " + this.filePath + "; MODE: " + this.mode);
        }
        try (FileWriter file = new FileWriter(this.filePath);
             BufferedWriter writer = new BufferedWriter(file)) {  // try-with-resources 结构管理文件对象
            for (String str : strings) { // 将 strings 逐行写入文本文件
                writer.write(str);
                writer.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
