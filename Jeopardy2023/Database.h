#pragma once
#include <stdio.h>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <tuple>
#include <iostream>
using namespace std;

class Database {
	public: 
		tuple<int, string> categories[6];
		tuple<string, string> getQuestion(int category, int difficulty);
		Database();
		~Database();
	private:
		const char* file = "jeopardy.db";
		int connection = 0;
		sqlite3* DB;
		static int callback(void* data, int columns, char** text, char** columnName);

};

