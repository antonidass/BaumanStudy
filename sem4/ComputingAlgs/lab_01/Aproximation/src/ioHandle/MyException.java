package ioHandle;

public class MyException extends Exception {
    private String detail;

    public MyException(String detail) {
        this.detail = detail;
    }

    @Override
    public String toString() {
        return detail;
    }

    public static void printA() {
        System.out.println("a");
    }

    @Override
    public synchronized Throwable fillInStackTrace() {
        return this;
    }
}
