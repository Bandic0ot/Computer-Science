import java.util.LinkedList;

public class MessageList {
    private LinkedList<Message> list;

    public MessageList() {
        list = new LinkedList<Message>();
    }

    public LinkedList<Message> getList() {
        return list;
    }

    public void setList(LinkedList<Message> list) {
        this.list = list;
    }
}
