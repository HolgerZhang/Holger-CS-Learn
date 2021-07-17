package punch.db;

import punch.activity.ActivityFactory;
import punch.activity.BasicActivity;
import punch.user.User;

import java.sql.*;
import java.util.*;

// 数据库单例类
public class Database {

    // 连接信息
    private static final String JDBC = "org.sqlite.JDBC";
    private static final String URL = "jdbc:sqlite:data/database/data.db";

    // SQL语句
    //language=SQLite
    private static final String createTableSql = "CREATE TABLE IF NOT EXISTS USERS (" +
            "UID        BIGINT      PRIMARY KEY NOT NULL, " +
            "USERNAME   VARCHAR(64) NOT NULL UNIQUE, " +
            "PASSMD5    VARCHAR(35) NOT NULL," +
            "ROLE       VARCHAR(10) DEFAULT 'NORMAL' CHECK ( ROLE IN ('NORMAL','ADMIN') )); " +
            "CREATE TABLE IF NOT EXISTS ACTIVITY ( " +
            "AID                BIGINT      PRIMARY KEY NOT NULL, " +
            "ACTIVITY_NAME      VARCHAR(64) NOT NULL, " +
            "ACTIVITY_TYPE      VARCHAR(10) NOT NULL" +
            "                               CHECK ( ACTIVITY_TYPE IN ('BASIC', 'REPEAT', 'ZEN', 'MONEY' ) ), " +
            "STATUS             VARCHAR(10) NOT NULL DEFAULT 'READY'" +
            "                               CHECK ( STATUS IN ('READY', 'EXEC', 'FINISH') ), " +
            "DESCRIPTION        TEXT        NOT NULL, " +
            "DETAIL_INFO        TEXT        DEFAULT ''); " +
            "CREATE TABLE IF NOT EXISTS ACTIVITY_OWN ( " +
            "UID        BIGINT      NOT NULL, " +
            "AID        BIGINT      NOT NULL, " +
            "A_MODE     VARCHAR(10) NOT NULL DEFAULT 'OWN'" +
            "                       CHECK ( A_MODE IN ('OWN','VISIBLE','EDITABLE') )," +
            "PRIMARY KEY (UID, AID)," +
            "FOREIGN KEY (AID) REFERENCES ACTIVITY(AID)," +
            "FOREIGN KEY (UID) REFERENCES USERS(UID)); " +
            "CREATE TABLE IF NOT EXISTS ACTIVITY_LOG ( " +
            "AID    BIGINT      NOT NULL, " +
            "UID    BIGINT      NOT NULL, " +
            "LOG_TIME   TIMESTAMP   DEFAULT (DATETIME('now','localtime')), " +
            "LOG_MSG    TEXT        NOT NULL, " +
            "PRIMARY KEY (AID, UID, LOG_TIME), " +
            "FOREIGN KEY (UID) REFERENCES USERS(UID)," +
            "FOREIGN KEY (AID) REFERENCES ACTIVITY(AID));";
    //language=SQLite
    private static final String selectUserSql = "SELECT * FROM USERS WHERE UID=?; ";
    //language=SQLite
    private static final String selectUserByNameSql = "SELECT * FROM USERS WHERE USERNAME=?; ";
    //language=SQLite
    private static final String insertUserSQl = "INSERT INTO USERS(UID, USERNAME, PASSMD5, ROLE) VALUES (?,?,?,?);";
    //language=SQLite
    private static final String selectActivitySql = "SELECT * FROM ACTIVITY WHERE AID=?;";
    //language=SQLite
    private static final String insertActivitySql = "INSERT INTO ACTIVITY(AID, ACTIVITY_NAME, ACTIVITY_TYPE, DESCRIPTION, DETAIL_INFO) VALUES (?,?,?,?,?);";
    //language=SQLite
    private static final String deleteActivitySql = "DELETE FROM ACTIVITY WHERE AID=?;";
    //language=SQLite
    private static final String updateActivityStatusSql = "UPDATE ACTIVITY SET STATUS=? WHERE AID=?; ";
    //language=SQLite
    private static final String updateActivityDescriptionSql = "UPDATE ACTIVITY SET DESCRIPTION=? WHERE AID=?; ";
    //language=SQLite
    private static final String updateActivityDetailSql = "UPDATE ACTIVITY SET DETAIL_INFO=? WHERE AID=?; ";
    //language=SQLite
    private static final String insertActivityModeSql = "INSERT INTO ACTIVITY_OWN(UID, AID, A_MODE) VALUES (?,?,?); ";
    //language=SQLite
    private static final String deleteActivityModeSql = "DELETE FROM ACTIVITY_OWN WHERE AID=?;";
    //language=SQLite
    private static final String selectActivityModeSql = "SELECT AID, A_MODE FROM ACTIVITY_OWN WHERE UID=?;";
    //language=SQLite
    private static final String insertLogSql = "INSERT INTO ACTIVITY_LOG(AID, UID, LOG_MSG) VALUES (?,?,?); ";
    //language=SQLite
    private static final String selectUserLogSql = "SELECT * FROM ACTIVITY_LOG WHERE UID=? ORDER BY LOG_TIME DESC LIMIT 30; ";
    //language=SQLite
    private static final String selectActivityLogSql = "SELECT * FROM ACTIVITY_LOG WHERE AID=? ORDER BY LOG_TIME DESC LIMIT 30; ";

