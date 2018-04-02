package server;

public class Message {
    private int id;
    private String msg;

    public Message() {
        super();
    }

    public Message(int i, String m) {
        id = i;
        msg = m;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }
}
