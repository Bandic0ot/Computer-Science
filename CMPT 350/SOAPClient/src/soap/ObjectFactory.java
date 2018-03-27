
package soap;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the soap package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _ReadMessagesResponse_QNAME = new QName("http://soap.com/", "readMessagesResponse");
    private final static QName _ReadMessages_QNAME = new QName("http://soap.com/", "readMessages");
    private final static QName _AddMessageResponse_QNAME = new QName("http://soap.com/", "addMessageResponse");
    private final static QName _AddMessage_QNAME = new QName("http://soap.com/", "addMessage");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: soap
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link ReadMessagesResponse }
     * 
     */
    public ReadMessagesResponse createReadMessagesResponse() {
        return new ReadMessagesResponse();
    }

    /**
     * Create an instance of {@link ReadMessages }
     * 
     */
    public ReadMessages createReadMessages() {
        return new ReadMessages();
    }

    /**
     * Create an instance of {@link AddMessageResponse }
     * 
     */
    public AddMessageResponse createAddMessageResponse() {
        return new AddMessageResponse();
    }

    /**
     * Create an instance of {@link AddMessage }
     * 
     */
    public AddMessage createAddMessage() {
        return new AddMessage();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ReadMessagesResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://soap.com/", name = "readMessagesResponse")
    public JAXBElement<ReadMessagesResponse> createReadMessagesResponse(ReadMessagesResponse value) {
        return new JAXBElement<ReadMessagesResponse>(_ReadMessagesResponse_QNAME, ReadMessagesResponse.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ReadMessages }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://soap.com/", name = "readMessages")
    public JAXBElement<ReadMessages> createReadMessages(ReadMessages value) {
        return new JAXBElement<ReadMessages>(_ReadMessages_QNAME, ReadMessages.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link AddMessageResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://soap.com/", name = "addMessageResponse")
    public JAXBElement<AddMessageResponse> createAddMessageResponse(AddMessageResponse value) {
        return new JAXBElement<AddMessageResponse>(_AddMessageResponse_QNAME, AddMessageResponse.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link AddMessage }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://soap.com/", name = "addMessage")
    public JAXBElement<AddMessage> createAddMessage(AddMessage value) {
        return new JAXBElement<AddMessage>(_AddMessage_QNAME, AddMessage.class, null, value);
    }

}
