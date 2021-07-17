package manager.account;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class User {

    private final String name;
    private final DevicesTable devices;

    public User(String name) {
        this.name = name;
        this.devices = new DevicesTable();
    }

    public static String md5Password(String password) {
        StringBuilder md5code = null;
        try {
            md5code = new StringBuilder(new BigInteger(1, MessageDigest.getInstance("md5").digest(password.getBytes())).toString(16));
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        assert md5code != null;
        for (int i = 0; i < 32 - md5code.length(); i++) {
            md5code.insert(0, "0");
        }
        return md5code.toString();
    }

    public DevicesTable getDevices() {
        return devices;
    }

    public String getName() {
        return name;
    }

}
