#include "requestProcessor.hxx"
#include "fileLocator.hxx"
#include "responseGenerator.hxx"
#include "parameterParser.hxx"
#include <map>
#include <regex>


// Processes the request, using requestType (GET, HEAD, POST)
// fileLocation is the file to return
// response will hold the http response to send back
// Returns status code. 200 for OK, and any code that findFile returns that is not 200
int processRequest(RequestType const requestType, std::string fileLocation, std::string& response) {
	std::string fileContent, fileType;

	// parse fileLocation for parameters
	std::map<std::string, std::string> map;

	bool paramtersFound = getParametersFromFileLocation(fileLocation, map);
	
	// findFile will set fileContent to the content of the file, if the last parameter is true (not HEAD)
	int status = findFile(fileLocation, fileContent, fileType, requestType != HEAD);
	if (status != 200)
		return status;

	switch (requestType) {
		case GET: {
			if (paramtersFound)
				fileContent = replaceParameters(fileContent, map);
			response = generateResponse("HTTP/1.1 200 OK", fileType, fileContent);
			break;
		} case HEAD: {
			response = generateResponse("HTTP/1.1 200 OK", fileType, "");
			break;
		} default: {
			return 400;
		}
	}

	return 200;
}



