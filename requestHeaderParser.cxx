#include "requestHeaderParser.hxx"
#include <regex>
#include <string>

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