package main

import (
	"fmt"
	"regexp"
)

func main ()  {
	string := "</a><footer class=\"uofs-footer\"><div class=\"container-fluid\">" +
			"<ul class=\"list-inline uofs-footer-custom\">" +
			"<li><a href=\"https://www.usask.ca/a-z\">A-Z</a>" +
				"</li><li><a href=\"https://www.usask.ca/search\">Search</a>" +
				"</li><li><a href=\"https://www.usask.ca/maps\">Maps</a></li>" +
					"<li><a href=\"https://jobs.usask.ca\">Jobs</a></li><li>"

	fmt.Println(string)

	result := regexp.MustCompile("(?:http(s)?)://([^/\r\n\"]+)(/[^\r\n\"]*)?")

	fmt.Println(result.FindAllString(string, -1))
}
