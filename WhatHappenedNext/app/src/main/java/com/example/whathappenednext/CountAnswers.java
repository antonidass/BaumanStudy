package com.example.whathappenednext;

public class CountAnswers {
    private static int LehaCount = 0;
    private static int NurlanCount = 0;
    private static int TambiCount = 0;
    private static int RustamCount = 0;


    public static String answers[][] = new String[][] {
            {"В общем", "В целом", "В общем и целом", "в"},
            {"пару килограмм бы не помешало", "у казахов всегда все хорошо", "ой бой", "мармелад"}
    };


    public static void incLeha() {
        LehaCount++;
    }

    public static void incTambi() {
        TambiCount++;
    }

    public static void incNurlan() {
        NurlanCount++;
    }

    public static void incRustam() {
        RustamCount++;
    }

    public static String getResult() {
        int ans = Math.max(Math.max(LehaCount, NurlanCount), Math.max(TambiCount, RustamCount));

        System.out.println("ans = " + ans + "leha = " + LehaCount + "rustam  =" + RustamCount);
        if (ans == LehaCount) {
            return "Leha";
        }
        else if (ans == NurlanCount) {
            return "Nurlan";
        }
        else if (ans == TambiCount) {
            return "Tambi";
        }
        else if (ans == RustamCount) {
            return "Rustam";
        }

        return "";
    }
}
