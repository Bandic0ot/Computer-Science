package com.soap;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.xml.ws.Endpoint;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.LinkedList;


@WebService()
public class SOAPWebService {
  private DatabaseInteface database;
  public SOAPWebService() {
    database = new DatabaseInteface();
  }

  @WebMethod
  public void addMessage(String message) {
    database.insert("messages (message)\n " + "VALUES ('" + message + "');");
  }

  @WebMethod
  public LinkedList<String> readMessages() {
    ResultSet messageSet;
    LinkedList<String> messages = new LinkedList<>();

    messageSet = database.select("* FROM messages");

    try {
      while(messageSet.next()) {
        messages.add(messageSet.getString("message"));
      }

      return messages;
    } catch (SQLException exception) {
      exception.printStackTrace();

      return messages;
    }
  }

  public static void main(String[] argv) {
    SOAPWebService s = new SOAPWebService();

    LinkedList<String> m = s.readMessages();

    for(String msg : m) {
      System.out.println(msg);
    }

    Object implementor = new SOAPWebService();
    String address = "http://localhost:9000/SOAPWebService";
    Endpoint.publish(address, implementor);
  }
}
