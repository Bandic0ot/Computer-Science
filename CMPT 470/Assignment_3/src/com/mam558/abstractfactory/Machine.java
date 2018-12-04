package com.mam558.abstractfactory;

abstract class Machine {
    static Machine createMachineInstance(String os) {
        Machine machine;

        if(os == "Windows") {
            machine = new Windows();
        } else if(os == "OSX") {
            machine = new OSX();
        } else {
            machine = null;
        }

        return machine;
    }

    public abstract String instance();
    public abstract String database();
}



