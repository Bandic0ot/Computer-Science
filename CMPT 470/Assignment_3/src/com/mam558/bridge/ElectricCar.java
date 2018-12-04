package com.mam558.bridge;

public class ElectricCar implements CarInterface {
    @Override
    public void engine() {
        System.out.println("The car is driving using an electric engine.");
    }
}
