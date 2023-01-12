#include "Database.h"

Database::Database():m_db(nullptr), m_zErrMsg(nullptr)
{
	
}

int Database::connect(std::string dbPath)
{
	int rc = sqlite3_open(dbPath.c_str(), &m_db);
	return rc;
}

int Database::close()
{
	return sqlite3_close(m_db);
}

std::string Database::errConnMsg()
{
	return std::string(sqlite3_errmsg(this->m_db));
}

void Database::freeErrMsg()
{
	sqlite3_free(this->m_zErrMsg);
}
