#include <stdio.h>
#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <map>
#include "Database.h"
#include "Model.h"

using namespace std;
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char **argv) 
{
	Database db;
	
	int rc;

	rc = db.connect("../bin/zxz.db");
	if (rc) 
	{
		std::cout << stderr << "Can't open database: %s\n" << db.errConnMsg() << std::endl;
		db.close();
		return(1);
	}

  	Model mo = Model(db);
	mo.m_sTableName = "userinfo";
	std::map<string, string> mm;
	mm["username"] = "omydafdgu";
	mm["password"] = "1234";


	//mo.delete();
	//mo.select();

	//mo.insert();
	//mo.save()

	//mo.updata();

	//const char* msql = "create table userinfo(username,password)";
	rc = mo.insert(mm);
	//rc = mo.save();
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", db.m_zErrMsg);
		db.freeErrMsg();
	}

	db.close();
	return 0;
	
}