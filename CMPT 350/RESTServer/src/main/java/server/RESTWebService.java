package server;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.sql.ResultSet;
import java.sql.SQLException;

@Path("/messages")
public class RESTWebService {
  private DatabaseInteface database;
  public RESTWebService() {
    database = new DatabaseInteface();
  }

  @POST
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addMessage(Message message) {
    database.insert("messages (message)\n " + "VALUES ('" + message.getMsg() + "');");
    database.insert("messages (message)\n " + "VALUES ('test'));");

    return Response.status(200).build();
  }

  @GET
  @Produces(MediaType.APPLICATION_JSON)
  public MessageList readMessages() {
    ResultSet messageSet;
    MessageList mList = new MessageList();
    messageSet = database.select("* FROM messages");

    try {
      while(messageSet.next()) {
        mList.getList().add(new Message(messageSet.getInt("id"), messageSet.getString("message")));
      }

      return mList;
    } catch (SQLException exception) {
      exception.printStackTrace();

      return mList;
    }
  }

  public static void main(String args[]) {
    DatabaseInteface database = new DatabaseInteface();
    ResultSet messageSet;
    MessageList mList = new MessageList();
    messageSet = database.select("* FROM messages");

    try {
      while (messageSet.next()) {
        mList.getList().add(new Message(messageSet.getInt("id"), messageSet.getString("message")));
      }
    } catch (SQLException e) {
      e.printStackTrace();
    }
  }
}
