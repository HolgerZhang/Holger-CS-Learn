package punch.user;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.UUID;

// 用户实体类
public class User {
    public static final String NORMAL_ROLE = "NORMAL";
    public static final String ADMIN_ROLE = "ADMIN";
    public static final String[] ROLES = {NORMAL_ROLE, ADMIN_ROLE};

    private long id;
    private String name;
    private String role;

    public User(String name, String role) {
        id = UUID.randomUUID().getLeastSignificantBits() & Long.MAX_VALUE;
        this.name = name;
        this.role = role;
    }

    public User() {
        this("new User", NORMAL_ROLE);
    }

    public static String md5Password(String password) {
        StringBuilder md5code = null;
        try {
            md5code = new StringBuilder(new BigInteger(1, MessageDigest.getInstance("md5").digest(password.getBytes())).toString(16));
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            System.exit(0);
        }
        for (int i = 0; i < 32 - md5code.length(); i++) {
            md5code.insert(0, "0");
        }
        return md5code.toString();
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj instanceof User) {
            return id == ((User) obj).id;
        }
        return false;
    }
}
