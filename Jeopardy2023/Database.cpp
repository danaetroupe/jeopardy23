#include "Database.h"
using namespace std;

Database::Database() {
	connection = sqlite3_open(file, &DB);
    if (connection) {
        cerr << "Error open DB: " << sqlite3_errmsg(DB) << endl;
    }
    else {
        cout << "Opened Database Successfully!" << endl;
        //int count;
        int ex = sqlite3_exec(DB, "SELECT COUNT(*) FROM Category;", callback, 0, NULL);
    }
};

Database::~Database() {
    sqlite3_close(DB);
};

tuple<string, string> Database::getQuestion(int category, int difficulty) {
    return tuple<string, string>{"0", "0"};
}

int Database::callback(void* data, int columns, char** text, char** columnName) {
    for (int i = 0; i < columns; i++) {
        cout << text[i] << endl;
    }
    return 0;
};



