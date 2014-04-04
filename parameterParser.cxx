#include "parameterParser.hxx"
#include <iostream>
#include <regex>
#include <map>
#include <iostream>

using namespace std;

void getParameters(std::string paramList, map<string, string>& parametersMap) {
	regex paramsRegex{"([^&]*=[^&]*)"};

	std::regex_iterator<std::string::iterator> rit ( paramList.begin(), paramList.end(), paramsRegex );
	std::regex_iterator<std::string::iterator> rend;
	
	while (rit!=rend) {
		regex valueRegex{"(.*)=(.*)"};
	cmatch valMatch;
	
	string x = rit->str();
	regex_search(x.c_str(), valMatch, valueRegex);
	
	string mapKey = valMatch[1];
	string mapValue = valMatch[2];
	
	if (!mapKey.empty() && !mapValue.empty()) {
		//Insert the the items found into the map
		parametersMap.insert( pair<string,string>(mapKey, mapValue) );
	}
		++rit;
	}
}

//Used in case of the GET form request
//Check if any parameters are present in the 
bool getParametersFromFileLocation(std::string& fileLocation, map<string, string>& parametersMap) {
	regex requestTypeRegex{"(.[^?]*[?])(.*)"};
	cmatch matchResult;
	if (!regex_search(fileLocation.c_str(), matchResult, requestTypeRegex))
		return false;
	
	fileLocation = regex_replace(fileLocation, std::regex("[?](.*)"), "");	//Remove the parameters from the URL
	string paramList = matchResult[2];		//Get the list of parameters
	
	getParameters(paramList, parametersMap);
	return true;
}

std::string escapeCharacters(std::string orig) {
	orig = regex_replace(orig, std::regex("<"), "&lt;");
	orig = regex_replace(orig, std::regex(">"), "&gt;");
	orig = regex_replace(orig, std::regex("&"), "&amp;");
	orig = regex_replace(orig, std::regex("'"), "&apos;");
	orig = regex_replace(orig, std::regex("\""), "&quot;");

	return orig;
}


// Returns the fileContents with the all values of pMap->first replaced with pMap->second
std::string replaceParameters(std::string fileContent, std::map<std::string, std::string> const pMap) {
	for (auto iter = std::begin(pMap), endIter = std::end(pMap); iter != endIter; ++iter) 
		fileContent = regex_replace(fileContent, std::regex("\\$" + iter->first), escapeCharacters(iter->second));
	
	return fileContent;
}
