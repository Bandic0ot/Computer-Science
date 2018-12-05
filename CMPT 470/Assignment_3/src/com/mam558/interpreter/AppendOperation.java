package com.mam558.interpreter;

public class AppendOperation implements StringInterpreter {
    protected StringInterpreter expr1;
    protected StringInterpreter expr2;

    public AppendOperation(StringInterpreter a, StringInterpreter b) {
        this.expr1 = a;
        this.expr2 = b;
    }

    @Override
    public String interpret() {
        return expr1.interpret().concat(expr2.interpret());
    }
}
