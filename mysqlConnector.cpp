#include "mysqlConnector.h"

/*
config = {
	host : ip
	root : rootName
	password : mysqlPassword
	database : the current database 
}
*/
MYSQLConnector::MYSQLConnector(unordered_map<string, string> config)
{
	this->mysql = mysql_init(NULL);
	this->mysql = mysql_real_connect(mysql, config["host"].c_str(), config["root"].c_str(), config["password"].c_str()
		, config["database"].c_str(), 0, NULL, 0);
	mysql_set_character_set(this->mysql, "gbk");
	if (!mysql) cerr << "ERR:" << "Mysql Connect Failed" << endl;
}

MYSQLConnector::~MYSQLConnector()
{
	mysql_close(this->mysql);
}

/* An old version of select strategy, for reference only
Sheet* MYSQLConnector::select(const char* sql)
{
	if (mysql_query(this->mysql, sql))
	{
		cerr << "ERR:" << "mysql query failed" << endl;
		return {};
	}

	MYSQL_RES* res = mysql_store_result(this->mysql);
	MYSQL_ROW row;
	MYSQL_FIELD* field = mysql_fetch_fields(res);
	vector<MYSQL_ROW> rows;
	vector<string> colNames;

	int len = mysql_num_fields(res);
	for (int i = 0; i < len; ++i)
		colNames.push_back(field[i].name);
	while ((row = mysql_fetch_row(res)) != NULL)
		rows.push_back(row);

	Sheet* result = new Sheet(colNames, rows, len);

	mysql_free_result(res);
	return result;
}
*/

Json MYSQLConnector::select(const char* sql)
{
	Json result = {};
	string data = "";
	if (mysql_query(this->mysql, sql))
	{
		cerr << "ERR:" << "mysql query failed" << endl;
		return result;
	}

	MYSQL_RES* res = mysql_store_result(this->mysql);
	MYSQL_ROW row;

	while ((row = mysql_fetch_row(res)) != NULL)
		result.push_back(Json::parse(row[0]));

	mysql_free_result(res);
	return result;
}

bool MYSQLConnector::exec(const char* sql)
{
	mysql_autocommit(this->mysql, 0);
	if (mysql_query(this->mysql, sql))
	{
		cout << "ERR:" << "Mysql Query Failed" << endl;
		mysql_rollback(this->mysql);
		return 0;
	}
	else {
		mysql_commit(this->mysql);
		return 1;
	}
}

bool MYSQLConnector::execMultiple(vector<string> sql)
{
	mysql_autocommit(this->mysql, 0);
	for (size_t i=0,len=sql.size(); i<len; ++i)
	{
		if (mysql_query(this->mysql, sql[i].c_str()))
		{
			cout << "ERR:" << "Index " << i << ": Query Failed" << endl;
			mysql_rollback(this->mysql);
			return 0;
		}
	}

	mysql_commit(this->mysql);
	return 1;
}
