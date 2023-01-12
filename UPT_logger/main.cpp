#include "Logger.h"
#include <iostream>
using namespace UPT::utility;

int main()
{
	Logger::instance()->open();
	LOG_DEBUG("hello world");
	LOG_INFO("hello info");
	LOG_ERROR("hello error");


	std::cout << "hello" << std::endl;
	
	//system("pause");
	return 0;
}

