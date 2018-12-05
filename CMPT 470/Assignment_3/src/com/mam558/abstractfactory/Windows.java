package com.mam558.abstractfactory;

public class Windows extends Machine {
    @Override
    public String instance() {
        return "Windows";
    }

    @Override
    public String database() {
        return "This is a MySQL database.";
    }
}
