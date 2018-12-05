package com.mam558.strategy;

public class Dog implements Animal {
    @Override
    public void makeSound() {
        System.out.println("The dog barked!");
    }
}
