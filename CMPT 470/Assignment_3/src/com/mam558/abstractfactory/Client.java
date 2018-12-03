package com.mam558.abstractfactory;

public class Client {
    public static void main(String[] args) {
        AbstractFactory OSXFactory = AbstractFactory.createFactory("OSX");
        AbstractFactory WindowsFactory = AbstractFactory.createFactory("Windows");

        System.out.println(OSXFactory.instance());
        System.out.println(OSXFactory.greeting() + "\n");

        System.out.println(WindowsFactory.instance());
        System.out.println(WindowsFactory.greeting());
    }
}
