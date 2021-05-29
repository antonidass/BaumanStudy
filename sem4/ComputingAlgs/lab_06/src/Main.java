public class Main {
    private static Double[] X = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    private static Double[] Y = {0.571, 0.889, 1.091, 1.231, 1.333, 1.412};
    private static Double[][] table = {
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
    };


    private static Double leftSide(Double[] y, Double step, int i) {
        if (i > 0) {
            return (y[i] - y[i - 1]) / step;
        }
        return null;
    }

    private static Double rightSide(Double[] y, Double step, int i) {
        if (i < y.length - 1) {
            return (Y[i + 1] - Y[i]) / step;
        }
        return null;
    }

    private static Double centerSide(Double[] y, Double step, int i) {
        if (i > 0 && i < y.length - 1) {
            return (y[i + 1] - y[i - 1]) / 2 / step;
        }
        return null;
    }

    private static Double secondDiff(Double[] y, Double step, int i) {
        if (i > 0 && i < y.length - 1) {
            return (y[i - 1] - 2 * y[i] + y[i + 1]) / (step * step);
        }
        return null;
    }

    private static Double rungeDiff(Double[] y, Double step, int i) {
        if (i >= 2) {
            Double F1 = leftSide(y, step, i);
            Double F2 = (y[i] - y[i - 2]) / (2 * step);

            return F1 + F1 - F2;
        }
        return null;
    }

    private static Double alignVarsDiff(Double[] y, Double[] x, int i) {
        if (i <= y.length - 2) {
            Double etaKsiDiff = (1 / y[i + 1] - 1 / y[i]) / (1 / x[i + 1] - 1 / x[i]);
            Double Y = y[i];
            Double X = x[i];
            return etaKsiDiff * Y * Y / X / X;
        }
        return null;
    }


    public static void main(String[] args) {
        System.out.println(" X          Y        Left side    Center Side    RungeDiff      AlignVarsDiff      SecondDiff");

        for (int i = 0; i < X.length; i++) {
            System.out.print(X[i] + "   |   " + Y[i] + "   |   ");
            Double res = leftSide(Y, X[1] - X[0], i);
            if (res != null) {
                System.out.printf(" %.3f    |  ", res);
            } else {
                System.out.printf(" -----    |  ");
            }
            res = centerSide(Y, X[1] - X[0], i);
            if (res != null) {
                System.out.printf("  %.3f     | ", res);
            } else {
                System.out.printf("  -----     | ");
            }
            res = rungeDiff(Y, X[1] - X[0], i);
            if (res != null) {
                System.out.printf("   %.3f     | ", res);
            } else {
                System.out.printf("   -----     | ");
            }
            res = alignVarsDiff(Y, X, i);
            if (res != null) {
                System.out.printf("    %.3f       | ", res);
            } else {
                System.out.printf("    -----       | ");
            }
            res = secondDiff(Y,X[1] - X[0], i);
            if (res != null) {
                System.out.printf("   %.3f      ", res);
            } else {
                System.out.printf("    -----      ");
            }
            System.out.println();
        }
    }
}
