package main

import (
	"fmt"
	"os"
	"strconv"
	"bufio"
	"regexp"
	"crypto/tls"
	"net"
	"net/url"
	"io"
	"strings"
)

func crawl(inputURL string, depth int) {
	var links []string
	protocol := regexp.MustCompile("https?").FindStringSubmatch(inputURL)

	if strings.Compare(protocol[0], "https") == 0 {
		links = secureRequest(inputURL)
	} else {
		links = insecureRequest(inputURL)
	}

	if depth > 0 {
		for i := range links {
			// Skip .dtd links
			if strings.HasSuffix(links[i], ".dtd") {
				i++
			}

			crawl(links[i], depth - 1)
		}
	} else {
		fmt.Println("\n------- " + inputURL + " -------")

		for i := range links {
			fmt.Println(links[i])
		}
	}
}

// Takes an https URL and returns the response body.
func secureRequest(inputURL string) []string {
	urlPath := ""
	parsedURL, err := url.Parse(inputURL)
	if err != nil {
		fmt.Println("URL Parsing Error: " + err.Error())
	} else {
		// Check to see if it's a raw path, whatever that means...
		if strings.Compare(parsedURL.RawPath, "") == 0 {
			urlPath = parsedURL.Path
		} else {
			urlPath = parsedURL.RawPath
		}
	}

	// Establish a connection with the server.
	if conn, err := tls.Dial("tcp", convertURL(inputURL), &tls.Config{InsecureSkipVerify: true,}); err == nil {
		defer conn.Close()

		fmt.Fprintf(conn, "GET /" + strings.TrimPrefix(urlPath, "/") + " HTTP/1.1\r\n")
		fmt.Fprintf(conn, "Host: " + parsedURL.Hostname() + "\r\n")
		fmt.Fprintf(conn, "Connection: close\r\n")
		fmt.Fprintf(conn, "Accept: text/html\r\n")
		fmt.Fprintf(conn, "\r\n\r\n")

		return parseBody(conn)
	} else {
		fmt.Println("TLS Connection Error: " + err.Error())

		return nil
	}
}

// Takes an http URL and returns the response body.
func insecureRequest(inputURL string) []string {
	urlPath := ""
	parsedURL, err := url.Parse(inputURL)
	if err != nil {
		fmt.Println("URL Parsing Error: " + err.Error())
	} else {
		// Check to see if it's a raw path, whatever that means...
		if strings.Compare(parsedURL.RawPath, "") == 0 {
			urlPath = parsedURL.Path
		} else {
			urlPath = parsedURL.RawPath
		}
	}

	// Establish a connection with the server.
	if conn, err := net.Dial("tcp", convertURL(inputURL)); err == nil {
		defer conn.Close()

		fmt.Fprintf(conn, "GET /" + strings.TrimPrefix(urlPath, "/") + " HTTP/1.1\r\n")
		fmt.Fprintf(conn, "Host: " + parsedURL.Hostname() + "\r\n")
		fmt.Fprintf(conn, "Connection: close\r\n")
		fmt.Fprintf(conn, "Accept: text/html\r\n")
		fmt.Fprintf(conn, "\r\n\r\n")

		return parseBody(conn)
	} else {
		fmt.Println("Standard Connection Error: " + err.Error())

		return nil
	}
}

// Parse the contents of the response body returning all the links found within.
func parseBody(connection io.Reader) []string {
	var links []string
	reader := bufio.NewReader(connection)
	exp := regexp.MustCompile("(?:http(s)?)://([^/\r\n\"')>]+)(/[^\r\n\"')>]*)?")

	for {
		if line, _, err := reader.ReadLine(); err != io.EOF {
			if str := exp.FindAllString(string(line), -1); str != nil {
				for i := range str {
					links = append(links, str[i])
				}
			}
		} else {
			break
		}
	}

	return links
}

// Convert the given url to a format that the dial function can use.
func convertURL(inputURL string) string {
	// Check to see whether the link is http or https and store the result.
	protocol := regexp.MustCompile("https?").FindStringSubmatch(inputURL)

	// Creates two main groups, the first of which is non-capturing. When accessing the returned
	// slice it is the second element ie. index [1] we want.
	if str, err := url.Parse(inputURL); err != nil {
		fmt.Println("URL Conversion Error: " + err.Error())
		return ""
	} else {
		// Attach all the pieces together to get a valid url for the Dial function.
		return net.JoinHostPort(str.Hostname(), protocol[0])
	}
}

func main() {
	var inputURL string
	var depth int

	// Check to see if the first argument is a valid URL
	if arg := regexp.MustCompile("(https?)://([^/\r\n\"'>)]+)(/[^\r\n\"')>]*)?"); arg.MatchString(os.Args[1]) {
		inputURL = os.Args[1]
	} else {
		fmt.Println("Please enter a valid URL. \neg. https://www.google.com")
		return
	}

	// Convert and check to see if the second argument is a valid integer.
	if arg, err := strconv.Atoi(os.Args[2]); err == nil {
		depth = arg
	} else {
		fmt.Println("Please enter a valid integer. \nError: " + err.Error())
		return
	}

	crawl(inputURL, depth)
}
