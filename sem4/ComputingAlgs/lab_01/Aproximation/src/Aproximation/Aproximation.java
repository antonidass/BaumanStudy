package Aproximation;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;

public class Aproximation {

    private static int[] getInterval(double table[][], int pow, double argumentValue) {
        int right;

        for (right = 0; right < table.length - 1; right++) {
            if (table[right][0] > argumentValue)
                break;
        }

        int left = right;

        while (right - left < pow) {
            if (left > 0) {
                left--;
            }
            if (right - left >= pow) {
                break;
            }
            if (right < table.length - 1) {
                right++;
            }
        }

        int result[] = {left, right};
        return result;
    }

    private static void addRow(double row[], double table[][], int index_row) {
        for (int i = 0; i < row.length; i++) {
            table[index_row][i] = row[i];
        }
    }

    private static void initTables(double diffTable[][], double derTable[], double table[][], int left, int right) {
        for (int i = left, j = 0; i < right + 1; i++, j++) {
            diffTable[0][j] = table[i][0];
            diffTable[1][j] = table[i][1];
            derTable[j] = table[i][2];
        }
    }

    private static double[][] getDiffTable(double table[][], int left, int right) {
        double diffTable[][] = new double[table.length][table.length];
        double derTable[] = new double[table[2].length];

        initTables(diffTable, derTable, table, left, right);

        int k = 2;

        for (int i = 1; i < right - left + 1; i++) {
            double row[] = new double[table.length];

            for (int j = 0; j < right - left - i + 1; j++) {
                if (diffTable[0][j] - diffTable[0][j + i] == 0) {
                    row[j] = derTable[j];
                } else {
                    row[j] = (diffTable[i][j] - diffTable[i][j + 1]) / (diffTable[0][j] - diffTable[0][j + i]);
                }
            }

            addRow(row, diffTable, k);
            k++;
        }

        return diffTable;
    }

    public static double getValue(double table[][], int pow, double argumentValue) {
        sort(table);
        int interval[] = getInterval(table, pow, argumentValue);
        int left = interval[0], right = interval[1];

        double diffTable[][] = getDiffTable(table, left, right);

        double mult = 1;
        double value = diffTable[1][0];

        for (int i = 2; i < pow + 2; i++) {
            mult *= (argumentValue - diffTable[0][i - 2]);
            value += diffTable[i][0] * mult;
        }

        return value;
    }

    private static void sort(double table[][]) {
        for (int i = 0; i < table.length; i++) {
            for (int j = i + 1; j < table.length; j++) {
                if (table[i][0] > table[j][0]) {
                    double temp[] = table[i];
                    table[i] = table[j];
                    table[j]  = temp;
                }
            }
        }
    }
}
