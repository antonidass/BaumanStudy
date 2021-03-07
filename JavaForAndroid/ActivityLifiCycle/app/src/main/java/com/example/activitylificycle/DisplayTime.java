package com.example.activitylificycle;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.TextView;

public class DisplayTime extends AppCompatActivity {
    private int seconds = 0;
    private boolean running = false;
    private boolean was_running = false;


    private void StartTimer() {
        TextView text_time = (TextView) findViewById(R.id.timer);
        Handler handler = new Handler();

        handler.post(new Runnable() {
            @Override
            public void run() {
                int hours = seconds / 3600;
                int minutes = (seconds % 3600) / 60;
                int secs = seconds % 60;

                String time = String.format("%d:%2d:%2d", hours, minutes, secs);
                text_time.setText(time);

                if (running) {
                    seconds++;
                }

                handler.postDelayed(this, 1000);
            }
        });
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_time);

        Intent intent = getIntent();
        String color = intent.getStringExtra("color");

        TextView text_time = (TextView) findViewById(R.id.timer);

        if (color.equals("green")) {
            text_time.setTextColor(getResources().getColor(R.color.green));
        }
        else if (color.equals("blue")) {
            text_time.setTextColor(getResources().getColor(R.color.blue));
        }
        else {
            text_time.setTextColor(getResources().getColor(R.color.black));
        }

        if (savedInstanceState != null) {
            seconds = savedInstanceState.getInt("seconds");

            was_running = savedInstanceState.getBoolean("was_running");
            if (was_running)
                running = savedInstanceState.getBoolean("running");
        }
        else {
            running = true;
            was_running = true;
        }

        StartTimer();
    }

    public void onClickStopTimer(View view) {
        running = !running;
        was_running = running;
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putInt("seconds", seconds);
        savedInstanceState.putBoolean("running", !running);
        savedInstanceState.putBoolean("was_running", was_running);
    }

  
    @Override
    protected void onPause() {
        super.onPause();
        was_running = running;
        running = false;
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (was_running) {
            running = true;
        }
    }
}