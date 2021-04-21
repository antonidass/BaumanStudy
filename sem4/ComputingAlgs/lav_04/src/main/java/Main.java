import com.github.sh0nk.matplotlib4j.Plot;
import com.github.sh0nk.matplotlib4j.PythonConfig;
import com.github.sh0nk.matplotlib4j.PythonExecutionException;

import java.io.IOException;
import java.util.*;

public class Main {
    private static Random random = new Random();
    private static Scanner scanner = new Scanner(System.in);
    private static final int SIZE_TABLE = 7;
    private static final Plot plt = Plot.create(PythonConfig.pythonBinPathConfig("/usr/bin/python3"));
    private static final Double DEFAULT_WEIGHT = 1.0;
    private static final Double EPS = 0.01;

    private static Double[][] getTable() {
        Double x = random.nextDouble() * 5;
        Double[][] table = new Double[SIZE_TABLE][3];

        for (int i = 0; i < SIZE_TABLE; i++) {
            Double[] tempRow = new Double[3];
            tempRow[0] = x + i;
            tempRow[1] = random.nextDouble() * 5;
            tempRow[2] = DEFAULT_WEIGHT;

            table[i] = tempRow;
        }

        return table;
    }

    private static void printTable(Double[][] table) {
        System.out.println("\nСозданная таблица\n№        X          Y        W\n");

        for (int i = 0; i < table.length; i++) {
            System.out.printf("%-3d     %-5.2f     %-4.2f     %-5.2f   \n",
                    i + 1, table[i][0], table[i][1], table[i][2]);
        }
    }

    private static void printMenu() {
        System.out.println("\n1 - Вывести на экран таблицу\n" +
                "2 - Изменить вес точки\n" +
                "3 - Вывести результаты\n" +
                "0 - Выход");
    }



    private static void changeWeight(Double[][] table) {
        int index;
        try {
            System.out.print("Введите номер точки в таблице: ");
            index = scanner.nextInt();
        } catch (java.util.InputMismatchException e) {
            System.out.println("Ошибка! Некорректный ввод точки!");
            return;
        }

        if ((index > table.length) || (index < 1)) {
            System.out.println("\nОшибка! Отсутствует точка с таким номером");
            return;
        }

        Double weight;
        try {
            System.out.print("Введите новый вес точки: ");
            weight = scanner.nextDouble();
        } catch (java.util.InputMismatchException e) {
            System.out.println("Ошибка! Некорректный вес точки!");
            return;
        }

        table[index - 1][2] = weight;
    }





    private static Double[][] getDefaultTable(Double [][] table) {
        Double[][] defaultTable = table.clone();

        for (int i = 0; i < table.length; i++) {
            defaultTable[i][2] = 1.0;
        }

        return defaultTable;
    }

    private static boolean isTableChanged(Double [][] table) {
        for (int i = 0; i < table.length; i++) {
            if (table[i][2] != 1) {
                return true;
            }
        }
        return false;
    }


    private static Double[][] initMatrix(int size) {
        Double[][] matrix = new Double[size + 1][size + 2];

        for (int i = 0; i < size + 1; i++) {
            Double[] row = new Double[size + 2];

            for (int j = 0; j < size + 2; j++) {
                row[i] = 0.0;
            }

            matrix[i] = row;
        }

        return matrix;
    }


