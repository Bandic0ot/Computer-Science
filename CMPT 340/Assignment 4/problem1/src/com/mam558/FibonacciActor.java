package com.mam558;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;
import akka.event.Logging;
import akka.event.LoggingAdapter;

public class FibonacciActor extends AbstractActor {
    private int wait, accumulator;
    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);
    private ActorRef parent;

    public FibonacciActor() {
        this.wait = 0;
        this.accumulator = 0;
    }

    static public Props props() {
        return Props.create(FibonacciActor.class, () -> new FibonacciActor());
    }

    public Receive createReceive() {
        return receiveBuilder()
                .match(FibonacciMessage.Fibonacci.class, msg -> {
                    this.fibonacci(msg);
                })
                .match(FibonacciMessage.JobDone.class, msg -> {
                    this.jobDone(msg);
                })
                .build();
    }


    public void fibonacci(FibonacciMessage.Fibonacci msg) {
        this.parent = getSender();

        if (msg.n <= 1) {
            // Send msg to PARENT not to ROOT
            parent.tell(new FibonacciMessage.JobDone(msg.n), getSelf());
        } else {
            ActorRef child1 = getContext().getSystem().actorOf(FibonacciActor.props());
            ActorRef child2 = getContext().getSystem().actorOf(FibonacciActor.props());


            child1.tell(new FibonacciMessage.Fibonacci(msg.n - 1), getSelf());
            child2.tell(new FibonacciMessage.Fibonacci(msg.n - 2), getSelf());

            this.wait = 1;
        }
    }

    public void jobDone(FibonacciMessage.JobDone msg) {
        this.accumulator += msg.n;

        // If we're waiting on to children wait for both children to reply before we
        // send the value off to the parent.
        if(this.wait == 0) {
            parent.tell(new FibonacciMessage.JobDone(this.accumulator), getSelf());
        } else {
            this.wait--;
        }
    }
}
