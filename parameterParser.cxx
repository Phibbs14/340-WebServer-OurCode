#include "parameterParser.hxx"
#include <iostream>
#include <regex>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

char replaceWith(string val);
string fix(string str);

//Method take in the parameter list and an empty map.
//It iterates through then parses the parameters and puts them into the map
void getParameters(string paramList, map<string, string>& parametersMap) {
	regex paramsRegex{"([^&]*=[^&]*)"};

	regex_iterator<string::iterator> rit ( paramList.begin(), paramList.end(), paramsRegex );
	regex_iterator<string::iterator> rend;
	
	while (rit!=rend) {
		regex valueRegex{"([^=]*)=([^=]*)"};
		cmatch valMatch;

		string x = rit->str();

		//fix() converts all of the percent encoding to ascii
		regex_search(fix(x).c_str(), valMatch, valueRegex);	

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
bool getParametersFromFileLocation(string& fileLocation, map<string, string>& parametersMap) {
	//cout << "\n\n\n\n" << fileLocation << "\n";
	regex requestTypeRegex{"(.[^?]*[?])(.*)"};
	cmatch matchResult;
	
	if (!regex_search(fileLocation.c_str(), matchResult, requestTypeRegex))
		return false;

	string paramList = matchResult[2];		//Get the list of parameters

	fileLocation = regex_replace(fileLocation, regex("[?](.*)"), "");	//Remove the parameters from the URL
	
	
	getParameters(paramList, parametersMap);
	return true;
}

//Replaces the following characters: &, < , >, ', " with there html codes
string escapeCharacters(string orig) {
	orig = regex_replace(orig, regex("&"), "&amp;");
	orig = regex_replace(orig, regex("<"), "&lt;");
	orig = regex_replace(orig, regex(">"), "&gt;");
	orig = regex_replace(orig, regex("'"), "&apos;");
	orig = regex_replace(orig, regex("\""), "&quot;");

	return orig;
}


// Returns the fileContents with the all values of pMap->first replaced with pMap->second
string replaceParameters(string fileContent, map<string, string> const pMap) {
	for (auto iter = begin(pMap), endIter = end(pMap); iter != endIter; ++iter) 
		fileContent = regex_replace(fileContent, regex("\\$" + iter->first), escapeCharacters(iter->second));
	
	return fileContent;
}

//Takes in the percent encoded string value and then converts it into the correct char using the hex value
char replaceWith(string val) { 
	int n;
  	char a;
  	istringstream(val) >> hex  >> n;
  	a = n;

  	return a;
}

//Takes in the parameter as a string and then replaces the percent encoding with the proper ascii characters
string fix(string str) {
	str = regex_replace(str, regex("\\+"), " ");
	auto index = str.begin();
	auto last = str.end();
	string val = "ab";
	char c;
	
	for ( ; index != last; ++index)
	{
		if ( *index == '%')
		{
			c = *(index + 1);
			val[0] = c;
			c = *(index + 2);
			val[1] = c;

			char newChar = replaceWith(val);

			*index = newChar;
			str.erase(index + 1, index + 3);
		}
	}

	return str;
}


