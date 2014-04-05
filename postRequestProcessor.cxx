#include "postRequestProcessor.hxx"
#include "parameterParser.hxx"
#include "responseGenerator.hxx"
#include "fileLocator.hxx"

// Processes parameters from a post request
// fileLocation has the exact location of the file to return
// parmaStr contains the parameters that need to be parsed
// response will contain the response to send back
// returns status code 
int processPostRequest(std::string const fileLocation, std::string const paramStr, std::string& response) {
	// parse fileLocation for parameters
	std::map<std::string, std::string> map; // parameter map
	std::string fileContent, fileType;

	getParameters(paramStr, map); // parse paramStr into map
	int status = findFile(fileLocation, fileContent, fileType, true); // get file contents and type
	if (status != 200) // error
		return status;

	// replace file contents with parameters
	fileContent = replaceParameters(fileContent, map);
	// generate response
	response = generateResponse("HTTP/1.1 200 OK", fileType, fileContent);

	return 200;
}