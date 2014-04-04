#ifndef REQUEST_LINE_PARSER_HXX
#define REQUEST_LINE_PARSER_HXX

#include <string>
#include "requestTypeEnum.hxx"

int parseRequestLine(std::string const requestLine, RequestType& requestType, std::string& fileLocation);

#endif