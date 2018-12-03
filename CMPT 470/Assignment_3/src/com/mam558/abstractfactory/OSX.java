package com.mam558.abstractfactory;

public class OSX extends AbstractFactory{
    @Override
    public String instance() {
        return "OSX";
    }

    @Override
    public String greeting() {
        return "Welcome to OSX!";
    }
}
