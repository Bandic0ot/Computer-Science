package server;

import javax.ws.rs.*;
import javax.ws.rs.core.*;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;

@Path("/messages")
public class RESTWebService {
  private DatabaseInteface database;

  public RESTWebService() {
    database = new DatabaseInteface();
  }

  @POST
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addMessage(Message message) {
    if(message.getId() == null) {
      database.insert("messages (message, post_time)\n " +
              "VALUES ('" + message.getMsg() + "', current_timestamp);");
    } else {
      database.insert("messages (id, message, post_time)\n" +
              "VALUES (" + message.getId() + ", '" + message.getMsg() + "', current_timestamp);");
    }

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
        mList.getList().add(new Message(messageSet.getString("user_id"),
                messageSet.getString("message"),
                messageSet.getTimestamp("post_time").toLocalDateTime().toString()));
      }

      return mList;
    } catch (SQLException exception) {
      exception.printStackTrace();

      return mList;
    }
  }

  @Path("/recent")
  @GET
  @Produces(MediaType.APPLICATION_JSON)
  public MessageList recentMessages(@Context Request r) {
    ResultSet messageSet;
    Response.ResponseBuilder response = null;
    MessageList mList = new MessageList();
    CacheControl cache = new CacheControl();
    EntityTag etag = new EntityTag(Integer.toString(LocalDateTime.now().toString().hashCode()));

    cache.setMaxAge(86400);

    response = r.evaluatePreconditions(etag);

    if(response != null) {
      return response.cacheControl(cache).build().getEntity();
    }

    messageSet = database.select("* FROM messages WHERE");

    return mList;
  }

  public static void main(String args[]) {
    RESTWebService s = new RESTWebService();

    for(Message m : s.readMessages().getList()) {
      System.out.println(m.getPost_time());
    }
  }
}
