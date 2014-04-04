#ifndef REQUEST_HEADER_PARSER_HXX
#define REQUEST_HEADER_PARSER_HXX

#include <map>
#include <sstream>

void parseRequestHeaders(std::stringstream&, std::map<std::string, std::string>&);

#endif