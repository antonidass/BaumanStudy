import java.util.Arrays;
import java.util.Scanner;

public class Main {
    private static Double f(Double x) {
        return x * x;
    }

    private static Double[][] getTable(Double xBegin, Double step, int amount) {
        Double[] xTable = new Double[amount];
        Double[] yTable = new Double[amount];
        Double tempX;

        for (int i = 0; i < amount; i++) {
            tempX = xBegin + step * i;
            xTable[i] = tempX;
            yTable[i] = f(tempX);
        }

        Double[][] table = new Double[2][amount];
        table[0] = xTable;
        table[1] = yTable;

        return table;
    }

    private static void printTable(Double[] x, Double[] y) {
        for (int i = 0; i < y.length; i++) {
            System.out.println("x[i] = " + x[i] + "   y[i] = " + y[i]);
        }
        System.out.println();
    }


    private static int getIndexNear(Double[] x, Double x_value) {
        int i = 0;

        if (x[0] - x[1] < 0) {
            while (x_value > x[i] && i < x.length - 1) {
                i++;
            }
        }
        else {
            while (x_value < x[i] && i < x.length - 1) {
                i++;
            }
        }

        return i;
    }

    private static Double[] getStep(Double[] x) {
        Double[] step = new Double[x.length];
        step[0] = 0.0;

        for (int i = 1; i < x.length; i++) {
                step[i] = x[i] - x[i - 1];
        }

        return step;
    }

    private static Double[][] getXiEta(Double[] step, Double[] y) {
        Double[] A = new Double[y.length];
        Double[] B = new Double[y.length];
        Double[] D = new Double[y.length];
        Double[] F = new Double[y.length];

        A[0] = 0.0; A[1] = 0.0; B[0] = 0.0; B[1] = 0.0; D[0] = 0.0; D[1] = 0.0; F[0] = 0.0; F[1] = 0.0;

        for (int i = 2; i < y.length; i++) {
            A[i] = step[i - 1];
            B[i] = -2 * (step[i - 1] + step[i]);
            D[i] = step[i];
            F[i] = -3 * ((y[i] - y[i - 1]) / step[i] - (y[i - 1] - y[i - 2]) / step[i - 1]);
        }

        Double[] xi = new Double[y.length + 1];
        Double[] eta = new Double[y.length + 1];
        xi[0] = 0.0; xi[1] = 0.0; xi[2] = 0.0;
        eta[0] = 0.0; eta[1] = 0.0; eta[2] = 0.0;

        for (int i = 2; i < y.length; i++) {
            xi[i + 1] = D[i] / (B[i] - A[i] * xi[i]);
            eta[i + 1] = (A[i] * eta[i] + F[i]) / (B[i] - A[i] * xi[i]);
        }

        Double[][] result = new Double[2][y.length];
        result[0] = xi;
        result[1] = eta;

        return result;
    }


    private static Double interpolate(Double[] x, Double[] y, Double x_value) {
        Double[] step = getStep(x);

        Double[][] temp = getXiEta(step, y);
        Double[] xi = temp[0];
        Double[] eta = temp[1];

        Double[] c = new Double[x.length + 1];
        Arrays.fill(c, 0.0);

        c[c.length - 2] = eta[eta.length - 1];

        for (int i = c.length - 2; i > 1; i--) {
            c[i] = xi[i + 1] * c[i + 1] + eta[i + 1];
        }

        Double[] a = new Double[x.length + 1];
        Double[] b = new Double[x.length + 1];
        Double[] d = new Double[x.length + 1];

        for (int i = 0; i < d.length; i++) {
            d[i] = 0.0;
            b[i] = 0.0;
        }

        a[0] = 0.0; b[0] = 0.0; d[0] = 0.0;

        for (int i = 0; i < y.length; i++) {
            a[i + 1] = y[i];
        }

        for (int i = 1; i < d.length - 1; i++) {
            b[i] = (y[i] - y[i - 1]) / step[i] - step[i] / 3 * (c[i + 1] + 2 * c[i]);
            d[i] = (c[i + 1] - c[i]) / (3 * step[i]);
        }

        int index_near = getIndexNear(x, x_value);

        return a[index_near] + b[index_near] * (x_value - x[index_near - 1]) +
                c[index_near] * (Math.pow(x_value - x[index_near - 1], 2)) +
                d[index_near] * (Math.pow(x_value - x[index_near - 1], 3));
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Введите начало значения X : ");
        Double xBegin = scanner.nextDouble();
        System.out.print("Введите шаг значения X : ");
        Double xStep = scanner.nextDouble();
        System.out.print("Введите количество точек : ");
        int pointsAmount = scanner.nextInt();

        Double[][] table = getTable(xBegin, xStep, pointsAmount);
        printTable(table[0], table[1]);

        System.out.print("Введите значение X : ");
        Double x_value = scanner.nextDouble();

        Double result = interpolate(table[0], table[1], x_value);

        System.out.println("Результат интерполяции: " + result);
        System.out.println("F(x) = " + f(x_value));
     }
}
