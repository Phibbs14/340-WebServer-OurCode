#include "requestLineParser.hxx"
#include <iostream>
#include <regex>

using namespace std;

// Check to see if the passed in string matches version number 1.1 or 1.0
// Returns true if matched, false otherwise
bool validateHttpVersion(string const httpVersion) {
	return httpVersion == "1.1" || httpVersion == "1.0";
}

// Matches matchTo against known request types and sets type accordingly
// Returns true if a match is found, false otherwise
bool checkRequestType(string const matchTo, RequestType& type) {
	if (matchTo == "GET")
		type = GET;
	else if (matchTo == "HEAD")
		type = HEAD;
	else if (matchTo == "POST")
		type = POST;
	else	
		return false;
	return true;
}

// Parses the request line for the request type and file location
// Checks for valid http version
// Returns 200 if everything is ok, and the error code otherwise
int parseRequestLine(string const requestLine, RequestType& requestType, string& fileLocation) {

	regex requestTypeRegex{"([A-Za-z]+)\\s(.*)\\sHTTP\\/(.+)"};
	cmatch matchResult;
	
	if (!regex_search(requestLine.c_str(), matchResult, requestTypeRegex))
		return 400; // bad request

	if (!checkRequestType(matchResult[1], requestType)) 
		return 501; // Unimplemented

	if (!validateHttpVersion(matchResult[3]))
		return 505; // Version not supported

	fileLocation = matchResult[2];

	return 200;
}
