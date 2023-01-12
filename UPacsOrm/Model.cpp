#include "Model.h"

Model::Model(Database& db):m_Datahandler(nullptr),m_vecDatahandler(nullptr),m_sTableName("")
{
	m_vecDatahandler = std::make_shared<std::vector<std::map<std::string, std::string>>>();
	m_Datahandler = std::make_shared<std::map<std::string, std::string>>();
	m_Modb = &db;
}

int Model::insert(std::map<std::string, std::string>& datahandler)
{
	std::map<std::string, std::string>::iterator it = (&datahandler)->begin();
	std::string sKey = "";
	std::string sValues = "";
	for (; it != (&datahandler)->end(); ++it)
	{
		sKey += '\'' + it->first + '\'' + ',';
		sValues += '\'' + it->second + '\'' + ',';
	}
	sKey.pop_back();
	sValues.pop_back();

	std::string sSql = "insert into " + m_sTableName + "(" + sKey + ") values (" + sValues + ")";

	return sqlite3_exec(m_Modb->m_db, sSql.c_str(), callback, 0, &(m_Modb->m_zErrMsg));
}

int Model::save()
{
	m_Datahandler->insert({ "username", "omyggggggg" });
	m_Datahandler->insert({ "password","1234" });
	std::map<std::string, std::string>::iterator it = m_Datahandler->begin();
	std::string sKey = "";
	std::string sValues = "";
	for (; it != m_Datahandler->end(); ++it)
	{
		sKey += '\'' + it->first  + '\'' + ',';
		sValues += '\'' +  it->second  + '\'' + ',';
	}
	sKey.pop_back();
	sValues.pop_back();

	std::string sSql = "insert into " + m_sTableName + " (" + sKey + ") values (" + sValues + ")";

	int rc = sqlite3_exec(m_Modb->m_db, sSql.c_str(), callback, 0, &(m_Modb->m_zErrMsg));
	return rc;
}

int Model::remove()
{
	return 0;
}
