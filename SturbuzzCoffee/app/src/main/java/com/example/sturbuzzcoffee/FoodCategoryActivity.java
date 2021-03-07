package com.example.sturbuzzcoffee;


import android.app.ListActivity;
import android.os.Bundle;
import android.widget.Adapter;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class FoodCategoryActivity extends ListActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ListView listFoods = getListView();

        ArrayAdapter<Drink> foods = new ArrayAdapter<Drink>(
                this,
                android.R.layout.simple_expandable_list_item_1,
                Drink.drinks);

        listFoods.setAdapter(foods);
    }


}