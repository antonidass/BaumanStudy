package com.example.workout;

public class Workout {
    private String name;
    private String description;

    public static final Workout[] workouts = {
            new Workout("The Limb Lossenere", "5 hsuava push aps \n 10 1-legged squats \n 15 Pull ups"),
            new Workout("Core Agony", "100 pull ups \n 100 push ups \n 100-sit ups \100 squats"),
            new Workout("The wimp special", "5 pull ups \n 10 push ups \n 15 squats"),
            new Workout("Stringth", "500 meter run\n 21 x 1.5 pood keteleboll swing\n21 x pull ups")
    };


    private Workout(String name, String description) {
        this.name = name;
        this.description = description;
    }

    public String getDescription() {
        return description;
    }

    public String getName() {
        return name;
    }

    public String toString() {
        return this.name;
    }
}

