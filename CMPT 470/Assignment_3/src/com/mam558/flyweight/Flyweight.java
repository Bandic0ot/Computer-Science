package com.mam558.flyweight;

public class Flyweight {
    public static void main(String[] args) {
        // The server acts as a factory for connections, anytime an
        // ip already exists the server just returns the associated connection
        Server server = new Server();

        Connection client1 = server.createConnection("172.0.0.1");
        Connection client2 = server.createConnection("172.0.0.2");

        client1.read();
        client1.write(1);
        System.out.println("Client1's secret number is " + client1.getSecretNumber() + "\n");

        client2.read();
        client2.write(2);
        System.out.println("Client2's secret number is " + client2.getSecretNumber() + "\n");

        // Notice that we don't write client3's secret number yet it
        // is the same as client1's
        Connection client3 = server.createConnection("172.0.0.1");
        System.out.println("Client1's secret number is " + client1.getSecretNumber());
        System.out.println("Client3's secret number is " + client3.getSecretNumber() + "\n");

        client3.write(5);
        System.out.println("Client1's secret number is " + client1.getSecretNumber());
        System.out.println("Client3's secret number is " + client3.getSecretNumber() + "\n");
    }
}
