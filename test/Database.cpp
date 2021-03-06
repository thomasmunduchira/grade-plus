#include "Database.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std;

Database::Database() {}

Database::Database(string filename) { load(filename); }

Database::~Database() { sqlite3_close(db); }

void Database::load(string filename) { sqlite3_open(filename.c_str(), &db); }

int callback(void *res, int columns, char **data, char **) {
  vector<vector<string>> &results =
      *(static_cast<vector<vector<string>> *>(res));
  vector<string> row;

  for (int i = 0; i < columns; i++) {
    row.push_back(data[i] ? data[i] : "NULL");

    DEBUG(cout << data[i] << ", ");
  }

  results.push_back(row);

  return 0;
}

vector<vector<string>> Database::execute(string command) const {
  DEBUG(cout << "Executing SQL: " << command << endl);
  DEBUG(cout << "Data: ");

  vector<vector<string>> results;
  char *err;
  int status = sqlite3_exec(db,              /* An open database */
                            command.c_str(), /* SQL to be evaluated */
                            callback,        /* Callback function */
                            &results,        /* 1st argument to callback */
                            &err             /* Error msg written here */
                            );

  DEBUG(cout << endl
             << "DB status: "
             << (status == SQLITE_OK ? "OK" : sqlite3_errstr(status)) << endl);

  if (err) {
    cout << "Error: " << err << endl;
    sqlite3_free(err);
  }

  return results;
}

int Database::lastInsertRowid() const { return sqlite3_last_insert_rowid(db); }
