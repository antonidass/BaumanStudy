package com.example.beersself;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Spinner;
import android.widget.TextView;

import java.util.List;

public class MainActivity extends AppCompatActivity {
    private AnimalVoices animalVoices = new AnimalVoices();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onClickFindVoices(View view) {
        TextView voices_field = (TextView) findViewById(R.id.voices_field);
        Spinner animals = (Spinner) findViewById(R.id.choice_animals);

        List<String> voices = animalVoices.getVoiceAnimal(String.valueOf(animals.getSelectedItem()));

        StringBuilder formattedVoices = new StringBuilder();

        for (String voice : voices) {
            formattedVoices.append(voice).append('\n');
        }

        voices_field.setText(formattedVoices);
    }
}