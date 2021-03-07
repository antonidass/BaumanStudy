package com.example.whathappenednext;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.ArrayList;

public class Questions extends AppCompatActivity {
    private int numberOfQuestion = 0;
    private final int count_questions = 2;
    public ArrayAdapter<String> adapter;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_questions);

        // Находим наш список
        ListView listView = (ListView) findViewById(R.id.first_options);

        adapter = new ArrayAdapter<String>(this,
                                                android.R.layout.simple_list_item_1,
                                                CountAnswers.answers[numberOfQuestion]) {
            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                TextView item = (TextView) super.getView(position, convertView, parent);
                item.setTextColor(getResources().getColor(R.color.red));
                item.setTextSize(getResources().getDimension(R.dimen.item_size));
                item.setGravity(Gravity.CENTER_HORIZONTAL);
                return item;
            }
        };

        listView.setAdapter(adapter);

        AdapterView.OnItemClickListener itemClickListener = new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if (position == 0 || position == 1) {
                    CountAnswers.incNurlan();
                    CountAnswers.incTambi();
                    System.out.println("OKkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk");
                }
                else if (position == 2) {
                    CountAnswers.incLeha();
                }
                else if (position == 3) {
                    System.out.println("RUSTAMMMMM");
                    CountAnswers.incRustam();
                }

                numberOfQuestion++;

                if (numberOfQuestion == count_questions) {
                    Intent intent = new Intent(Questions.this, EndActivity.class);
                    startActivity(intent);
                }

                // Поменять текст у всех элементов ListView
                if (numberOfQuestion < count_questions) {

                    adapter = new ArrayAdapter<String>(Questions.this, android.R.layout.simple_list_item_1,  CountAnswers.answers[numberOfQuestion]) {
                        @Override
                        public View getView(int position, View convertView, ViewGroup parent) {
                            TextView item = (TextView) super.getView(position, convertView, parent);
                            item.setTextColor(getResources().getColor(R.color.red));
                            item.setTextSize(getResources().getDimension(R.dimen.item_size));
                            item.setGravity(Gravity.CENTER_HORIZONTAL);
                            return item;
                        }
                    };

                    listView.setAdapter(adapter);
                }
            }
        };

        listView.setOnItemClickListener(itemClickListener);

        // Обязательно устанавливаем слушателя
    }
}