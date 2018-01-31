package main

import (
	"fmt"
	"net"
	"os"
	"bufio"
	"regexp"
	"time"
	"io"
	"io/ioutil"
)

// Starts a local server.
func serve(file string) {
	server, err := net.Listen("tcp", ":8080")
	if err != nil {
		fmt.Println("Error starting server. " + err.Error())
	}

	fmt.Println("Listening...")

	for {
		conn, err := server.Accept()
		if err != nil {
			go respondServerError(conn)
		}

		content, err := ioutil.ReadFile(file + parseGetRequest(readMessage(conn)))

		if err != nil {
			go respondNotFound(conn)
		} else {
			go respondOK(conn, string(content))
		}
	}
}

// Responds to the clients message with content.
func respondOK(conn net.Conn, content string) {
	fmt.Fprintf(conn, "HTTP/1.0 200 OK\r\n")
	fmt.Fprintf(conn, "Content-Type: text/html\r\n")
	fmt.Fprintf(conn, "Connection: close\r\n")
	fmt.Fprintf(conn, "\r\n")

	io.WriteString(conn, string(content))

	conn.Close()
}

// Responds to the clients message with error message.
func respondNotFound(conn net.Conn) {
	fmt.Fprintf(conn, "HTTP/1.0 404 Not Found\r\n")
	fmt.Fprintf(conn, "Content-Type: text/html\r\n")
	fmt.Fprintf(conn, "Connection: close\r\n")
	fmt.Fprintf(conn, "\r\n")

	conn.Close()
}

// Responds to the clients message with error message.
func respondServerError(conn net.Conn) {
	fmt.Fprintf(conn, "HTTP/1.0 500 Internal Server Error\r\n")
	fmt.Fprintf(conn, "Content-Type: text/html\r\n")
	fmt.Fprintf(conn, "Connection: close\r\n")
	fmt.Fprintf(conn, "\r\n")

	conn.Close()
}

// Parses a GET request from a client message.
func parseGetRequest(message string) string {
	expr := regexp.MustCompile(`(?:GET /)([^ \r\n]*)`)
	str := expr.FindStringSubmatch(message)

	return str[1]
}

// Reads the message sent by the client and returns it as a string.
func readMessage(conn net.Conn) string {
	var message string

	for scanner := bufio.NewScanner(conn); scanner.Scan(); {
		conn.SetReadDeadline(time.Now().Add(time.Second))
		message += string(scanner.Text()) + "\n"
	}

	return message
}

func main()  {
	inputDir := os.Args[1]

	serve(inputDir)
}