package ioHandle;

import java.io.IOException;
import java.util.InputMismatchException;
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
}
