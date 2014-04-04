#include "postRequestProcessor.hxx"
#include "parameterParser.hxx"
#include "responseGenerator.hxx"
#include "fileLocator.hxx"


int processPostRequest(std::string const fileLocation, std::string const paramStr, std::string& response) {
	// parse fileLocation for parameters
	std::map<std::string, std::string> map;
	std::string fileContent, fileType;

	getParameters(paramStr, map);
	int status = findFile(fileLocation, fileContent, fileType, true);
	if (status != 200)
		return status;

	fileContent = replaceParameters(fileContent, map);
	response = generateResponse("HTTP/1.1 200 OK", fileType, fileContent);

	return 200;
}