#ifndef PARAMETER_PARSER_HXX
#define PARAMETER_PARSER_HXX

#include <string>
#include <map>

void getParameters(std::string paramList, std::map<std::string, std::string>& parametersMap);
bool getParametersFromFileLocation(std::string& fileLocation, std::map<std::string, std::string>& parametersMap);
std::string replaceParameters(std::string fileContent, std::map<std::string, std::string> const pMap);
#endif