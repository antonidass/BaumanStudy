package com.example.layoutwork;

import androidx.appcompat.app.AppCompatActivity;

import android.media.Image;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Switch;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public void onClickSwitch(View view) {
        boolean on = ((Switch) view).isChecked();

        if (on)
        {
            System.out.println("ON");
        }
        else {
            System.out.println("OFF");
        }
    }


    public void onClickCheckBox(View view) {
        boolean on = ((CheckBox) view).isChecked();

        if (on) {
            if (view.getId() == R.id.kek) {
                System.out.println("KEK");
            }
            else {
                System.out.println("MILK");
            }
        }
        else {
            if (view.getId() == R.id.milk) {
                System.out.println("BEZ MILK");
            }
            else {
                System.out.println("BEZ KEK");
            }
        }
    }

    public void onClickSend(View view) {
        RadioGroup radioGroup = findViewById(R.id.radio_group);

        int id = radioGroup.getCheckedRadioButtonId();

        if (id == -1) {
            System.out.println("No one setted radio");
        }

        else  {
            RadioButton radioButton = findViewById(id);
            System.out.println("Some one setted radio");
        }

        ImageView photo = (ImageView) findViewById(R.id.photo);
        String desc = "Description";
        int image = R.drawable.alien;
        photo.setContentDescription(desc);
        photo.setImageResource(image);


        // Уведомления
        CharSequence text = "Your faggot";
        int duration = Toast.LENGTH_SHORT;
        Toast toast = Toast.makeText(this, text, duration);
        toast.show();
    }

    public void onRadioButtonClicked(View view) {
        RadioGroup radioGroup = (RadioGroup) findViewById(R.id.radio_group);
        int id = radioGroup.getCheckedRadioButtonId();

        switch (id) {
            case R.id.radio1:
                System.out.println("Ustanovlen 1");
                break;

            case R.id.radio2:
                System.out.println("Ustanovlen 2");
                break;
        }
    }


}