package com.mam558.builder;

public class ComputerBuilder {
    public Computer buildLowSpecComputer() {
        Computer computer = new Computer();

        computer.setCPU("Intel i3","$");
        computer.setGPU("Nvidia GTX 1050", "$");
        computer.setRAM("Corsair 4GB", "$");
        computer.setStorage("Seagate HDD 500GB", "$");

        return computer;
    }

    public Computer buildMedSpecComputer() {
        Computer computer = new Computer();

        computer.setCPU("Intel i5","$$");
        computer.setGPU("Nvidia GTX 1070", "$$");
        computer.setRAM("Corsair 8GB", "$$");
        computer.setStorage("Seagate HDD 1TB", "$$");

        return computer;
    }

    public Computer buildHighSpecComputer() {
        Computer computer = new Computer();

        computer.setCPU("AMD Ryzen 7","$$$");
        computer.setGPU("Nvidia GTX 2080 Ti", "$$$");
        computer.setRAM("Corsair 32GB", "$$$");
        computer.setStorage("Samsung SSD 1TB", "$$$");

        return computer;
    }
}
