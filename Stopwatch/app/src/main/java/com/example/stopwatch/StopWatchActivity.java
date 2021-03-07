package com.example.stopwatch;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.TextView;

public class StopWatchActivity extends AppCompatActivity {
    private int seconds = 0;
    private boolean running = false;
    private boolean was_running = false;




    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stopwatch);

        if (savedInstanceState != null) {
            seconds = savedInstanceState.getInt("secs");
            running = savedInstanceState.getBoolean("run");
            was_running = savedInstanceState.getBoolean("wasRunning");
        }

        runTimer();
    }

//
//    @Override
//    protected void onStop() {
//        super.onStop();
//        was_running = running;
//        running = false;
//    }
//
//    @Override
//    protected void onStart() {
//        super.onStart();
//
//        if (was_running) {
//            running = true;
//        }
//    }

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


    public void onClickStart(View view) {
        was_running = true;
        running = true;
    }

    public void onClickStop(View view) {
        was_running = false;
        running = false;
    }

    public void onClickReset(View view) {
        was_running = false;
        running = false;
        seconds = 0;
    }

    private void runTimer() {
        final TextView timer = (TextView) findViewById(R.id.time);
        final Handler handler = new Handler();

        handler.post(new Runnable() {
            @Override
            public void run() {
                int hours = seconds / 3600;
                int minutes = (seconds % 3600) / 60;
                int secs = seconds % 60;

                String time = String.format("%d:%02d:%02d", hours, minutes, secs);
                timer.setText(time);

                if (running) {
                    seconds++;
                }
                handler.postDelayed(this, 1000);
            }
        });
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putInt("secs", seconds);
        savedInstanceState.putBoolean("run", running);
        savedInstanceState.putBoolean("wasRunning", was_running);
    }
}




