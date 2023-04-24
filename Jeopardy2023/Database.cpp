#include "database.h"
#include <sstream>
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
    string question;
    string answer;

    ostringstream oss;
    oss << "SELECT question, answer FROM QuestionAnswer WHERE cat_id == " << category << " AND difficulty == " << difficulty;
    string sql = oss.str();
    cout << "sql string: " << sql << endl;
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), sql.length(), &stmt, NULL);

    int success = sqlite3_step(stmt);
    question = (const char*)(sqlite3_column_text(stmt, 0));
    answer = (const char*)(sqlite3_column_text(stmt, 1));
    cout << question << answer << endl;
    return tuple<string, string>{question, answer};
}

void Database::getCategories() {
    string sql = "SELECT id, name from Category ORDER BY random();";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), sql.length(), &stmt, NULL);
    for (int i = 0; i < 6; i++) {
        int count = 0;
        while (count < 5) {
            int success = sqlite3_step(stmt);
            
            ostringstream oss;
            oss << "SELECT count(*) from QuestionAnswer WHERE cat_id == " << sqlite3_column_int(stmt, 0);
            string sql2 = oss.str();
            sqlite3_stmt* stmt2;
            sqlite3_prepare_v2(DB, sql2.c_str(), sql2.length(), &stmt2, NULL);
            success = sqlite3_step(stmt2);
            count = sqlite3_column_int(stmt2, 0);
        }
        categoryID[i] = sqlite3_column_int(stmt, 0);
        categoryName[i] = (const char*)(sqlite3_column_text(stmt, 1));
    }
}




