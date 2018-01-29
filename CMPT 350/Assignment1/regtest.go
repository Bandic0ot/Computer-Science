package main

import (
	"fmt"
	"crypto/tls"
	"bufio"
	"io"
	"strings"
	"regexp"
)

func main () {
	if conn, err := tls.Dial("tcp", "www.google-analytics.com:https", &tls.Config{}); err == nil  {
		fmt.Fprintf(conn, "GET /analytics HTTP/1.1\r\n")
		fmt.Fprintf(conn, "Host: www.google-analytics.com\r\n")
		fmt.Fprintf(conn, "Connection: close\r\n")
		fmt.Fprintf(conn, "Accept: text/html\r\n")
		fmt.Fprintf(conn, "\r\n\r\n")

		reader := bufio.NewReader(conn)
		exp := regexp.MustCompile("(?:http(s)?)://([^/\r\n\"]+)(/[^\r\n\"]*)?")

		for {
			if line, _, err := reader.ReadLine(); err != io.EOF {
				if str := exp.FindAllStringSubmatch(string(line), -1); str != nil {
					for i := range str {
						fmt.Println(strings.TrimSuffix(str[i][0], "/"))
					}
				}


				//fmt.Println(string(line))
			} else {
				break
			}
		}



		//if err := data.Err(); err != nil {
		//	fmt.Fprintln(os.Stderr, "reading standard input:", err)
		//}

		conn.Close()
	} else {
		fmt.Println(err.Error())
		return
	}


}
