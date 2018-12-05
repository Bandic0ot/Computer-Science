package com.mam558.strategy;

public class Pet {
    private Animal animal;

    public Pet(Animal a) {
        this.animal = a;
    }

    public void sound() {
        this.animal.makeSound();
    }

    public void eat() {
        System.out.println("The pet is eating.");
    }

    public void sleep() {
        System.out.println("The pet is sleeping.");
    }
}
