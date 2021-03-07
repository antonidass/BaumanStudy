package com.example.whathappenednext;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class EndActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_end);

        TextView textView = (TextView) findViewById(R.id.result);

        String result = CountAnswers.getResult();
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("Поздравляю ты ");
        stringBuilder.append(result);

        textView.setText(stringBuilder.toString());
    }
}