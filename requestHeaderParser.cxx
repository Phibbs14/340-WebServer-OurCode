#include "requestHeaderParser.hxx"
#include <regex>
#include <string>

//Given the http request string, and an empty map (used to store the header values).
//this method parses the hettp request headers and then places them into the headerMap.
void parseRequestHeaders(std::stringstream& http_request, std::map<std::string, std::string>& headerMap)
{
  using namespace std;
	regex regexForMap{"(([A-Za-z-]+):\\s(.+))"};
	
	string str;
	cmatch mapRegexResult;
	while (getline(http_request, str))
	{
		regex_search(str.c_str(), mapRegexResult, regexForMap);
		
		string mapKey = mapRegexResult[2];
		string mapValue = mapRegexResult[3];
		if(!mapKey.empty() && !mapValue.empty())
		{
			//Insert the the items found into the map
			headerMap.insert( pair<string,string>(mapKey, mapValue) );
		}	
	}
}