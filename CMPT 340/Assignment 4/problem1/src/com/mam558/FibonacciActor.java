package com.mam558;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;
import akka.event.Logging;
import akka.event.LoggingAdapter;

public class FibonacciActor extends AbstractActor {
    private int count, accumulator;
    private ActorRef parent;
    private ActorRef[] workers;

    public FibonacciActor() {
        this.count = 0;
        this.workers = new ActorRef[2];
        this.accumulator = 0;
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
                    this.FinalResult(msg);
                })
                .build();
    }


    public void result(FibonacciMessage.Result msg) {
        this.parent = getSender();

        if (msg.n == 0) {
            parent.tell(new FibonacciMessage.FinalResult(0), getSelf());
        } else if (msg.n == 1) {
            parent.tell(new FibonacciMessage.FinalResult(1), getSelf());
        } else {
            for(int i = 0; i < 2; i++) {
                this.workers[i] = getContext().getSystem().actorOf(FibonacciActor.props());
            }

            workers[0].tell(new FibonacciMessage.Result(msg.n - 1), getSelf());
            workers[1].tell(new FibonacciMessage.Result(msg.n - 2), getSelf());
        }
    }

    public void FinalResult(FibonacciMessage.FinalResult msg) {
        if(this.count == 0) {
            this.accumulator += msg.n;
            this.count++;
        } else {
            parent.forward(new FibonacciMessage.FinalResult(accumulator), getContext());
        }
    }
}
