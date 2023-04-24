#pragma once
#include <stdio.h>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>
using namespace std;

class Database {
	public: 
		tuple<string, string> getQuestion(int category, int difficulty);
		Database();
		~Database();

		string categoryName[6];
		int categoryID[6];
	private:
		const char* file = "C:/Users/danae/Desktop/Programming/databases/Jeopardy2023/jeopardy.db";
		int connection = 0;
		sqlite3* DB;
	
		void getCategories();
};

