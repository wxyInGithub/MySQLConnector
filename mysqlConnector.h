#ifndef MYSQL_CONNECTOR_H
#define MYSQL_CONNECTOR_H

#include <mysql/mysql.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <json.hpp>
using namespace std;
using Json = nlohmann::json;

class MYSQLConnector {
public:
	MYSQLConnector(unordered_map<string, string> config);
	~MYSQLConnector();
	Json select(const char* sql);
	bool exec(const char* sql);
	bool execMultiple(vector<string> sql);
private:
	MYSQL* mysql;
};

#endif
