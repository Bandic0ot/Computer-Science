package com.mam558.abstractfactory;

public class AbstractFactory {
    public static void main(String[] args) {
        Machine OSXInstance = Machine.createMachineInstance("OSX");
        Machine WindowsInstance = Machine.createMachineInstance("Windows");

        System.out.println(OSXInstance.instance());
        System.out.println(OSXInstance.database() + "\n");

        System.out.println(WindowsInstance.instance());
        System.out.println(WindowsInstance.database());
    }
}
