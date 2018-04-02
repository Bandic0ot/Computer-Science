import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.Entity;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "PostMessages")
public class PostMessages extends HttpServlet {
    Client client = ClientBuilder.newClient();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        Message m = new Message(0, request.getParameter("message"));

        Response rep = client.target("http://localhost:8080/RESTServer")
                .path("messages")
                .request(MediaType.APPLICATION_JSON)
                .post(Entity.entity(m, MediaType.APPLICATION_JSON));

        System.out.println(rep.getStatus());

        doGet(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        PrintWriter out = response.getWriter();

        out.println("<html>\n" +
                "<head><title>" + "Post Message" + "</title></head>\n" +
                "<body>\n" +
                "<form action=\"postmessage\" method=\"POST\">\n" +
                "New Message:<br>\n" +
                "<input type=\"text\" name=\"message\"><br>\n" +
                "<input type=\"submit\" value=\"Submit\">\n" +
                "</form>\n" +
                "<form action=\"messages\" method=\"GET\">\n" +
                "<input type=\"submit\" value=\"All Messages\">\n" +
                "</form>" +
                "</body> </html>");
    }
}
