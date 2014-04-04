#include "responseGenerator.hxx"
#include "http_utils.hxx"
#include <chrono>
#include "rfc2822.hxx"

// Will generate the http response by creating the response header, followed by the body if any
std::string generateResponse(std::string const header, std::string const contentType, std::string const body) {
	std::stringstream ret;
    // get time
	using namespace std::chrono;
  	std::time_t time_in_secs = system_clock::to_time_t(system_clock::now());

    // build header
	ret 
		<< "HTTP/1.1 " << header << crlf
    	<< "Server: 03-60-340_Project_WebServer/1.0" << crlf
    	<< "Date: " << rfc2822::date(gmtime(&time_in_secs)) << crlf
    	<< "Connection: close" << crlf
    	<< "Content-Type: " << contentType << crlf
    	<< crlf;

    // append body if any
    if (body.empty()) 
    	ret << crlf;
    else
    	ret << body << crlf << crlf;

    return ret.str();
}
