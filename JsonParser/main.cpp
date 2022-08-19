#include <iostream>
using namespace std;
#include "JsonException.h"
#include "JsonParser.h"

int main()
{
	char*  jsonStr = "{\"na,me\":\"yangyihua\",\"age\":35,{\"address\":\"pengbu\",[{\"xueke\":\"yuwen\",\"score\":\"90\"},{\"shengao\":\"90cm\"}]}}";

	char*  jsonStr2 = "{\"name\':\"yangyihua\",\"age\":35,{\"address\":\"pengbu\",[{\"xueke\":\"yuwen\",\"score\":\"90\"},{\"shengao\":\"90cm\"}]}}";
	JsonParser*  parser = NULL;
	try {
       parser = new JsonParser(jsonStr);
	   Event  evet;
	   while(parser->hasNext()) {
	   	evet = parser->next();
	   	if(evet == START_OBJECT) {
	   		std::cout<< "{" << std::endl << "\t";
	   	}
	   	if(evet == END_OBJECT) {
	   		std::cout << "}" << std::endl;
	   	}
	   	if(evet == START_ARRAY) {
	   		std::cout << "[" << std::endl << "\t";
	   	}
	   	if(evet == END_ARRAY) {
	   		std::cout << "]" << std::endl;
	   	}
	   	if(evet == KEY_NAME) {
	   		std::cout << "\"" << parser->getString() << "\":";
	   	}
	   	if(evet == VALUE_STRING) {
	   		std::cout << "\"" << parser->getString() << "\"," << std::endl << "\t";
	   	}
	   	if(evet == VALUE_NUMBER) {
	   		std::cout <<  parser->getString() << std::endl << "\t";
	   	}
	   	if(evet == VALUE_NULL) {
	   
	   	}
	   	if(evet == VALUE_TRUE) {
	   
	   	}
	   	if(evet == VALUE_FALSE) {
	   
	   	}
	  }
	}catch(JsonException exception) {
		std::cout << "We catch a exception here" << std::endl;	
	}
	UINT8  a = 0;
	parser->close();
	
	return 0;
}