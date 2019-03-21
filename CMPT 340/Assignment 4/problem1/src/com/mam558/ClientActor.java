package com.mam558;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;
import akka.event.Logging;
import akka.event.LoggingAdapter;

public class ClientActor extends AbstractActor {
    private int n;
    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);

    public ClientActor(int n) {
        this.n = n;
    }

    static public Props props(int n) {
        return Props.create(ClientActor.class, () -> new ClientActor(n));
    }

    public void preStart(){
        ActorRef fibActor = getContext().getSystem().actorOf(FibonacciActor.props());
        fibActor.tell(new FibonacciMessage.Result(n), self());
    }

    public Receive createReceive() {
        return receiveBuilder()
                .match(FibonacciMessage.FinalResult.class, msg -> {
                    this.answer(msg);
                })
                .build();
    }

    public void answer(FibonacciMessage.FinalResult msg) {
        log.info("Answer: {} ", msg.n);
    }
}
