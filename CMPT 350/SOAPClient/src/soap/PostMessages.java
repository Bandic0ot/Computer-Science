package soap;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "PostMessages")
public class PostMessages extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        SOAPWebServiceService service = new SOAPWebServiceService();
        SOAPWebService client = service.getSOAPWebServicePort();

        client.addMessage(request.getParameter("message"));

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
