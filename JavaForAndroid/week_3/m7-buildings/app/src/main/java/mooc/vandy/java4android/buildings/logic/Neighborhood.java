package mooc.vandy.java4android.buildings.logic;

import java.io.FileNotFoundException;

import mooc.vandy.java4android.buildings.ui.OutputInterface;

/**
 * This Neighborhood utility class provides static helper methods the
 * print a Building List and calculate the area of a Building list.
 * A utility class in Java should always be final and have a private
 * constructor.
 */
public final class Neighborhood {
    private Neighborhood() {}

    public static void print(Building[] buildings, String header, OutputInterface out) {
        out.println(header + "\n" + "----------");

        for (Building build : buildings) {
            out.println(build);
        }
    }

    public static int calcArea(Building[] buildings) {
        int area = 0;

        for (Building build : buildings) {
            area += build.calcLotArea();
        }

        return area;
    }
}
