package manager.db;

import manager.devices.SmartDeviceFactory;
import manager.devices.base.SmartDevice;

import java.sql.*;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class Database {
    private static final String JDBC = "org.sqlite.JDBC";
    private static final String URL = "jdbc:sqlite:data/data.db";
    //language=SQLite
    private static final String createTableSql = "CREATE TABLE IF NOT EXISTS USERS (" +
            "USERNAME VARCHAR(64) PRIMARY KEY NOT NULL, " +
            "PASSMD5 VARCHAR(35) NOT NULL); " +
            "CREATE TABLE IF NOT EXISTS DEVICES ( " +
            "DEV_ID    BIGINT      PRIMARY KEY NOT NULL, " +
            "DEV_NAME  VARCHAR(64) NOT NULL, " +
            "DEV_TYPE  VARCHAR(32) NOT NULL, " +
            "POSITION  VARCHAR(32) DEFAULT '穿戴设备', " +
            "USERNAME  VARCHAR(64) NOT NULL, " +
            "FOREIGN KEY (USERNAME) REFERENCES USERS(USERNAME)); " +
            "CREATE TABLE IF NOT EXISTS DEV_LOG ( " +
            "DEV_ID    BIGINT    NOT NULL, " +
            "LOG_TIME  TIMESTAMP DEFAULT (DATETIME('now','localtime')), " +
            "USERNAME  VARCHAR(64) NOT NULL, " +
            "LOG_MSG   TEXT, " +
            "PRIMARY KEY (DEV_ID, LOG_TIME), " +
            "FOREIGN KEY (DEV_ID) REFERENCES DEVICES(DEV_ID), " +
            "FOREIGN KEY (USERNAME) REFERENCES USERS(USERNAME));";
    //language=SQLite
    private static final String selectUserSql = "SELECT * FROM USERS WHERE USERNAME=?;";
    //language=SQLite
    private static final String insertUserSql = "INSERT INTO USERS VALUES (?,?);";
    //language=SQLite
    private static final String selectDevicesByUserSql = "SELECT * FROM DEVICES WHERE USERNAME=?;";
    //language=SQLite
    private static final String insertDeviceSql = "INSERT INTO DEVICES VALUES (?,?,?,?,?);";
    //language=SQLite
    private static final String insertDeviceDefaultSql = "INSERT INTO DEVICES(DEV_ID, DEV_NAME, DEV_TYPE, USERNAME) VALUES (?,?,?,?);";
    //language=SQLite
    private static final String deleteDeviceByIdSql = "DELETE FROM DEVICES WHERE DEV_ID=?;";
    //language=SQLite
    private static final String selectDeviceLogByIdSql = "SELECT * FROM DEV_LOG WHERE DEV_ID=? ORDER BY LOG_TIME DESC LIMIT 30;";
    //language=SQLite
    private static final String selectDeviceLogByUserSql = "SELECT * FROM DEV_LOG WHERE USERNAME=? ORDER BY LOG_TIME DESC LIMIT 30;";
    //language=SQLite
    private static final String insertDeviceLogSql = "INSERT INTO DEV_LOG(DEV_ID, USERNAME, LOG_MSG) VALUES (?,?,?);";
    //language=SQLite
    private static final String totalDevicesSql = "SELECT max(DEV_ID) AS MAX_DEVS FROM DEVICES;";
    //language=SQLite
    private static final String selectPositionsByUserSql = "SELECT DISTINCT POSITION FROM DEVICES WHERE USERNAME=? AND POSITION IS NOT NULL;";
    //language=SQLite
    private static final String selectDevicesByUserPositionSql = "SELECT DEV_ID FROM DEVICES WHERE USERNAME=? AND POSITION=?;";
    //language=SQLite
    private static final String deleteAllLogSql = "-- noinspection SqlWithoutWhereForFile \n" +
            "DELETE FROM DEV_LOG;";
    //language=SQLite
    private static final String deleteAllDevicesSql = "-- noinspection SqlWithoutWhereForFile \n" +
            "DELETE FROM DEVICES;";
    //language=SQLite
    private static final String deleteAllUserSql = "-- noinspection SqlWithoutWhereForFile \n" +
            "DELETE FROM USERS;";

    static {
        try {
            doSqlQuery(new SQLQueryMaker() {
                @Override
                public void make(Connection conn) throws SQLException {
                    Statement stmt = conn.createStatement();
                    stmt.executeUpdate(createTableSql);
                    stmt.close();
                }
            });
            doSqlQuery(new SQLQueryMaker() {
                @Override
                public void make(Connection conn) throws SQLException {
                    Statement stmt = conn.createStatement();
                    ResultSet rs = stmt.executeQuery(totalDevicesSql);
                    if (rs.next()) {
                        long n = rs.getLong("MAX_DEVS");
                        SmartDevice.setTotalDevicesNumber(n + 1);
                    }
                    rs.close();
                    stmt.close();
                }
            });
        } catch (SQLException e) {
            e.printStackTrace();
            System.exit(0);
        }
    }

    private static void doSqlQuery(SQLQueryMaker maker) throws SQLException {
        Connection c;
        try {
            Class.forName(JDBC);
            c = DriverManager.getConnection(URL);
            System.out.println("数据库连接成功");
            maker.make(c);
            System.out.println("查询成功完成");
            c.close();
        } catch (ClassNotFoundException e) {
            System.err.println("数据库出现错误");
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
    }

    public static String selectUserPasswordMd5(String username) throws SQLException {
        final String[] passwdMd5 = new String[1];
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectUserSql);
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    passwdMd5[0] = rs.getString("PASSMD5");
                }
                rs.close();
                stmt.close();
            }
        });
        return passwdMd5[0];
    }

    public static void insertUser(String username, String passwordMd5)
            throws SQLException, IllegalArgumentException {
        if (isValidUser(username)) {
            throw new IllegalArgumentException("用户" + username + "已存在");
        }
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(insertUserSql);
                stmt.setString(1, username);
                stmt.setString(2, passwordMd5);
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    public static boolean isValidUser(String username) throws SQLException {
        final boolean[] result = new boolean[1];
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectUserSql);
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                result[0] = rs.next();
                rs.close();
                stmt.close();
            }
        });
        return result[0];
    }

    public static List<SmartDevice> selectDevices(String username) throws SQLException {
        final List<SmartDevice> devices = new LinkedList<>();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectDevicesByUserSql);
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                while (rs.next()) {
                    long id = rs.getLong("DEV_ID");
                    String name = rs.getString("DEV_NAME");
                    String type = rs.getString("DEV_TYPE");
                    String position = rs.getString("POSITION");
                    devices.add(SmartDeviceFactory.createDevice(id, name, type, position));
                }
                rs.close();
                stmt.close();
            }
        });
        return devices;
    }

    public static void insertDevice(long id, String dev_name, String type, String position, String username)
            throws SQLException {
        System.out.println(id);
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt;
                if (position != null) {
                    stmt = conn.prepareStatement(insertDeviceSql);
                    stmt.setLong(1, id);
                    stmt.setString(2, dev_name);
                    stmt.setString(3, type);
                    stmt.setString(4, position);
                    stmt.setString(5, username);
                } else {
                    stmt = conn.prepareStatement(insertDeviceDefaultSql);
                    stmt.setLong(1, id);
                    stmt.setString(2, dev_name);
                    stmt.setString(3, type);
                    stmt.setString(4, username);
                }
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    public static void deleteDevice(long id) throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(deleteDeviceByIdSql);
                stmt.setLong(1, id);
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    public static String selectDeviceLog(long id) throws SQLException {
        StringBuilder str = new StringBuilder();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectDeviceLogByIdSql);
                stmt.setLong(1, id);
                ResultSet rs = stmt.executeQuery();
                while (rs.next()) {
                    String time = rs.getString("LOG_TIME");
                    String user = rs.getString("USERNAME");
                    String msg = rs.getString("LOG_MSG");
                    str.append(String.format("[%s] Dev no.%d | user = %s | %s\n", time, id, user, msg));
                }
                rs.close();
                stmt.close();
            }
        });
        return str.toString();
    }

    public static String selectDeviceLog(String username) throws SQLException {
        StringBuilder str = new StringBuilder();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectDeviceLogByUserSql);
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                while (rs.next()) {
                    String time = rs.getString("LOG_TIME");
                    long id = rs.getLong("DEV_ID");
                    String msg = rs.getString("LOG_MSG");
                    str.append(String.format("[%s] Dev no.%d | user = %s | %s\n", time, id, username, msg));
                }
                rs.close();
                stmt.close();
            }
        });
        return str.toString();
    }

    public static void insertDeviceLog(long id, String username, String msg) throws SQLException {
        System.out.printf("Dev no.%d | user = %s | %s\n", id, username, msg);
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(insertDeviceLogSql);
                stmt.setLong(1, id);
                stmt.setString(2, username);
                stmt.setString(3, msg);
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    public static List<String> selectPositions(String username) throws SQLException {
        List<String> result = new LinkedList<>();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectPositionsByUserSql);
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                while (rs.next()) {
                    String pos = rs.getString("POSITION");
                    result.add(pos);
                }
                rs.close();
                stmt.close();
            }
        });
        return result;
    }

    public static Set<Long> selectSceneDevices(String username, String position) throws SQLException {
        Set<Long> result = new TreeSet<>();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectDevicesByUserPositionSql);
                stmt.setString(1, username);
                stmt.setString(2, position);
                ResultSet rs = stmt.executeQuery();
                while (rs.next()) {
                    long id = rs.getLong("DEV_ID");
                    result.add(id);
                }
                rs.close();
                stmt.close();
            }
        });
        return result;
    }

    public static void resetDB() throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                Statement stmt = conn.createStatement();
                int line = 0;
                line += stmt.executeUpdate(deleteAllLogSql);
                line += stmt.executeUpdate(deleteAllDevicesSql);
                line += stmt.executeUpdate(deleteAllUserSql);
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    interface SQLQueryMaker {
        void make(Connection conn) throws SQLException;
    }
}
