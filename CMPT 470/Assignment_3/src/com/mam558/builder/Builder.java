package com.mam558.builder;

// This class also acts as the director, selecting which computer to build
// from different the different builder methods.
public class Builder {
    public static void main(String[] args) {
        ComputerBuilder builder = new ComputerBuilder();

        Computer lowSpec = builder.buildLowSpecComputer();
        Computer medSpec = builder.buildMedSpecComputer();
        Computer highSpec = builder.buildHighSpecComputer();

        lowSpec.printSpec();
        medSpec.printSpec();
        highSpec.printSpec();
    }
}
