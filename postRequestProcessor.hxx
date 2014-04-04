#ifndef POST_REQUEST_PROCESSOR_HXX
#define POST_REQUEST_PROCESSOR_HXX
#include <string>

int processPostRequest(std::string const fileLocation, std::string const paramStr, std::string& response);

#endif