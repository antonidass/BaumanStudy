import java.util.ArrayList;
import java.util.function.DoublePredicate;

public class Geometry {
    public ArrayList<ArrayList<Double>> Points;

    public ArrayList<Double> xNewCoords;
    public ArrayList<Double> yNewCoords;

    public Double Rad;
    public Double squareT;
    public Double squareC;
    public int countPoints;


    Geometry() {
        Points = new ArrayList<ArrayList<Double>>(10);
        countPoints = 0;
        xNewCoords = new ArrayList<>(10);
        yNewCoords = new ArrayList<>(10);
    }

    public void addPoint(Double x, Double y) {
        ArrayList<Double> newPoint = new ArrayList<>(2);
        newPoint.add(0, x);
        newPoint.add(1, y);
        this.countPoints++;

        this.Points.add(newPoint);
    }


    // уравнение окружности (x - xCenter)^2 + (y - yCenter)^2 = R^2

    public Double[] getCircle(Double x1, Double y1, Double x2, Double y2, Double x3, Double y3) {
        Double xCenter, yCenter, Radius;

        Double k1 = x1 * x1 + y1 * y1 - x2 * x2 - y2 * y2;
        Double k2 = x2 * x2 + y2 * y2 - x3 * x3 - y3 * y3;
        Double k3 = x1 * x1 + y1 * y1 - x3 * x3 - y3 * y3;

        yCenter = (k1 * (x2 - x3) - k2 * (x1 - x2)) / (2 * ((y1 - y2) * (x2 - x3) - (y2 - y3) * (x1 - x2)));

        if (x1.equals(x2)) {
            xCenter = (k3 - 2 * yCenter * (y1 - y3)) / (2 * (x1 - x3));
        }
        else {
            xCenter = (k1 - 2 * yCenter * (y1 - y2)) / (2 * (x1 - x2));
        }

        Radius = Math.sqrt((x1 - xCenter) * (x1 - xCenter) + (y1 - yCenter) * (y1 - yCenter));

        return new Double[]{xCenter, yCenter, Radius};
    }


    public Double getSquareTriangle(Double x1, Double y1, Double x2, Double y2, Double x3, Double y3) {
        return Math.abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
    }


    public Double getSide(Double x1, Double y1, Double x2, Double y2) {
        return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }


    public Double getSquareCircle(Double x1, Double y1, Double x2, Double y2, Double x3, Double y3, Double squareTriangle) {
        Double side1 = getSide(x1, y1, x2, y2);
        Double side2 = getSide(x2, y2, x3, y3);
        Double side3 = getSide(x1, y1, x3, y3);

        Double Radius = side1 * side2 * side3 / (4 * squareTriangle);

        return Math.PI * Radius * Radius;
    }


    public Double[] getMaxDiff() {

        Double squareTriangle, squareCircle;
        Double maxDiff = -1.0, curDiff;
        Double x1Max = null, y1Max = null, x2Max = null, y2Max = null, x3Max = null, y3Max = null;
        Double numMax1 = -1.0, numMax2 = -1.0, numMax3 = -1.0;

        for (int i = 0; i < Points.size(); i++) {
            for (int j = i + 1; j < Points.size(); j++) {
                for (int k = j + 1; k < Points.size(); k++) {
                    Double x1 = Points.get(i).get(0);
                    Double y1 = Points.get(i).get(1);
                    Double x2 = Points.get(j).get(0);
                    Double y2 = Points.get(j).get(1);
                    Double x3 = Points.get(k).get(0);
                    Double y3 = Points.get(k).get(1);

                    squareTriangle = getSquareTriangle(x1, y1, x2, y2, x3, y3);

                    // Проверка существования треугольника
                    if (squareTriangle.equals(0.0)) {
                        continue;
                    }

                    squareCircle = getSquareCircle(x1, y1, x2, y2, x3, y3, squareTriangle);

                    curDiff = squareCircle - squareTriangle;

                    if (curDiff > maxDiff) {
                        numMax1 = Double.valueOf(i);
                        numMax2 = Double.valueOf(j);
                        numMax3 = Double.valueOf(k);
                        maxDiff = curDiff;
                        x1Max = x1; x2Max = x2; x3Max = x3;
                        y1Max = y1; y2Max = y2; y3Max = y3;

                        squareT = squareTriangle;
                        squareC = squareCircle;
                    }
                }
            }
        }

        return new Double[]{maxDiff, x1Max, y1Max, x2Max, y2Max, x3Max, y3Max, numMax1, numMax2, numMax3};
    }
}
