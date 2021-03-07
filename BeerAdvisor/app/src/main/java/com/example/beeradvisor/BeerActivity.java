package com.example.beeradvisor;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Spinner;
import android.widget.TextView;

import java.util.List;

public class BeerActivity extends AppCompatActivity {
    private BeerExpert beerExpert = new BeerExpert();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_find_beer);
    }

    // Call when user click the button
    public void onClickFindBeer(View view) {
        TextView brands = (TextView) findViewById(R.id.brands);
        Spinner color = (Spinner) findViewById(R.id.color);

        String beerType = String.valueOf(color.getSelectedItem());

        List<String> sorts = beerExpert.getBrands(beerType);
        StringBuilder brandsFormatted = new StringBuilder();

        for (String brand : sorts) {
            brandsFormatted.append(brand).append('\n');
        }

        brands.setText(brandsFormatted);
    }



}