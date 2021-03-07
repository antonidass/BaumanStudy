package com.example.lesson1;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.res.ResourcesCompat;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);



        final TextView view = findViewById(R.id.mainView);
        view.setTextColor(Color.BLUE);

        String s = getString(R.string.app_name);

        int color = ResourcesCompat.getColor(getResources(), R.color.purple_200, getTheme());
        view.setTextColor(color);

        Button button = findViewById(R.id.buttonMain);


    }


    private class MyClickListener implements View.OnClickListener {
        private TextView mTextView;

        public MyClickListener(TextView view) {
            mTextView = view;
        }

        @Override
        public void onClick(View v) {
            incrementCounter(mTextView, mTextView.getId() == R.id.buttonMain);

        }
    }


    private void incrementCounter(TextView viewToIncrement, boolean increment) {
        String currentText = viewToIncrement.getText().toString();
        int currentNumber = Integer.parseInt(currentText);
        int nextNumber = increment ? currentNumber + 1 : currentNumber - 1;
        viewToIncrement.setText(String.valueOf(nextNumber));
    }






}