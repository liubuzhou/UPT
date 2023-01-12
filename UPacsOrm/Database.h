#pragma once
#include "sqlite3.h"
#include <string>
#include <memory>
class Database
{
public:
	Database();
	int connect(std::string dbPath);
	int close();
	std::string errConnMsg();
	void freeErrMsg();


	sqlite3* m_db;
	char * m_zErrMsg;
};

