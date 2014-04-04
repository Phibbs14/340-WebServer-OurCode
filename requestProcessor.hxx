#ifndef REQUEST_PROCESSOR_HXXX
#define REQUEST_PROCESSOR_HXXX

#include <string>
#include "requestTypeEnum.hxx"

int processRequest(RequestType const requestType, std::string fileLocation, std::string& response);

#endif