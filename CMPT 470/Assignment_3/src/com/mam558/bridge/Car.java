package com.mam558.bridge;

public class Car {
    private CarInterface carInterface;

    public Car(CarInterface i) {
        this.carInterface = i;
    }

    public void engine() {
        carInterface.engine();
    }
    public void accelerate() {
        System.out.println("The car is accelerating.");
    }

    public void brake() {
        System.out.println("The car is braking.");
    }
}
