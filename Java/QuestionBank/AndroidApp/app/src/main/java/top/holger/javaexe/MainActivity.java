package top.holger.javaexe;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.View;
import android.widget.*;
import androidx.appcompat.app.AppCompatActivity;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

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

public class MainActivity extends AppCompatActivity {
    Button prevBtn;
    Button nextBtn;
    RadioButton aBtn;
    RadioButton bBtn;
    RadioButton cBtn;
    RadioButton dBtn;
    TextView text;

    ArrayList<Question> questions = new ArrayList<>();
    int index = 0;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        prevBtn = findViewById(R.id.prev_btn);
        nextBtn = findViewById(R.id.next_btn);
        aBtn = findViewById(R.id.choice_A);
        bBtn = findViewById(R.id.choice_B);
        cBtn = findViewById(R.id.choice_C);
        dBtn = findViewById(R.id.choice_D);
        text = findViewById(R.id.main_text);

        loadData();
        text.setEnabled(false);

        View.OnClickListener listener = new ButtonListener();
        prevBtn.setOnClickListener(listener);
        nextBtn.setOnClickListener(listener);
        aBtn.setOnClickListener(listener);
        bBtn.setOnClickListener(listener);
        cBtn.setOnClickListener(listener);
        dBtn.setOnClickListener(listener);

        Question q = questions.get(index);
        text.setText(q.id + ": " + q.detail);
        aBtn.setText("A: " + q.a);
        bBtn.setText("B: " + q.b);
        cBtn.setText("C: " + q.c);
        dBtn.setText("D: " + q.d);
        ((RadioGroup)findViewById(R.id.group_btn)).clearCheck();
    }

    private void loadData() {
        StringBuilder string = new StringBuilder();
        try {
            InputStream is = getResources().openRawResource(R.raw.data);
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            String line;
            while ((line = br.readLine()) != null) {
                string.append(line);
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }
        try {
            JSONObject jsonObject = new JSONObject(string.toString()).getJSONObject("question");
            JSONArray jsonArray = jsonObject.getJSONArray("questionList");
            for (int i = 0; i < jsonArray.length(); i++) {
                JSONObject json = (JSONObject) jsonArray.opt(i);
                int id = Integer.parseInt(json.getString("id"));
                String detail = json.getString("detail");
                String a = json.getString("a");
                String b = json.getString("b");
                String c = json.getString("c");
                String d = json.getString("d");
                String ans = json.getString("ans");
                questions.add(new Question(id, detail, a, b, c, d, ans));
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    class ButtonListener implements View.OnClickListener {

        @SuppressLint({"NonConstantResourceId", "SetTextI18n"})
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.choice_A:
                    if (questions.get(index).check("A")) {
                        Toast.makeText(MainActivity.this.getApplicationContext(), "回答正确", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(MainActivity.this.getApplicationContext(),
                                "回答错误，正确答案为：" + questions.get(index).ans, Toast.LENGTH_LONG).show();
                    }
                    break;
                case R.id.choice_B:
                    if (questions.get(index).check("B")) {
                        Toast.makeText(MainActivity.this.getApplicationContext(), "回答正确", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(MainActivity.this.getApplicationContext(),
                                "回答错误，正确答案为：" + questions.get(index).ans, Toast.LENGTH_LONG).show();
                    }
                    break;
                case R.id.choice_C:
                    if (questions.get(index).check("C")) {
                        Toast.makeText(MainActivity.this.getApplicationContext(), "回答正确", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(MainActivity.this.getApplicationContext(),
                                "回答错误，正确答案为：" + questions.get(index).ans, Toast.LENGTH_LONG).show();
                    }
                    break;
                case R.id.choice_D:
                    if (questions.get(index).check("D")) {
                        Toast.makeText(MainActivity.this.getApplicationContext(), "回答正确", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(MainActivity.this.getApplicationContext(),
                                "回答错误，正确答案为：" + questions.get(index).ans, Toast.LENGTH_LONG).show();
                    }
                    break;
                case R.id.next_btn:
                    if (index >= questions.size() - 1) {
                        index = questions.size() - 1;
                    } else {
                        index++;
                    }
                    Question q = questions.get(index);
                    text.setText(q.id + ": " + q.detail);
                    aBtn.setText("A: " + q.a);
                    bBtn.setText("B: " + q.b);
                    cBtn.setText("C: " + q.c);
                    dBtn.setText("D: " + q.d);
                    ((RadioGroup)findViewById(R.id.group_btn)).clearCheck();
                    break;
                case R.id.prev_btn:
                    if (index <= 0) {
                        index = 0;
                    } else {
                        index--;
                    }
                    Question q2 = questions.get(index);
                    text.setText(q2.id + ": " + q2.detail);
                    aBtn.setText("A: " + q2.a);
                    bBtn.setText("B: " + q2.b);
                    cBtn.setText("C: " + q2.c);
                    dBtn.setText("D: " + q2.d);
                    ((RadioGroup)findViewById(R.id.group_btn)).clearCheck();
                    break;
            }
        }
    }
}