package soap;

public class Client {
    public static void main(String args[]) {
        SOAPWebServiceService service = new SOAPWebServiceService();
        SOAPWebService client = service.getSOAPWebServicePort();

        System.out.println(client.readMessages());
    }
}
