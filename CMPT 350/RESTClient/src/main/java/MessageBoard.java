import org.glassfish.jersey.client.JerseyClientBuilder;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.core.MediaType;
import java.io.*;

@WebServlet(name = "MessageBoard")
public class MessageBoard extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String messages = "";
        Client client = JerseyClientBuilder.createClient();
        MessageList m = client
                .target("http://localhost:8080/RESTServer")
                .path("messages")
                .request(MediaType.APPLICATION_JSON)
                .get(MessageList.class);

        for(Message msg : m.getList()) {
            messages += msg.getMsg() + "<br>" + "\n";
        }

        PrintWriter out = response.getWriter();

        out.println("<html>\n" +
                "<head><title>" + "Message Board" + "</title></head>\n" +
                "<body>\n" +
                messages +
                "<form action=\"NEWMESSAGES\" method=\"GET\">\n" +
                "<input type=\"submit\" value=\"Add Message\">" +
                "</form>\n" +
                "</body> </html>");
    }
}
