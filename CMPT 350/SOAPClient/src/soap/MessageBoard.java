package soap;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "MessageBoard")
public class MessageBoard extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        SOAPWebServiceService service = new SOAPWebServiceService();
        SOAPWebService client = service.getSOAPWebServicePort();
        String messages = "";

        for(String msg : client.readMessages()) {
            messages += msg + "<br>" + "\n";
        }

        PrintWriter out = response.getWriter();

        out.println("<html>\n" +
                "<head><title>" + "Message Board" + "</title></head>\n" +
                "<body>\n" +
                messages +
                "<form action=\"postmessage\" method=\"GET\">\n" +
                "<input type=\"submit\" value=\"Add Message\">" +
                "</form>\n" +
                "</body> </html>");
    }
}
