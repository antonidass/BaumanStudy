package com.example.beeradvisor;

import java.util.ArrayList;
import java.util.List;


public class BeerExpert {

    public List<String> getBrands(String color) {
        List<String> brands = new ArrayList<String>();

        if (color.equals("amber")) {
            brands.add("Antoxa amber");
            brands.add("Red Antoxa");
        }
        else {
            brands.add("Russian Govno");
            brands.add("Sobachiy shit");
        }

        return brands;
    }
}
