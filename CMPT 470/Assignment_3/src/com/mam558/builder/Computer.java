package com.mam558.builder;

public class Computer {
    private String CPU;
    private String GPU;
    private String RAM;
    private String storage;

    public void setCPU(String name, String price) {
        this.CPU = name + " " + price;
    }
    public void setGPU(String name, String price) {
        this.GPU = name + " " + price;
    }
    public void setRAM(String name, String price) {
        this.RAM = name + " " + price;
    }
    public void setStorage(String name, String price) {
        this.storage = name + " " + price;
    }

    public void printSpec() {
        System.out.println(this.CPU);
        System.out.println(this.GPU);
        System.out.println(this.RAM);
        System.out.println(this.storage + "\n");
    }
}
