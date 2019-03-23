import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;
import akka.event.Logging;
import akka.event.LoggingAdapter;

public class Client extends AbstractActor {
    private int[] values;
    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);

    public Client(int[] v) {
        this.values = v;
    }

    static public Props props(int[] v) {
        return Props.create(Client.class, () -> new Client(v));
    }


    @Override
    public void preStart(){
        ActorRef filter = getContext().getSystem().actorOf(FilterActor.props());

        for(int i = 0; i < this.values.length; i++) {
            filter.tell(new FilterMessage.Value(values[i]), getSelf());
        }
    }

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(FilterMessage.SmallestValue.class, msg -> {
                    this.sorted(msg);
                })
                .build();
    }

    public void sorted(FilterMessage.SmallestValue msg) {
        log.info("Answer: {} ", msg.i);
    }
}
