#include "database.h"
using namespace std;

Database::Database() {
	connection = sqlite3_open(file, &DB);
    if (connection != SQLITE_OK) {
        cerr << "Error open DB: " << sqlite3_errmsg(DB) << endl;
    }
    else {
        getCategories();
    }
    
};

Database::~Database() {
    sqlite3_close(DB);
};

tuple<string, string> Database::getQuestion(int category, int difficulty) {
    return tuple<string, string>{"0", "0"};
}

void Database::getCategories() {
    string sql = "SELECT id, name from Category ORDER BY random();";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), sql.length(), &stmt, NULL);
    for (int i = 0; i < 6; i++) {
        int success = sqlite3_step(stmt);
        categoryID[i] = sqlite3_column_int(stmt, 0);
        categoryName[i] = (const char*)(sqlite3_column_text(stmt, 1));
        cout << categoryID[i] << ": " << categoryName[i] << endl;
    }
}




