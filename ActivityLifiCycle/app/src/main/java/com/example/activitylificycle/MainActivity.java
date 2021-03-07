package com.example.activitylificycle;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Spinner;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public void onClickStartTimer(View view) {
        Spinner choice_color = (Spinner) findViewById(R.id.choice_color);

        String color = choice_color.getSelectedItem().toString();

        Intent intent = new Intent(this, DisplayTime.class);
        intent.putExtra("color", color);
        startActivity(intent);
    }
}