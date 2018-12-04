package com.mam558.bridge;

public class GasCar implements CarInterface {
    @Override
    public void engine() {
        System.out.println("The car is driving using a combustion engine.");
    }
}
