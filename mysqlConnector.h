#ifndef MYSQL_CONNECTOR_H
#define MYSQL_CONNECTOR_H

#include <mysql.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class Sheet {
public:
	Sheet(vector<string> colNames, vector<MYSQL_ROW> rows, int length);
	~Sheet();
	vector<string> colNames;
	vector<MYSQL_ROW> rows;
	int length;
};

class MYSQLConnector {
public:
	MYSQLConnector(unordered_map<string, string> config);
	~MYSQLConnector();
	void printRows(Sheet* table);
	Sheet* select(const char* sql);
	bool exec(const char* sql);
	bool execMultiple(vector<string> sql);
private:
	MYSQL* mysql;
};

#endif