    // 初始化块，初始化数据库
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
        } catch (SQLException e) {
            e.printStackTrace();
            System.exit(0);
        }
    }

    // cache
    private final Map<Long, User> userCache;
    private final Map<Long, BasicActivity> activityCache;

    private Database() {
        userCache = new HashMap<>();
        activityCache = new HashMap<>();
    }

    // 获取数据库实例方法
    public static Database getInstance() {
        return InstanceHolder.INSTANCE;
    }

    // 获取用户密码MD5值
    public String selectUserPasswordMd5(long id) throws SQLException {
        final String[] passwdMd5 = new String[1];
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectUserSql);
                stmt.setLong(1, id);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    passwdMd5[0] = rs.getString("PASSMD5");
                } else {
                    throw new SQLException("用户不存在");
                }
                rs.close();
                stmt.close();
            }
        });
        return passwdMd5[0];
    }

    // 更新活动通用方法
    private static void updateActivity(long aid, String info, String updateActivityDetailSql) throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(updateActivityDetailSql);
                stmt.setLong(2, aid);
                stmt.setString(1, info);
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    // 执行查询实用方法
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

    // 获取用户对象(编号)
    public User selectUser(long id) throws SQLException {
        if (userCache.containsKey(id)) {
            return userCache.get(id);
        }
        User newUserInstance = new User();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectUserSql);
                stmt.setLong(1, id);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    newUserInstance.setId(id);
                    newUserInstance.setName(rs.getString("USERNAME"));
                    newUserInstance.setRole(rs.getString("ROLE"));
                } else {
                    throw new SQLException("用户不存在");
                }
                rs.close();
                stmt.close();
            }
        });
        userCache.put(id, newUserInstance);
        return newUserInstance;
    }

    // 获取用户对象(姓名)
    public User selectUser(String username) throws SQLException {
        for (User user : userCache.values()) {
            if (user.getName().equals(username)) {
                return user;
            }
        }
        User newUserInstance = new User();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectUserByNameSql);
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    newUserInstance.setId(rs.getLong("UID"));
                    newUserInstance.setName(username);
                    newUserInstance.setRole(rs.getString("ROLE"));
                } else {
                    throw new SQLException("用户不存在");
                }
                rs.close();
                stmt.close();
            }
        });
        userCache.put(newUserInstance.getId(), newUserInstance);
        return newUserInstance;
    }

    // 新增用户数据
    public void insertUser(User user, String password) throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(insertUserSQl);
                stmt.setLong(1, user.getId());
                stmt.setString(2, user.getName());
                stmt.setString(3, User.md5Password(password));
                stmt.setString(4, user.getRole());
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
        userCache.put(user.getId(), user);
    }

    // 获取活动对象
    public BasicActivity selectActivity(long id) throws SQLException {
        if (activityCache.containsKey(id)) {
            return activityCache.get(id);
        }
        final BasicActivity[] activity = {null};
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectActivitySql);
                stmt.setLong(1, id);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    long id = rs.getLong("AID");
                    String name = rs.getString("ACTIVITY_NAME");
                    String type = rs.getString("ACTIVITY_TYPE");
                    String status = rs.getString("STATUS");
                    String desc = rs.getString("DESCRIPTION");
                    String detail = rs.getString("DETAIL_INFO");
                    activity[0] = ActivityFactory.createActivity(id, name, type, status, desc, detail);
                } else {
                    throw new SQLException("活动不存在");
                }
                rs.close();
                stmt.close();
            }
        });
        activityCache.put(id, activity[0]);
        return activity[0];
    }

    // 新增活动数据
    public void insertActivity(BasicActivity activity) throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(insertActivitySql);
                stmt.setLong(1, activity.getId());
                stmt.setString(2, activity.getName());
                stmt.setString(3, activity.getType());
                stmt.setString(4, activity.getDescription());
                stmt.setString(5, activity.getDetailInfo());
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
        activityCache.put(activity.getId(), activity);
    }

    // 删除活动数据
    public void deleteActivity(long aid) throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(deleteActivitySql);
                stmt.setLong(1, aid);
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
        activityCache.remove(aid);
    }

    // 更新活动状态
    public void updateActivityStatus(long aid, String status) throws SQLException {
        updateActivity(aid, status, updateActivityStatusSql);
    }

    // 更新活动内容
    public void updateActivityDescription(long aid, String desc) throws SQLException {
        updateActivity(aid, desc, updateActivityDescriptionSql);
    }

    // 更新活动细节信息
    public void updateActivityDetail(long aid, String info) throws SQLException {
        updateActivity(aid, info, updateActivityDetailSql);
    }

    // 获取用户持有的活动
    public Map<Long, String> selectUserActivityIdWithMode(long uid) throws SQLException {
        final Map<Long, String> activitiesAndMode = new HashMap<>();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectActivityModeSql);
                stmt.setLong(1, uid);
                ResultSet rs = stmt.executeQuery();
                while (rs.next()) {
                    long aid = rs.getLong("AID");
                    String mode = rs.getString("A_MODE");
                    activitiesAndMode.put(aid, mode);
                }
                rs.close();
                stmt.close();
            }
        });
        return activitiesAndMode;
    }

    // 新增用户活动持有关系
    public void insertActivityMode(long uid, long aid, String mode) throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(insertActivityModeSql);
                stmt.setLong(1, uid);
                stmt.setLong(2, aid);
                stmt.setString(3, mode);
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    // 删除用户活动持有关系
    public void deleteActivityModes(long aid) throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(deleteActivityModeSql);
                stmt.setLong(1, aid);
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    // 记录日志
    public void insertLog(long aid, long uid, String msg) throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(insertLogSql);
                stmt.setLong(1, aid);
                stmt.setLong(2, uid);
                stmt.setString(3, msg);
                int line = stmt.executeUpdate();
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    // 查询用户日志
    public List<String> selectUserLog(long uid) throws SQLException {
        List<String> logs = new LinkedList<>();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectUserLogSql);
                stmt.setLong(1, uid);
                ResultSet rs = stmt.executeQuery();
                while (rs.next()) {
                    long aid = rs.getLong("AID");
                    String msg = rs.getString("LOG_MSG");
                    String time = rs.getString("LOG_TIME");
                    logs.add(String.format("[%s] user@%x | activity@%x | %s", time, uid, aid, msg));
                }
                rs.close();
                stmt.close();
            }
        });
        return logs;
    }

    // 查询活动日志
    public List<String> selectActivityLog(long aid) throws SQLException {
        List<String> logs = new LinkedList<>();
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                PreparedStatement stmt = conn.prepareStatement(selectActivityLogSql);
                stmt.setLong(1, aid);
                ResultSet rs = stmt.executeQuery();
                while (rs.next()) {
                    long uid = rs.getLong("UID");
                    String msg = rs.getString("LOG_MSG");
                    String time = rs.getString("LOG_TIME");
                    logs.add(String.format("[%s] user@%x | activity@%x | %s", time, uid, aid, msg));
                }
                rs.close();
                stmt.close();
            }
        });
        return logs;
    }

    // 清空缓存
    public void clearCache() {
        userCache.clear();
        activityCache.clear();
    }

    public void reset() throws SQLException {
        doSqlQuery(new SQLQueryMaker() {
            @Override
            public void make(Connection conn) throws SQLException {
                Statement stmt = conn.createStatement();
                int line = 0;
                line += stmt.executeUpdate("DELETE FROM ACTIVITY_LOG;");
                line += stmt.executeUpdate("DELETE FROM ACTIVITY_OWN;");
                line += stmt.executeUpdate("DELETE FROM ACTIVITY;");
                line += stmt.executeUpdate("DELETE FROM USERS;");
                System.out.println(line + "行受影响");
                stmt.close();
            }
        });
    }

    // SQL查询连接处理接口
    private interface SQLQueryMaker {
        void make(Connection conn) throws SQLException;
    }

    // 单例模式实例装载静态内部类
    private static class InstanceHolder {
        private static final Database INSTANCE = new Database();
    }
}
