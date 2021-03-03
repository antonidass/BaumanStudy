package ioHandle;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class ioHandle {

    public static int getInt() throws IOException, MyException {
        Scanner scanner = new Scanner(System.in);
        int choice;
        try {
            choice = scanner.nextInt();

        } catch (InputMismatchException exception) {
            throw new MyException("Error in input choice");
        }

        return choice;
    }

    public static double getDouble() throws MyException {
        Scanner scanner = new Scanner(System.in);
        double num;

        try {
            num = scanner.nextDouble();
        } catch (InputMismatchException exception) {
            throw new MyException("Error in value argument");
        }

        return num;
    }

    public static String getString() throws MyException {
        Scanner scanner = new Scanner(System.in);
        String string;

        try {
            string = scanner.nextLine();
        } catch (InputMismatchException exception) {
            throw new MyException("Error in file name");
        }

        return string;
    }

    public static double[][] inputTable(String uri) throws IOException {
        Path path = Path.of(uri);
        List<String> list = Files.readAllLines(path);

        double table[][] = new double[list.size()][list.size()];

        for (int i = 0; i < list.size(); i++) {
            table[i][0] = Double.valueOf(list.get(i).split(" ")[0]).doubleValue();
            table[i][1] = Double.valueOf(list.get(i).split(" ")[1]).doubleValue();
            table[i][2] = Double.valueOf(list.get(i).split(" ")[2]).doubleValue();
        }

        return table;
    }

    public static double[][] inputAddedTable(String uri) throws IOException {
        Path path = Path.of(uri);
        List<String> list = Files.readAllLines(path);

        double table[][] = new double[list.size() * 2][list.size() * 2];

        int k = 0;
        for (int i = 0; i < list.size(); i++) {
            table[k][0] = Double.valueOf(list.get(i).split(" ")[0]).doubleValue();
            table[k][1] = Double.valueOf(list.get(i).split(" ")[1]).doubleValue();
            table[k++][2] = Double.valueOf(list.get(i).split(" ")[2]).doubleValue();

            table[k][0] = Double.valueOf(list.get(i).split(" ")[0]).doubleValue();
            table[k][1] = Double.valueOf(list.get(i).split(" ")[1]).doubleValue();
            table[k++][2] = Double.valueOf(list.get(i).split(" ")[2]).doubleValue();
        }

        return table;
    }

    public static double[][] inputRootTable(String uri) throws IOException {
        Path path = Path.of(uri);
        List<String> list = Files.readAllLines(path);

        double table[][] = new double[list.size()][list.size()];

        for (int i = 0; i < list.size(); i++) {
            table[i][0] = Double.valueOf(list.get(i).split(" ")[1]).doubleValue();
            table[i][1] = Double.valueOf(list.get(i).split(" ")[0]).doubleValue();
            table[i][2] = Double.valueOf(list.get(i).split(" ")[2]).doubleValue();
        }

        return table;
    }
}
