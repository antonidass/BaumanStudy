package com.example.beersself;

import java.util.ArrayList;
import java.util.List;

public class AnimalVoices {

    public List<String> getVoiceAnimal(String animal) {
        List<String> voice_animal = new ArrayList<String>();

        if (animal.equals("parrot")) {
            voice_animal.add("car car");
            voice_animal.add("popka jurak");
        }
        else if (animal.equals("cat")) {
            voice_animal.add("Meooooow");
            voice_animal.add("mur myak");
        }
        else {
            voice_animal.add("bark bark");
            voice_animal.add("baaark Bark");
        }

        return voice_animal;
    }

}
