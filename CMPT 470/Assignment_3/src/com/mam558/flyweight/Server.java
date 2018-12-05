package com.mam558.flyweight;

import java.util.HashMap;

public class Server {
    private HashMap connectionMap = new HashMap<String, Connection>();

    public Connection createConnection(String ip) {
        Connection connection;

        if(connectionMap.containsKey(ip)) {
            connection = (Connection)connectionMap.get(ip);
        } else {
            connection = new Connection(ip);
            connectionMap.put(ip, connection);
        }

        return connection;
    }
}
