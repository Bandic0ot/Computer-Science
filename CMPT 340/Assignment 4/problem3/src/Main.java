import akka.actor.ActorRef;
import akka.actor.ActorSystem;

public class Main {

    public static void main(String[] args) {
        int[] values = {7, 3, 0};

        final ActorSystem system = ActorSystem.create("Sort");
        final ActorRef client = system.actorOf(Client.props(values), "Client");
    }
}