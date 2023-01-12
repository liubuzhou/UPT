#include <iostream>
#include "IniFile.h"

using namespace UPT::utility;

int main()
{
	IniFile ini;
	ini.load("./main.ini");

	ini.set("server", "AE", "UIH");
	ini.remove("server", "ip");
	ini.show();

	ini.save("./temp.ini");

	system("pause");
	return 0;
}