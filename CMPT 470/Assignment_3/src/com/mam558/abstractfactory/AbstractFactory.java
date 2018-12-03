package com.mam558.abstractfactory;

abstract class AbstractFactory {
    static AbstractFactory createFactory(String os) {
        AbstractFactory factory;

        if(os == "Windows") {
            factory = new Windows();
        } else if(os == "OSX") {
            factory = new OSX();
        } else {
            factory = null;
        }

        return factory;
    }

    // Methods for creating an OS instance appropriate for client's machine
    public abstract String instance();
    public abstract String greeting();
}



