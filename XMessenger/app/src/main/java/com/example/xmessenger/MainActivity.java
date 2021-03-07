package com.example.xmessenger;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    private final int key = 11111111;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    private String CodeMsg(String message) {
        StringBuilder stringBuilder = new StringBuilder();

        for (int i = 0; i < message.length(); i++) {
            stringBuilder.append((char) (message.charAt(i) ^ key));
        }

        return stringBuilder.toString();
    }

    public void onClickDecodeMsg(View view) {
        EditText text = (EditText) findViewById(R.id.message);
        String message = text.getText().toString();

        String decoded_message = CodeMsg(message);
        text.setText(decoded_message);
    }

    public void onClickSendMsg(View view) {
        EditText text = (EditText) findViewById(R.id.message);
        String message = text.getText().toString();

        Intent intent = new Intent(Intent.ACTION_SEND);
        intent.setType("text/plain");
        intent.putExtra(Intent.EXTRA_TEXT, CodeMsg(message));

        String chooserTitle = "Send message...";
        Intent chooserIntent = Intent.createChooser(intent, chooserTitle);
        startActivity(chooserIntent);
    }
}