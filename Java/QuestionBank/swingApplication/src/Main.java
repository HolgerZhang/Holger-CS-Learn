import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import java.util.ArrayList;

/*
import sqlite3

import pandas as pd

conn = sqlite3.connect('data.db')
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS QUESTION(
       ID           INT     PRIMARY KEY,
       DETAIL       TEXT    NOT NULL,
       A            TEXT    NOT NULL,
       B            TEXT    NOT NULL,
       C            TEXT    NOT NULL,
       D            TEXT    NOT NULL,
       ANSWER       CHAR(4) NOT NULL CHECK (ANSWER IN ('A','B','C','D')));''')
conn.commit()

# readbook = data=pd.read_excel.open_workbook(r'd:\raw.xls')
data = pd.read_excel(r'd:\raw.xls', dtype={
    "subject": str,
    "select1": str,
    "select2": str,
    "select3": str,
    "select4": str,
    "answer": str
})
for i in range(data.shape[0]):
    id = i + 1
    detail = str(data.iloc[i, 0])
    a = str(data.iloc[i, 1])
    b = str(data.iloc[i, 2])
    c = str(data.iloc[i, 3])
    d = str(data.iloc[i, 4])
    ans = str(data.iloc[i, 5])
    cur = conn.cursor()
    cur.execute("INSERT INTO QUESTION VALUES (?,?,?,?,?,?,?)", (id, detail, a, b, c, d, ans))
    conn.commit()
    print("insert", (id, detail, a, b, c, d, ans))

conn.close()

*/

class Question {
    int id;
    String detail, a, b, c, d, ans;

    public Question(int id, String detail, String a, String b, String c, String d, String ans) {
        this.id = id;
        this.detail = detail;
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;
        this.ans = ans;
    }

    public boolean check(String choice) {
        return choice.equals(ans);
    }
}

public class Main extends JFrame {
    private static final String JDBC = "org.sqlite.JDBC";
    private static final String URL = "jdbc:sqlite:data/data.db";

    ArrayList<Question> questions = new ArrayList<>();
    int index = -1;

    public static void main(String[] args) {
        Main m = new Main();
        m.load();
        m.start();
    }

    void load() {
        Connection c;
        try {
            Class.forName(JDBC);
            c = DriverManager.getConnection(URL);
            System.out.println("数据库连接成功");
            Statement s = c.createStatement();
            ResultSet rs = s.executeQuery("select * from QUESTION;");
            while (rs.next()) {
                questions.add(new Question(rs.getInt("ID"),
                        rs.getString("DETAIL"),
                        rs.getString("A"),
                        rs.getString("B"),
                        rs.getString("C"),
                        rs.getString("D"),
                        rs.getString("ANSWER")));
            }
            System.out.println("查询成功完成");
            c.close();
        } catch (ClassNotFoundException | SQLException e) {
            System.err.println("数据库出现错误");
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
    }

    void start() {
        try {   // 保持与操作系统原生UI一致的感官
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }
        setLocationRelativeTo(null);
        setSize(700, 600);
        setTitle("Java选择题练习");
        JTextArea area = new JTextArea("Welcome");
        area.setEditable(false);
        area.setLineWrap(true);
        area.setFont(new Font("", Font.BOLD, 18));
        JScrollPane jsp = new JScrollPane(area);
        jsp.getVerticalScrollBar().setUnitIncrement(30);
        jsp.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        add(jsp, BorderLayout.CENTER);
        JPanel p = new JPanel();
        p.setLayout(new GridLayout(1, 0, 10, 10));
        add(p, BorderLayout.SOUTH);
        JButton prevBtn = new JButton("上一题");
        prevBtn.setFont(new Font("", Font.BOLD, 18));
        JButton A = new JButton("A");
        A.setFont(new Font("", Font.BOLD, 18));
        JButton B = new JButton("B");
        B.setFont(new Font("", Font.BOLD, 18));
        JButton C = new JButton("C");
        C.setFont(new Font("", Font.BOLD, 18));
        JButton D = new JButton("D");
        D.setFont(new Font("", Font.BOLD, 18));
        JButton nextBtn = new JButton("下一题");
        nextBtn.setFont(new Font("", Font.BOLD, 18));
        p.add(prevBtn);
        p.add(A);
        p.add(B);
        p.add(C);
        p.add(D);
        p.add(nextBtn);

        ActionListener l = (ActionEvent event) -> {
            if (questions.get(index).check(((JButton) event.getSource()).getText())) {
                JOptionPane.showMessageDialog(this, "回答正确");
            } else {
                JOptionPane.showMessageDialog(this, "回答错误，正确答案为：" + questions.get(index).ans);
            }
        };
        A.addActionListener(l);
        B.addActionListener(l);
        C.addActionListener(l);
        D.addActionListener(l);

        nextBtn.addActionListener(event -> {
            if (index >= questions.size() - 1) {
                index = questions.size() - 1;
            } else {
                index++;
            }
            area.setText(questions.get(index).id + ": " + questions.get(index).detail + "\n\nA. " + questions.get(index).a + "\nB. " + questions.get(index).b + "\nC. " + questions.get(index).c + "\nD. " + questions.get(index).d);
        });

        prevBtn.addActionListener(event -> {
            if (index <= 0) {
                index = 0;
            } else {
                index--;
            }
            area.setText(questions.get(index).id + ": " + questions.get(index).detail + "\n\nA. " + questions.get(index).a + "\nB. " + questions.get(index).b + "\nC. " + questions.get(index).c + "\nD. " + questions.get(index).d);
        });

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
}