    private static Double[][] getSlaeMatrix(Double[][] table, int n) {
        Double[][] matrix = initMatrix(n);

        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < n + 1; j++) {
                matrix[i][j] = 0.0;
                matrix[i][n + 1] = 0.0;

                for (int k = 0; k < table.length; k++) {
                    Double weight = table[k][2];
                    Double x = table[k][0];
                    Double y = table[k][1];

                    matrix[i][j] += weight * Math.pow(x, (i + j));
                    matrix[i][n + 1] += weight * y * Math.pow(x, i);
                }
            }
        }

        return matrix;
    }


    private static Double[] solveGauss(Double [][] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = i + 1; j < matrix.length; j++) {
                if (i == j) {
                    continue;
                }

                Double k = matrix[j][i] / matrix[i][i];

                for (int z = i; z < matrix.length + 1; z++) {
                    matrix[j][z] -= k * matrix[i][z];
                }
            }
        }

        Double[] result = new Double[matrix.length];

        Arrays.fill(result, 0.0);

        for (int i = matrix.length - 1; i > -1; i--) {
            for (int j = matrix.length - 1; j > i; j--) {
                matrix[i][matrix.length] -= result[j] * matrix[i][j];
            }
            result[i] = matrix[i][matrix.length] / matrix[i][i];
        }

        return result;
    }




    private static List<List<Double>> findGraphDots(Double[][] table, int n) {
        Double [][] matrix = getSlaeMatrix(table, n);
        Double [] result = solveGauss(matrix);

        List<Double> xArray = new ArrayList<>();
        List<Double> yArray = new ArrayList<>();
        Double k = table[0][0] - EPS;

        while (k <= table[table.length - 1][0] + EPS) {
            Double y = 0.0;

            for (int j = 0; j < n + 1; j++) {
                y += result[j] * Math.pow(k, j);
            }

            xArray.add(k);
            yArray.add(y);

            k += EPS;
        }

        List<List<Double>> temp = new ArrayList<>();
        temp.add(xArray);
        temp.add(yArray);

        return temp;
    }


    private static void plotGraphs(Double [][] table, int n, String typeGraph, String typeDots) {
        for (int i = 1; i < n + 1; i++) {
            if (i > 2 && i < n) continue;

            List<List<Double>> tempTable = findGraphDots(table, i);
            plt.plot()
                    .add(tempTable.get(0), tempTable.get(1))
                    .label(typeDots + " n = " + i)
                    .linestyle(typeGraph);
        }
    }




    private static void solveTask(Double[][] table) throws PythonExecutionException, IOException {
        int n;
        try {
            System.out.print("Введите степень аппроксимирующего полинома: ");
            n = scanner.nextInt();
        } catch (java.util.InputMismatchException e) {
            System.out.println("Ошибка! Некрректно введена степень полинома!");
            return;
        }
        if (n >= SIZE_TABLE || n <= 0) {
            System.out.println("Ошибка! Некрректно введена степень полинома!");
            return;
        }

        String typeDots, typeGraph;
        if (isTableChanged(table)) {
            Double[][] defaultTable = getDefaultTable(table);
            typeDots = "Разные веса";
            typeGraph = "-.";

            plotGraphs(defaultTable, n, "-", "Равыне веса");

        } else {
            typeDots = "Равные веса";
            typeGraph = "-";
        }

        plotGraphs(table, n, typeGraph, typeDots);

        List<Double> xArray = new ArrayList<>();
        List<Double> yArray = new ArrayList<>();

        for (int i = 0; i < table.length; i++) {
            xArray.add(table[i][0]);
            yArray.add(table[i][1]);
        }

        plt.plot().add(xArray, yArray).label("Точки").linestyle("dotted");
        plt.legend();
        plt.xlabel("X");
        plt.ylabel("Y");
        plt.show();
    }






    public static void main(String[] args) throws PythonExecutionException, IOException {

        Double[][] table = getTable();
        printTable(table);

        int choice = 1;

        while (choice != 0) {
            printMenu();

            try {
                System.out.print("Выберите действие: ");
                choice = scanner.nextInt();
            } catch (java.util.InputMismatchException e) {
                System.out.println("Неверный ввод! Повторите попытку!");
                continue;
            }

            switch (choice) {
                case 1:
                    printTable(table);
                    break;
                case 2:
                    changeWeight(table);
                    break;
                case 3:
                    solveTask(table);
                    break;
                default:
                    System.out.println("Ошибка в выборе команды! Повторите попытку");
            }
        }
    }
}
