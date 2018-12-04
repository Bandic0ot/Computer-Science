package com.mam558.abstractfactory;

public class OSX extends Machine {
    @Override
    public String instance() {
        return "OSX";
    }

    @Override
    public String database() {
        return "This is a Postgres database.";
    }
}
