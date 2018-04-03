package server;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import java.sql.ResultSet;
import java.sql.SQLException;

@Path("/ids")
public class MessageIDs {
    private DatabaseInteface database;

    public MessageIDs() {
        database = new DatabaseInteface();
    }

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public MessageList getMessageIDs() {
        ResultSet messageSet;
        MessageList mList = new MessageList();
        messageSet = database.select("user_id FROM messages");

        try {
            while(messageSet.next()) {
                boolean foundMatch = false;

                if(mList.getList().size() == 0) {
                    mList.getList().add(new Message(messageSet.getString("user_id"), null, null));
                } else {
                    for(Message m : mList.getList()) {
                        if(m.getId().equals(messageSet.getString("user_id"))) {
                            foundMatch = true;
                        }
                    }

                    if(!foundMatch) {
                        mList.getList().add(new Message(messageSet.getString("user_id"), null, null));
                    }
                }
            }
        } catch(SQLException e) {
            e.printStackTrace();
        }

        return mList;
    }

    @Path("/with/{id}")
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public MessageList getMessagesWithID(@PathParam("id") String id) {
        ResultSet messageSet;
        MessageList mList = new MessageList();
        messageSet = database.select("* FROM messages WHERE user_id = '" + id + "';");

        try {
            while(messageSet.next()) {
                mList.getList().add(new Message(messageSet.getString("user_id"),
                        messageSet.getString("message"),
                        messageSet.getTimestamp("post_time").toLocalDateTime().toString()));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return mList;
    }

    @Path("/without/{id}")
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public MessageList getMessagesWithoutID(@PathParam("id") String id) {
        ResultSet messageSet;
        MessageList mList = new MessageList();
        messageSet = database.select("* FROM messages WHERE user_id != '" + id + "';");

        try {
            while(messageSet.next()) {
                mList.getList().add(new Message(messageSet.getString("user_id"),
                        messageSet.getString("message"),
                        messageSet.getTimestamp("post_time").toLocalDateTime().toString()));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return mList;
    }

    public static void main(String args[]) {
        MessageIDs m = new MessageIDs();

        for(Message s : m.getMessagesWithoutID("test1").getList()) {
            System.out.println(s.getId() + " " + s.getMsg() + " " + s.getPost_time());
        }
    }
}
