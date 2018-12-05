package com.mam558.interpreter;

public class Expression implements StringInterpreter {
    private String symbol;

    public Expression(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String interpret() {
        return this.symbol;
    }
}
