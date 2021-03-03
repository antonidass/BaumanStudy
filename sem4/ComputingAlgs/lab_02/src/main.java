import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class main {

    public static Double f(Double x, Double y) {
        return x * x + y * y;
    }

    public static void printMatrix(ArrayList<Double> x, ArrayList<Double> y, ArrayList<ArrayList<Double>> z) {
        System.out.println("\nСозданная матрица: ");

        System.out.print("y\\x  ");
        for (int i = 0; i < x.size(); i++) {
            System.out.print(x.get(i) + "  ");
        }
        System.out.println();

        for (int i = 0; i < y.size(); i++) {
            System.out.print(y.get(i) + "  ");
            for (int j = 0; j < y.size(); j++) {
                System.out.print(z.get(i).get(j) + "  ");
            }
            System.out.println();
        }
    }

    public static ArrayList<Object> getMatrix(Double x_begin, Double x_step, int x_amount_dots, Double y_begin, Double y_step, int y_amount_dots) {
        ArrayList<Double> x = new ArrayList<>(x_amount_dots);
        ArrayList<Double> y = new ArrayList<>(y_amount_dots);
        ArrayList<ArrayList<Double>> z = new ArrayList<>(y_amount_dots);

        for (int i = 0; i < x_amount_dots; i++) {
            x.add(i, x_begin + i * x_step);
        }

        for (int i = 0; i < y_amount_dots; i++) {
            y.add(i, y_begin + i * y_step);
        }

        for (int i = 0; i < y_amount_dots; i++) {
            ArrayList<Double> temp = new ArrayList<>(x_amount_dots);

            for (int j = 0; j < x_amount_dots; j++) {
                temp.add(j, f(x.get(j), y.get(i)));
            }

            z.add(i, temp);
        }

        return new ArrayList<>(Arrays.asList(x, y, z));
    }



    public static ArrayList<Integer> chooseDots(ArrayList<Double> array, int n, Double x) {
        Double minValue = Math.abs(array.get(0) - x);
        int index_nearest = 0;

        for (int i = 1; i < array.size(); i++) {
            if (Math.abs(array.get(i) - x)  < minValue) {
                index_nearest = i;
                minValue = Math.abs(array.get(i) - x);
            }
        }

        int spaces = (int) Math.ceil(n / 2.0);
        int i_end;
        int i_start;

        if (index_nearest + spaces + 1 > array.size()) {
            i_end =  array.size();
            i_start = array.size() - n;
        }
        else if (index_nearest < spaces) {
            i_start = 0;
            i_end = n;
        }
        else {
            i_start = index_nearest - spaces + 1;
            i_end = i_start + n;
        }

        ArrayList<Integer> result = new ArrayList<>(2);
        result.add(0, i_start);
        result.add(1, i_end);

        return result;
    }


    public static ArrayList<ArrayList<Double>> getDiffMatrix(ArrayList<ArrayList<Double>> table, int n) {
        for (int i = 0; i < n; i++) {
            ArrayList<Double> temp = new ArrayList<>();

            for (int j = 0; j < n - i; j++) {
                temp.add((table.get(i + 1).get(j) - table.get(i + 1).get(j + 1)) / (table.get(0).get(j) - table.get(0).get(i + j + 1)));
            }

            table.add(temp);
        }

        return table;
    }


    public static Double newton_interpolation(ArrayList<ArrayList<Double>> table, int n, Double x) {
        ArrayList<ArrayList<Double>> matrix = getDiffMatrix(table, n);

        Double temp = 1.0, result = 0.0;

        for (int i = 0; i < n + 1; i++) {
            result += temp * matrix.get(i + 1).get(0);
            temp *= (x - matrix.get(0).get(i));
        }

        return result;
    }


    public static Double mult_interpolation(ArrayList<Double> x, ArrayList<Double> y, ArrayList<ArrayList<Double>> z, Double x_val, Double y_val, int x_n, int y_n) {
        ArrayList<Integer> indexesX = chooseDots(x, x_n + 1, x_val);
        ArrayList<Integer> indexesY = chooseDots(y, y_n + 1, y_val);

        int ix_begin = indexesX.get(0);
        int ix_end = indexesX.get(1);

        int iy_begin = indexesY.get(0);
        int iy_end = indexesY.get(1);

        ArrayList<Double> newX = new ArrayList<>();
        ArrayList<Double> newY = new ArrayList<>();
        ArrayList<ArrayList<Double>> newZ = new ArrayList<>();

        for (int i = ix_begin; i < ix_end; i++) {
            newX.add(x.get(i));
        }

        for (int i = iy_begin; i < iy_end; i++) {
            newY.add(y.get(i));
            newZ.add(z.get(i));
        }


        for (int i = 0; i < y_n + 1; i++) {
            ArrayList<Double> temp = new ArrayList<>();
            for (int j = ix_begin; j < ix_end; j++) {
                temp.add(newZ.get(i).get(j));
            }
            newZ.set(i, temp);
        }

        ArrayList<Double> result = new ArrayList<>();

        for (int i = 0; i < y_n + 1; i++) {
            ArrayList<ArrayList<Double>> arrayList = new ArrayList<>();
            arrayList.add(newX);
            arrayList.add(newZ.get(i));
            result.add(newton_interpolation(arrayList, x_n, x_val));
        }

        ArrayList<ArrayList<Double>> arrayList = new ArrayList<>();
        arrayList.add(newY);
        arrayList.add(result);

        return newton_interpolation(arrayList, y_n, y_val);
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите начальное значение x : ");
        Double x_begin = scanner.nextDouble();

        System.out.print("Введите шаг для x : ");
        Double x_step = scanner.nextDouble();

        System.out.print("Введите количество точек : ");
        int x_amount_dots = scanner.nextInt();

        System.out.print("Введите начальное значение y : ");
        Double y_begin = scanner.nextDouble();

        System.out.print("Введите шаг для y : ");
        Double y_step = scanner.nextDouble();

        System.out.print("Введите количество точек : ");
        int y_amount_dots = scanner.nextInt();


        ArrayList<Object> matrix = getMatrix(x_begin, x_step, x_amount_dots, y_begin, y_step, y_amount_dots);

        ArrayList<Double> x = (ArrayList<Double>) matrix.get(0);
        ArrayList<Double> y = (ArrayList<Double>) matrix.get(1);
        ArrayList<ArrayList<Double>> z = (ArrayList<ArrayList<Double>>) matrix.get(2);

        printMatrix(x, y, z);

        int x_n, y_n;
        Double x_find, y_find;

        System.out.print("\nВведите n(x): ");
        x_n = scanner.nextInt();

        System.out.print("Введите x : ");
        x_find = scanner.nextDouble();

        System.out.print("Введите n(y): ");
        y_n = scanner.nextInt();

        System.out.print("Введите y : ");
        y_find = scanner.nextDouble();


        Double found = mult_interpolation(x, y, z, x_find, y_find, x_n, y_n);


        System.out.println("\nРезультат интерполирования = " + found);
        System.out.println("f(x) = " + f(x_find, y_find));
        System.out.println("Погрешность = " + Math.abs(f(x_find, y_find) - found));
    }
}
