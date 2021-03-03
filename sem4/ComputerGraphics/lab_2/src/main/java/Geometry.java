import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Geometry implements Cloneable {
    Double xCenter = 420.0;
    Double yCenter = 376.0;
    Double EPS = 1e-6;

    List<List<Double>> Door;
    List<List<Double>> SmallWindow;
    List<List<Double>> RombDoor;
    List<List<Double>> CrossSmallWindow;
    List<List<Double>> House;
    List<List<Double>> Window;
    List<List<Double>> CrossWindow;



    Double doorA, doorB;
    Double smallWindowA, smallWindowB;

    public Geometry Clone() {
        Geometry newGeometry = new Geometry();
        newGeometry.Door.clear();
        newGeometry.SmallWindow.clear();
        newGeometry.RombDoor.clear();
        newGeometry.CrossWindow.clear();
        newGeometry.CrossSmallWindow.clear();
        newGeometry.House.clear();
        newGeometry.Window.clear();

        for (int i = 0; i < Door.size(); i++) {
            newGeometry.Door.add(Arrays.asList(this.Door.get(i).get(0).doubleValue(), this.Door.get(i).get(1).doubleValue()));
        }

        for (int i = 0; i < SmallWindow.size(); i++) {
            newGeometry.SmallWindow.add(Arrays.asList(this.SmallWindow.get(i).get(0).doubleValue(), this.SmallWindow.get(i).get(1).doubleValue()));
        }

        for (int i = 0; i < RombDoor.size(); i++) {
            newGeometry.RombDoor.add(Arrays.asList(this.RombDoor.get(i).get(0).doubleValue(), this.RombDoor.get(i).get(1).doubleValue()));
        }

        for (int i = 0; i < House.size(); i++) {
            newGeometry.House.add(Arrays.asList(this.House.get(i).get(0).doubleValue(), this.House.get(i).get(1).doubleValue()));
        }

        for (int i = 0; i < CrossSmallWindow.size(); i++) {
            newGeometry.CrossSmallWindow.add(Arrays.asList(this.CrossSmallWindow.get(i).get(0).doubleValue(), this.CrossSmallWindow.get(i).get(1).doubleValue()));
        }

        for (int i = 0; i < Window.size(); i++) {
            newGeometry.Window.add(Arrays.asList(this.Window.get(i).get(0).doubleValue(), this.Window.get(i).get(1).doubleValue()));
        }

        for (int i = 0; i < CrossWindow.size(); i++) {
            newGeometry.CrossWindow.add(Arrays.asList(this.CrossWindow.get(i).get(0).doubleValue(), this.CrossWindow.get(i).get(1).doubleValue()));
        }

        return newGeometry;
    }


    public List<List<Double>> getDoor(Double a, Double b) {
        List<List<Double>> door = new ArrayList<>();

        for (Double t = 0.0; t - 2 * Math.PI < EPS; t += 0.01) {
            ArrayList<Double> point = new ArrayList<>(2);
            point.add(-a * Math.cos(t) + xCenter + 100);
            point.add(b * Math.sin(t) + yCenter);
            door.add(point);
        }

        return door;
    }

    public List<List<Double>> getRombDoor() {
        List<List<Double>> romb = new ArrayList<>(4);

        romb.add(Arrays.asList(xCenter + 100 + doorA, yCenter));
        romb.add(Arrays.asList(xCenter + 100 - doorA, yCenter));
        romb.add(Arrays.asList(xCenter + 100, yCenter + doorB));
        romb.add(Arrays.asList(xCenter + 100, yCenter - doorB));

        return romb;
    }


    public List<List<Double>> getSmallWindowCross() {
        List<List<Double>> cross = new ArrayList<>(4);
        cross.add(Arrays.asList(xCenter - 120 - smallWindowA, yCenter - 40));
        cross.add(Arrays.asList(xCenter - 120 + smallWindowA, yCenter - 40));
        cross.add(Arrays.asList(xCenter - 120, yCenter - 40 + smallWindowB));
        cross.add(Arrays.asList(xCenter - 120, yCenter - 40 - smallWindowB));

        return cross;
    }

    public List<List<Double>> getSmallWindow(Double a, Double b) {
        List<List<Double>> smallWindow = new ArrayList<>();

        for (Double t = 0.0; t - 2 * Math.PI < EPS; t += 0.01) {
            ArrayList<Double> point = new ArrayList<>(2);
            point.add(-a * Math.cos(t) + xCenter - 120);
            point.add(b * Math.sin(t) + yCenter - 40);
            smallWindow.add(point);
        }

        return smallWindow;
    }

    public List<List<Double>> getHouse() {
        List<List<Double>> house = new ArrayList<>();

        house.add(Arrays.asList(this.xCenter, 146.0));
        house.add(Arrays.asList(620.0, 246.0));
        house.add(Arrays.asList(620.0, 506.0));
        house.add(Arrays.asList(220.0, 506.0));
        house.add(Arrays.asList(220.0, 246.0));

        return house;
    }

    public List<List<Double>> getWindow() {
        List<List<Double>> window = new ArrayList<>();

        window.add(Arrays.asList(xCenter - 50, 190.0));
        window.add(Arrays.asList(xCenter + 50, 190.0));
        window.add(Arrays.asList(xCenter + 50, 230.0));
        window.add(Arrays.asList(xCenter - 50, 230.0));

        return window;
    }

    public List<List<Double>> getCrossWindow() {
        List<List<Double>> cross = new ArrayList<>();

        cross.add(Arrays.asList(xCenter, 190.0));
        cross.add(Arrays.asList(xCenter, 230.0));
        cross.add(Arrays.asList(xCenter + 50, 210.0));
        cross.add(Arrays.asList(xCenter - 50, 210.0));

        return cross;
    }




    public void move(List<List<Double>> Coords, Double dx, Double dy) {
        for (int i = 0; i < Coords.size(); i++) {
            Coords.set(i, Arrays.asList(Coords.get(i).get(0) + dx, Coords.get(i).get(1) + dy));
        }
    }

    public void rotate(List<List<Double>> Coords, Double rx, Double ry, Double alpha) {
        Double cosAlpha = Math.cos(Math.toRadians(alpha));
        Double sinAlpha = Math.sin(Math.toRadians(alpha));

        Double x, y, newX, newY;

        for (int i = 0; i < Coords.size(); i++) {
            x = Coords.get(i).get(0);
            y = Coords.get(i).get(1);

            newX = rx + (x - rx) * cosAlpha + (y - ry) * sinAlpha;
            newY = ry - (x - rx) * sinAlpha + (y - ry) * cosAlpha;

            Coords.set(i, Arrays.asList(newX, newY));
        }
    }

    public void scale(List<List<Double>> Coords, Double mx, Double my, Double kx, Double ky) {
        Double newX, newY;

        for (int i = 0; i < Coords.size(); i++) {
            newX = kx * Coords.get(i).get(0) + (1 - kx) * mx;
            newY = ky * Coords.get(i).get(1) + (1 - ky) * my;
            Coords.set(i, Arrays.asList(newX, newY));
        }
    }



    public void UpdateMoveAll(Double dx, Double dy) {
        dy = -dy;

        move(Door, dx, dy);
        move(SmallWindow, dx, dy);
        move(RombDoor, dx, dy);
        move(CrossSmallWindow, dx, dy);
        move(House, dx, dy);
        move(Window, dx, dy);
        move(CrossWindow, dx, dy);
    }

    public void rotateAll(Double rx, Double ry, Double alpha) {
        rotate(Door, rx, ry, alpha);
        rotate(SmallWindow, rx, ry, alpha);
        rotate(RombDoor, rx, ry, alpha);
        rotate(House, rx, ry, alpha);
        rotate(Window, rx, ry, alpha);
        rotate(CrossSmallWindow, rx, ry, alpha);
        rotate(CrossWindow, rx, ry, alpha);
    }


    public void scaleAll(Double mx, Double my, Double kx, Double ky) {
        scale(Door, mx, my, kx, ky);
        scale(SmallWindow, mx, my, kx, ky);
        scale(RombDoor, mx, my, kx, ky);
        scale(House, mx, my, kx, ky);
        scale(Window, mx, my, kx, ky);
        scale(CrossSmallWindow, mx, my, kx, ky);
        scale(CrossWindow, mx, my, kx, ky);
    }


    Geometry() {
        this.doorA = 50.0;
        this.doorB = 80.0;

        this.smallWindowA = 35.0;
        this.smallWindowB = 35.0;

        this.Door = getDoor(doorA, doorB);
        this.SmallWindow = getSmallWindow(smallWindowA, smallWindowB);
        this.RombDoor = getRombDoor();
        this.CrossSmallWindow = getSmallWindowCross();
        this.House = getHouse();
        this.Window = getWindow();
        this.CrossWindow = getCrossWindow();
    }
}
