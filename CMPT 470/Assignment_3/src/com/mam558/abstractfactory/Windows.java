package com.mam558.abstractfactory;

public class Windows extends AbstractFactory {

    @Override
    public String instance() {
        return "Windows";
    }

    @Override
    public String greeting() {
        return "Welcome to Windows!";
    }
}
