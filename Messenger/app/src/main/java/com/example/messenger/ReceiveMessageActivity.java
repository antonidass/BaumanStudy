package com.example.messenger;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class ReceiveMessageActivity extends AppCompatActivity {
    public static final String EXTRA_MSG = "message";
    public static final String NUM = "44";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_receive_message);

        Intent intent = getIntent();

        String messageText = intent.getStringExtra(EXTRA_MSG);
        Integer num = intent.getIntExtra(NUM, 4);

        TextView textView = (TextView) findViewById(R.id.message);
        textView.setText(num.toString());


    }
}