package com.mam558.interpreter;

public class Interpreter {


    public static StringInterpreter join() {
        StringInterpreter first = new Expression("dog");
        StringInterpreter second = new Expression("cat");

        return new AppendOperation(first, second);
    }

    public static void main(String[] args) {
        StringInterpreter joinStrings = join();
        System.out.println(joinStrings.interpret());
    }
}
