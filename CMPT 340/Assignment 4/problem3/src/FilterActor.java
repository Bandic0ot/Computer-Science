import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;

public class FilterActor extends AbstractActor {
    private int incoming, smallest;
    private ActorRef parent, child;

    static public Props props() {
        return Props.create(FilterActor.class, () -> new FilterActor());
    }

    public FilterActor() {
    }

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(FilterMessage.Value.class, msg -> {
                    this.receiveValue(msg);
                })
                .match(FilterMessage.SmallestValue.class, msg -> {
                    this.smallestValue(msg);
                })
                .build();
    }

    public void receiveValue(FilterMessage.Value msg) {
        this.parent = getSender();
        this.incoming = msg.i;

        if(this.incoming == 0) {
            parent.tell(new FilterMessage.SmallestValue(this.smallest), getSelf());

            if(child != null) {
                child.tell(new FilterMessage.Value(this.incoming), getSelf());
            }
        } else {
            if(child == null) {
                child = this.getContext().getSystem().actorOf(FilterActor.props());
            }
            // If the value received is not the sentinel either pass it down or
            // keep it.

            // Check to see if this is the first time being initialized, if it is
            // or if the value being received is smaller, pass
            if (this.smallest == 0) {
                this.smallest = this.incoming;
            } else if (this.smallest > this.incoming) {
                child.tell(new FilterMessage.Value(this.smallest), getSelf());
                this.smallest = this.incoming;
            } else {
                child.tell(new FilterMessage.Value(this.incoming), getSelf());
            }
        }
    }

    public void smallestValue(FilterMessage.SmallestValue msg) {
        parent.forward(new FilterMessage.SmallestValue(msg.i), this.getContext());
    }
}
