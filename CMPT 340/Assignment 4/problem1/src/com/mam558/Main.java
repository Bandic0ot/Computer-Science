package com.mam558;

/* public int fibonacci(int n)  {
    if(n == 0)
        return 0;
    else if(n == 1)
      return 1;
   else
      return fibonacci(n - 1) + fibonacci(n - 2);
}
*/

import akka.actor.ActorRef;
import akka.actor.ActorSystem;

public class Main {

    public static void main(String[] args) {

        // Read in command line arguments
        final int fibonacciGoal = 7;

        System.out.println("Finding Fibonacci Number: " + fibonacciGoal);

        final ActorSystem system = ActorSystem.create("fibonacci");
        final ActorRef client = system.actorOf(ClientActor.props(fibonacciGoal), "client");
    }
}
