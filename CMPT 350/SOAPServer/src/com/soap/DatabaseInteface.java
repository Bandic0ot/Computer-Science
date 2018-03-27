package com.soap;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.*;
import java.util.Properties;

public class DatabaseInteface {
    private Connection dbConnection;
    private Statement dbStatement;

    /**
     * Establishes a connection with the database on success.
     */
    private void connect() {
        Properties dbProperties = new Properties();
        InputStream input = null;

        // Read the dbconfig file for database credentials.
        try {
            input = new FileInputStream("dbconfig.properties");

            dbProperties.load(input);

        } catch(IOException exception) {
            exception.printStackTrace();
        } finally {
            try {
                input.close();
            } catch (IOException exception) {
                exception.printStackTrace();
            }
        }

        // Attempt to establish a connection to the database.
        try {
            dbConnection = DriverManager.getConnection(
                    dbProperties.getProperty("database"),
                    dbProperties.getProperty("username"),
                    dbProperties.getProperty("password"));
        } catch(SQLException exception) {
            System.out.println("Failed to connect to the database.");

            exception.printStackTrace();
        }
    }

    /**
     * Closes a connection to the database.
     */
    private void disconnect() {
        try {
            dbConnection.close();
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
    }

    /**
     * Selects the given query from the database.
     * @param query - A string containing the desired select target.
     * @return result - A ResultSet object containing the query results.
     */
    public ResultSet select(String query) {
        // Connect to the database.
        connect();

        try {
            // Execute the select statement and return the result.
            dbStatement = dbConnection.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);

            return dbStatement.executeQuery("SELECT " + query);
        } catch(SQLException exception) {
            System.out.println("Select query failed.");

            exception.printStackTrace();
            return null;
        } finally {
            if(dbStatement != null) {
                disconnect();
            }
        }
    }

    /**
     * Inserts the given query into the database.
     * @param query - A string containing the desired insert target.
     */
    public void insert(String query) {
        System.out.println(query);
        // Connect to the database.
        connect();

        try {
            // Execute the insert statement.
            dbStatement = dbConnection.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);

            dbStatement.execute("INSERT INTO " + query);
        } catch(SQLException exception) {
            System.out.println("Insert query failed.");

            exception.printStackTrace();
        } finally {
            if(dbStatement != null) {
                disconnect();
            }
        }
    }
}
