package main

import (
	"fmt"
	"os"
	"net"
	"strconv"
	"bufio"
	"regexp"
	//"crypto/tls"
)

func crawl(url string, depth int) (string, int) {

	return url, depth
}

func main() {
	var depth int
	url := os.Args[1]

	// Assign the command line arguments to the above variables.
	if arg, err := strconv.Atoi(os.Args[2]); err == nil {
		depth = arg
	} else {
		fmt.Println("Command String Error: " + err.Error(), depth)
	}

	// Establish a connection with the server.
	if conn, err := net.Dial("tcp", url); err == nil {

		fmt.Println("Connection successful...")

		fmt.Fprintf(conn, "GET / HTTP/1.0\r\n")
		fmt.Fprintf(conn, "Accept: text/html\r\n")
		fmt.Fprintf(conn, "\r\n\r\n")

		data := bufio.NewScanner(conn)
		//data.Split(bufio.ScanWords)

		for data.Scan() {
			exp := regexp.MustCompile("(?:http(s)?)://([^/\r\n\"]+)(/[^\r\n\"]*)?")

			if string := exp.FindAllString(data.Text(), -1); string != nil {
				for i := range string {
					fmt.Println(string[i])
				}
			}

			//fmt.Println(data.Text())
		}

		if err := data.Err(); err != nil {
			fmt.Fprintln(os.Stderr, "reading standard input:", err)
		}

		conn.Close()
	} else {
		fmt.Println("Connection Error: " + err.Error())
		conn.Close()
	}
}
