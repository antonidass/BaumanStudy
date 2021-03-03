import ioHandle.MyException;

import java.io.IOException;

import static Aproximation.Aproximation.getValue;
import static ioHandle.ioHandle.*;

public class Main {
    public static void main(String[] args) throws MyException, IOException {
        System.out.print("Input name of data file :");
        String fileName = getString();

        double table[][] = inputTable(fileName);
        double addedTable[][] = inputAddedTable(fileName);
        double rootTable[][] = inputRootTable(fileName);

        System.out.println("Input polynomial pow and argument value");
        int pow = ioHandle.ioHandle.getInt();
        double argValue = ioHandle.ioHandle.getDouble();

        double value1 = getValue(table, pow, argValue);
        double value2 = getValue(addedTable, pow, argValue);
        double value3 = getValue(rootTable, pow, 0);

        System.out.println("Aproximated value (Newton) : " + value1);
        System.out.println("Aproximated value (Hermite) : " + value2);
        System.out.println("Root : " + value3);
    }
}
