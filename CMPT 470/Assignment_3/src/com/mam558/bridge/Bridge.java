package com.mam558.bridge;

public class Bridge {
    public static void main(String[] args) {
        Car electric = new Car(new ElectricCar());
        Car gas = new Car(new GasCar());

        electric.engine();
        electric.accelerate();
        electric.brake();

        System.out.print("\n");

        gas.engine();
        gas.accelerate();
        gas.brake();
    }
}
