import HermitePolynomial.HermitePolynomial;
import NewtonPolynomial.NewtonPolynom;
import ioHandle.MyException;

import java.io.IOException;


public class Main {

    public static void main(String[] args) throws MyException, IOException {
        System.out.println("Choose aproximaition method : \n" +
                           "1 - Newton Polynomial\n" +
                           "2 - Hermite Polynomial\n");
        int choice = ioHandle.ioHandle.getInt();

        System.out.println("Input polynomial pow and argument value");
        int pow = ioHandle.ioHandle.getInt();
        double argValue = ioHandle.ioHandle.getDouble();


        if (choice == 1) {
            NewtonPolynom newtonPolynom = new NewtonPolynom(pow, argValue);
            double function_value = newtonPolynom.getFunctionValue();
            System.out.println("Aproximated value = " + function_value);
        }
        else if (choice == 2) {
            HermitePolynomial hermitePolynomial = new HermitePolynomial(pow, argValue);
            double functionValue = hermitePolynomial.getFunctionValue();
            System.out.println("Aproximated value = "+  functionValue);
        }
    }
}
