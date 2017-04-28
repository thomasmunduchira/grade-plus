#include "Assignment.h"
#include "Database.h"

#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Assignment::Assignment(int id, int categoryId, string name,
                       double pointsPossible, Database db)
    : id(id), categoryId(categoryId), name(name),
      pointsPossible(pointsPossible), db(db) {}

// Getters
int Assignment::getId() const { return id; }

int Assignment::getCategoryId() const { return categoryId; }

string Assignment::getName() const { return name; }

double Assignment::getPointsPossible() const { return pointsPossible; }

// Setters
void Assignment::setCategoryId(int a_categoryId) { categoryId = a_categoryId; }

void Assignment::setName(string a_name) { name = a_name; }

void Assignment::setPointsPossible(double a_pointsPossible) {
  pointsPossible = a_pointsPossible;
}

// Database query commands
void Assignment::insert() {
  stringstream command;
  command << "INSERT INTO assignments ";
  command << "(categoryId, name, pointsPossible) ";
  command << "VALUES (";
  command << getCategoryId() << ", ";
  command << "'" << getName() << "', ";
  command << getPointsPossible() << ");";

  db.execute(command.str());
}

void Assignment::update() const {
  stringstream command;
  command << "UPDATE assignments SET ";
  command << "categoryId = " << getCategoryId() << ", ";
  command << "name = '" << getName() << "', ";
  command << "pointsPossible = " << getPointsPossible() << " ";
  command << "WHERE id = " << getId() << ";";

  db.execute(command.str());
}

void Assignment::remove() const {
  stringstream command;
  command << "DELETE FROM assignments WHERE id = " << getId() << ";";

  db.execute(command.str());
}

// Static database query commands
void Assignment::create(Database db) {
  string command = "CREATE TABLE IF NOT EXISTS assignments ("
                   "    id             INTEGER     PRIMARY KEY,"
                   "    categoryId     INTEGER (1) NOT NULL,"
                   "    name           TEXT (150)  NOT NULL"
                   "                               UNIQUE,"
                   "    pointsPossible NUMERIC (4) NOT NULL"
                   ");";

  db.execute(command);
}

map<int, Assignment *> Assignment::read(Database db) {
  map<int, Assignment *> data;
  vector<vector<string>> results;

  results = db.execute("SELECT * FROM assignments;");

  for (vector<string> row : results) {
    int id = stoi(row[0]);

    data[id] = new Assignment(id, stoi(row[1]), row[2], stod(row[3]), db);
  }

  return data;
}
