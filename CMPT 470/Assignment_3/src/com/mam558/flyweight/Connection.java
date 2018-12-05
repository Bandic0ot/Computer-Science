package com.mam558.flyweight;

public class Connection {
    private String ip; // Extrinsic State
    private int secretNumber; // Intrinsic State

    public Connection(String c) {
        this.ip = c;
    }

    public void read() {
        System.out.println(this.ip + " read from the server.");
    }

    public void write(int i) {
        System.out.println(this.ip + " wrote to the server.");
        this.secretNumber = i;
    }

    public int getSecretNumber() {
        return this.secretNumber;
    }
}
