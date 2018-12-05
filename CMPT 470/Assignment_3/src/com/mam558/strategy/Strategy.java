package com.mam558.strategy;

public class Strategy {
    public static void main(String[] args) {
        Pet dog = new Pet(new Dog());
        Pet cat = new Pet(new Cat());

        // Both pets use the generic pet functions.
        dog.eat();
        cat.sleep();

        // When a sound is made however, the Pet class dynamically
        // assigns the correct sound at runtime.
        dog.sound();
        cat.sound();
    }
}
