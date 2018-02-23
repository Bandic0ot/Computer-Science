import sun.jvm.hotspot.HelloWorld;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "NEWMESSAGES")
public class NEWMESSAGES extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        String title = "New Messages";

        PrintWriter out = response.getWriter();

        out.println("<html>\n" +
                "<head><title>" + title + "</title></head>\n" +
                "<body>\n" +
                "<form action=\"ALLMESSAGES\" method=\"POST\">\n" +
                "New Message:<br>\n" +
                "<input type=\"text\" name=\"message\"><br>\n" +
                "<input type=\"submit\" value=\"Submit\">\n" +
                "</form>\n" +
                "</body> </html>" );
    }
}
