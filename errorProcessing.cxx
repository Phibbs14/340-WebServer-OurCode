#include "responseGenerator.hxx"

using std::string;

// Returns an html page with the passed in title and body
string getHtmlErrorPage(string const title, string const body) {
	return 
		"<!DOCTYPE html>\n"
      	"<html>\n"
       	"  <head><title>" + title + "</title></head>\n"
       	"  <body><h1>" + body + "</h1></body>\n"
       	"</html>\n"
	;
}

// Returns an response message for the passed in errorCode
string processErrorCode(int const errorCode) {
	string htmlTitle, htmlBody, headerTitle;

	switch (errorCode) {
		case 400:
			htmlTitle = "HTTP 400: Bad Request";
			htmlBody = "Bad request was received.";
			headerTitle = "400 Bad Request";
			break;
		case 403:
			htmlTitle = "HTTP 403: Forbiddden";
			htmlBody = "Sorry, file cannot be retrieved because of permissions.";
			headerTitle = "403 Forbidden";
			break;
		case 404:
			htmlTitle = "HTTP 404: Not Found";
			htmlBody = "File not found.";
			headerTitle = "400 Not Found";
			break;
		case 500:
			htmlTitle = "HTTP 500: Internal Server Error";
			htmlBody = "Sorry, we have encountered an error.";
			headerTitle = "500 Internal Server Error";
			break;
		case 501:
			htmlTitle = "HTTP 501: Not Implemented";
			htmlBody = "Sorry, request/feature not implemented.";
			headerTitle = "501 Not Implemented";
			break;
		case 505:
			htmlTitle = "HTTP 505: HTTP Version Not Supported";
			htmlBody = "Sorry, HTTP version not supported.";
			headerTitle = "505 Version Not Supported";
			break;
		default:
			throw "Unimplemented Error code - how did I get here?";
	}

    return generateResponse(headerTitle, "text/html", getHtmlErrorPage(htmlTitle, htmlBody));
}