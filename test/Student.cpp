#include "Student.h"
#include "Database.h"
#include "DatabaseItem.h"

#include <sstream>
#include <string>

using namespace std;

ostream &operator<<(ostream &output, const Student &student) {
  output << "Student " << student.getId() << " ";
  output << "First Name: " << student.getFirstName() << ", ";
  output << "Last Name: " << student.getLastName();
  return output;
}

Student::Student(string id, string firstName, string lastName, Database &db)
    : DatabaseItem(db), id(id), firstName(firstName), lastName(lastName) {}

// Getters
string Student::getId() const { return id; }

string Student::getFirstName() const { return firstName; }

string Student::getLastName() const { return lastName; }

// Setters
void Student::setId(string a_id) { id = a_id; }

void Student::setFirstName(string a_firstName) { firstName = a_firstName; }

void Student::setLastName(string a_lastName) { lastName = a_lastName; }

// Database query commands
void Student::insert() {
  stringstream command;
  command << "INSERT INTO students VALUES (";
  command << "'" << getId() << "', ";
  command << "'" << getFirstName() << "', ";
  command << "'" << getLastName() << "'";
  command << ");";

  db.execute(command.str());
}

void Student::update() const {
  stringstream command;
  command << "UPDATE students SET ";
  command << "firstName = '" << getFirstName() << "', ";
  command << "lastName = '" << getLastName() << "' ";
  command << "WHERE id = '" << getId() << "'";
  command << ";";

  db.execute(command.str());
}

void Student::remove() const {
  stringstream command;
  command << "DELETE from students WHERE ";
  command << "id = '" << getId() << "'";
  command << ";";

  db.execute(command.str());
}

// Static database query commands
void Student::create(Database &db) {
  string command = "CREATE TABLE IF NOT EXISTS students (\n"
                   "    id        TEXT (16) PRIMARY KEY\n"
                   "                        NOT NULL\n"
                   "                        UNIQUE,\n"
                   "    firstName TEXT (36) NOT NULL,\n"
                   "    lastName  TEXT (36) NOT NULL\n"
                   ");";

  db.execute(command);
}

map<string, Student *> Student::read(Database &db) {
  map<string, Student *> data;
  vector<vector<string>> results;

  results = db.execute("SELECT * FROM students;");

  for (vector<string> row : results) {
    string id = row[0];

    data[id] = new Student(id, row[1], row[2], db);
  }

  return data;
}
