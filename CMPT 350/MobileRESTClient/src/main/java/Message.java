public class Message {
    private String user_id;
    private String msg;
    private String post_time;

    public Message() {
        super();
    }

    public Message(String i, String m, String t) {
        user_id = i;
        msg = m;
        post_time = t;
    }

    public String getId() {
        return user_id;
    }

    public void setId(String id) {
        this.user_id = id;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public String getUser_id() {
        return user_id;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public String getPost_time() {
        return post_time;
    }

    public void setPost_time(String post_time) {
        this.post_time = post_time;
    }
}
