package com.example.accountapp.logic;

import com.example.accountapp.ui.OutputInterface;



public class Account {
    private String name;
    private int number;
    private double balance;

    LogicInterface mLogic;

    public Account() {
        this(null, 0, 0.0);
    }

    public Account(String new_name, int num, double new_balance) {
        this(new_name, num);
        balance = new_balance;
    }

    public Account(String new_name, int num) {
        name = new_name;
        number = num;
    }

    public void displayBalance() {
        System.out.println(number + " " + balance);
    }

    public void deposit(double amt) {
        balance += amt;
    }

    public boolean withdrawal(double sum) {
        if (balance - sum >= 0) {
            balance -= sum;
            return true;
        }

        return false;
    }


    public String getName() {
        return name;
    }

    public int getNumber() {
        return number;
    }

    public double getBalance() {
        return balance;
    }

    public void setName(String new_name) {
        name = new_name;
    }

    public void setNumber(int new_number) {
        number = new_number;
    }

}
