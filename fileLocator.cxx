#include "fileLocator.hxx"
#include <sstream>
#include <fstream>
#include <iostream>
#include "boost/filesystem.hpp"

namespace bf = boost::filesystem;
using namespace std;

// Determines the file type of the path 
// Returns 404 for file not found, since we're only handling these
int parseExtension(bf::path path, string& fileType) {
	string extension = bf::extension(path);
	if 		(extension == ".txt")
		fileType = "text/plain";
	else if (extension == ".html")
		fileType = "text/html";
	else if (extension == ".334html")
		fileType = "text/html";
	else if (extension == ".htm")
		fileType = "text/html";
	else if (extension == ".css")
		fileType = "text/css";
	else if (extension == ".xml")
		fileType = "text/xml";
	else if (extension == ".js")
		fileType = "application/javascript";
	else if (extension == ".svg")
		fileType = "image/svg+xml";
	else if (extension == ".png")
		fileType = "image/png";
	else if (extension == ".jpg")
		fileType = "image/jpeg";
	else
		return 404;

	return 200;
}

int readFile(bf::path filePath, string& fileContent);

//This method tries to find the file within the file system
//If it's found then the readFile method is called.
//Return 404 if the file is not found, 200 if the file was found and read correctly,
//403 if the file has the wrong permissions
int findFile(string const fileLocation, string& fileContent, string& fileType, bool returnFile)
{
	bf::path filePath = fileLocation;
	try
  	{
		if( bf::exists(filePath) ) //File found
		{	
			//Check the files permissions
			bf::file_status fileStatus = status(filePath);
			if (fileStatus.permissions() >= 420)
			{
				if (parseExtension(filePath, fileType) != 200)
					return 404; // unknown extension
				
				//Return any errors that occre after calling the readFile
				if (returnFile)
					return readFile(filePath, fileContent);
				else
					return 200;
			}
			else
				return 403;		//If the file does not have the correct permissions then return error 403
		} else 
			return 404;		// Couldn't find the file, returns 404 error
	}
	catch (const bf::filesystem_error& ex)
  	{
    	return 404;
  	}
}

//Given the filePath this method reads the file contents and stres them into the the
//fileContents variable reference
//If the file is read OK then status 200 is returned, else it returns status 500
int readFile(bf::path filePath, string& fileContent)
{
	try 
	{
		std::ifstream ifs (filePath.string(), std::ifstream::binary);

		ostringstream out;
		out << ifs.rdbuf();
		
		fileContent = out.str();	//get the file contents as a string 
		return 200;
	}
	catch (...)
	{
		return 500;
	}
}
