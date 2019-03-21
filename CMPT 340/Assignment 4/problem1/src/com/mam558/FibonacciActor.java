package com.mam558;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;
import akka.event.Logging;
import akka.event.LoggingAdapter;

public class FibonacciActor extends AbstractActor {
    private int n, sub1, sub2;
    private ActorRef parent;
    private ActorRef[] workers;

    public FibonacciActor() {

    }

    static public Props props() {
        return Props.create(FibonacciActor.class, () -> new FibonacciActor());
    }

    public Receive createReceive() {
        return receiveBuilder()
                .match(FibonacciMessage.Result.class, msg -> {
                    this.result(msg);
                })
                .match(FibonacciMessage.FinalResult.class, msg -> {
                    this.finalResult(msg);
                })
                .match(FibonacciMessage.FirstResult.class, msg -> {
                    this.firstResult(msg);
                })
                .match(FibonacciMessage.SecondResult.class, msg -> {
                    this.secondResult(msg);
                })
                .build();
    }

    public void firstResult(FibonacciMessage.FirstResult msg) {
        this.sub1 = msg.n;
    }

    public void secondResult(FibonacciMessage.SecondResult msg) {
        this.sub2 = msg.n;
    }

    public void result(FibonacciMessage.Result msg) {
        this.parent = getSender();

        if (msg.n == 0) {
            parent.tell(new FibonacciMessage.FinalResult(0), getSelf());
        } else if (msg.n == 1) {
            parent.tell(new FibonacciMessage.FinalResult(1), getSelf());
        } else {
            for(int i = 0; i < 2; i++) {
                workers[i] = getContext().getSystem().actorOf(FibonacciActor.props());
            }

            workers[0].tell(new FibonacciMessage.FirstResult(msg.n - 1), self());
            workers[1].tell(new FibonacciMessage.SecondResult(msg.n - 2), self());

            parent.tell(new FibonacciMessage.FinalResult(this.sub1 + this.sub2), self());
        }
    }

    public void finalResult(FibonacciMessage.FinalResult msg) {
        this.parent.forward(msg, this.getContext());
    }

}
