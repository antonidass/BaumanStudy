package NewtonPolynomial;

import java.math.BigDecimal;
import java.math.RoundingMode;

public class NewtonPolynom {
//    private double x[] = {0.00, 0.15, 0.30, 0.45, 0.60, 0.75, 0.90, 1.05};
//    private double y[] = {1.000000, 0.838771, 0.655336, 0.450447, 0.225336, -0.018310, -0.278390, -0.552430};

      private double x[] = {3, 4, 5, 6, 7, 8, 9};
//      private double y[] = {-4, 1, 0, -1, 0, 1};
      private double y[] = {9, 16, 25, 36, 49, 64, 81};

//    private double yDer[] = {-1.000000, -1.14944, -1.29552, -1.43497, -1.56464, -1.68164, -1.78333, -1.86742};
//    private double x[] = {0, 1, 2 ,3};
//    private double y[] = {0, 0.50, 0.866, 1};
//
//    private double x[] = {0, 0.25, 0.5 ,0.75, 1};
//    private double y[] = {1, 0.924, 0.707, 0.383, 0};

//    private double x[] = {0, 1.00, 2.00 ,3.00, 4.00, 5.00, 6.00};
//    private double y[] = {0.00, 1.00, 4.00, 9.00, 16.00, 25.00, 36.00};

    private int powPolynomial;
    private double argValue;
    private double temp_y[];

    public NewtonPolynom(int powPolynomial, double argValue) {
        this.argValue = argValue;
        this.powPolynomial = powPolynomial;
    }

    private int getIndexOfMiddle() {
        int i;

        if (argValue < x[0])
            return 0;

        for (i = 0; i < x.length - 1; i++) {
            if (x[i] <= argValue && argValue < x[i + 1]) {
                return i;
            }
        }
        return i;
    }

    private double[] fill_temp_y(int indexStart, int indexEnd) {
        double temp[] = new double[indexEnd - indexStart + 1];
        System.out.print("Array temp[y] = ");

        for (int i = 0; i < indexEnd - indexStart + 1; i++) {
            temp[i] = y[indexStart + i];
            System.out.print(temp[i] + " ");
        }

        System.out.println();

        return temp;
    }

    private double roundResult(double value, int precision) {
        BigDecimal result = new BigDecimal(value);
        result.setScale(precision, RoundingMode.HALF_UP);

        return result.doubleValue();
    }


    private int getIndexStart(int indexMiddle) {
        if (indexMiddle - powPolynomial / 2 < 0) {
            return 0;
        }

        if (indexMiddle + powPolynomial / 2 >= y.length) {
            return  y.length - powPolynomial + 1;
        }

        return indexMiddle - powPolynomial / 2;
    }

    private int getIndexEnd(int indexMiddle) {
        int indexStart = getIndexStart(indexMiddle);

        if (indexStart + powPolynomial >= y.length) {
            return y.length - 1;
        }

        if (indexMiddle - powPolynomial / 2 <= 0) {
            return powPolynomial - indexStart;
        }

        return indexStart + powPolynomial;
    }


    public double getFunctionValue() {
        int indexMiddle = getIndexOfMiddle();
        int indexStart = getIndexStart(indexMiddle);
        int indexEnd = getIndexEnd(indexMiddle);

        System.out.println("Middle index " + indexMiddle + " index_start = " + indexStart + " index_end = " + indexEnd);

        double temp_y[] = fill_temp_y(indexStart, indexEnd);
        double funcValue = 0;

        for (int i = 0; i < indexEnd - indexStart; i++) {
            System.out.println("NEW TABLE");
            for (int j = 0; j < indexEnd - indexStart - i; j++) {
                System.out.println("first y = " + temp_y[j + 1] + " second y = " + temp_y[j]);
                System.out.println("first x = " + x[j + 1 + i] + " second x = " + x[j]);
                System.out.println("dif / dif = " + (temp_y[j + 1] - temp_y[j]) / (x[j + 1 + i] - x[j]));

                temp_y[j] = roundResult((temp_y[j + 1] - temp_y[j]) / (x[j + 1 + i] - x[j]), 6);

                System.out.println("RESULT  = " + temp_y[j] + "\n");
             }

            double mult = 1;
            for (int k = 0; k < i + 1; k++) {
                mult *= (argValue - x[indexStart + k]);
            }

            mult = roundResult(mult, 6);
            funcValue += mult * temp_y[0];
            funcValue = roundResult(funcValue, 6);

            System.out.println("mult = " + mult + "\ntemp_y[0] = " + temp_y[0] + "\nfunc valuе =  " + funcValue);
        }

        System.out.println("y0 = " + y[indexStart]);
        return funcValue + y[indexStart];
    }
}