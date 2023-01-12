#pragma once
#include "sqlite3.h"
#include "Database.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
class Model
{
public:
	Model(Database& db);

	int insert(std::map<std::string, std::string>& datahandler);
	int save();
	int remove();
	std::vector<std::map<std::string, std::string>> where(std::string, std::string);


public:
	int count();//数据量
	void truncate();//清空表




	inline static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
		int i;
		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
		return 0;
	}

	std::shared_ptr<std::vector<std::map<std::string, std::string>>>  m_vecDatahandler;
	std::shared_ptr < std::map<std::string, std::string>>  m_Datahandler;
	std::string m_sTableName;
	Database* m_Modb;
};

