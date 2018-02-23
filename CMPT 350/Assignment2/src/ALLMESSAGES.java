import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "ALLMESSAGES")
public class ALLMESSAGES extends HttpServlet {
    protected String messages = "";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        String title = "All Messages";
        messages += request.getParameter("message") + "<br>" + "\n";

        PrintWriter out = response.getWriter();

        out.println("<html>\n" +
                "<head><title>" + title + "</title></head>\n" +
                "<body>\n" +
                messages +
                "<form action=\"NEWMESSAGES\" method=\"GET\">\n" +
                "<input type=\"submit\" value=\"Add Message\">" +
                "</form>\n" +
                "</body> </html>" );
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        String title = "All Messages";

        PrintWriter out = response.getWriter();

        out.println("<html>\n" +
                "<head><title>" + title + "</title></head>\n" +
                "<body>\n" +
                messages +
                "<form action=\"NEWMESSAGES\" method=\"GET\">\n" +
                "<input type=\"submit\" value=\"Add Message\">" +
                "</form>\n" +
                "</body> </html>" );
    }
}
