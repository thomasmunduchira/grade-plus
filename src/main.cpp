#include "Course.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
  // main prompt
  bool isOpen = false;
  Course course;

  string input;

  cout << "  _____            __        ___  __       \n";
  cout << " / ___/______ ____/ /__ ____/ _ \\/ /_ _____\n";
  cout << "/ (_ / __/ _ `/ _  / -_)___/ ___/ / // (_-<\n";
  cout << "\\___/_/  \\_,_/\\_,_/\\__/   /_/  /_/\\_,_/___/\n\n";
  // input loop
  while (true) {
    cout << "What would you like to do?\n";
    cout << "\tWORK on an existing Course [W]\n\tCREATE a new Course [C]\n\tQUIT [Q]\n\t$: ";
    getline(cin, input);

    // open Course
    if (tolower(input[0]) == 'w') {
      cout << "Which Course: ";
      getline(cin, input);
      string name = input;
      cout << "Opening Course: " << name << "...\n";
      course.load(name);
      isOpen = true;
      break;
    }

    // create Course
    else if (tolower(input[0]) == 'c') {
      cout << "Please enter a unique name\n";
      cout << "Course Name: ";
      getline(cin, input);
      string name = input;
      cout << "Creating Course: " << name << endl;
      course.load(name);
      isOpen = true;
      break;
    }

    // quit
    else if (tolower(input[0]) == 'q') {
      cout << "Goodbye\n";
      break;
    }

    // invalid
    else {
      cout << "Invalid entry: " << input << endl;
    }
  } // opening loop

  // second loop while the course is open
  while (isOpen) {
    cout << "\nCourse Name: " << course.getName() << "\n";
    cout << "\tSELECT students [S]\n\tSELECT assignments "
            "[A]\n\tSELECT categories [C]\n\tSELECT submissions [B]\n\tQUIT "
            "[Q]\n\t$: ";
    getline(cin, input);
    // students handler
    if (tolower(input[0]) == 's' || tolower(input[0]) == 'S') {
      while (true) {
        course.printStudents();
        cout << "\tADD student [A]\n\tREMOVE student [R]\n\tUP [U]\n\tQUIT [Q]\n\t$: ";
        getline(cin, input);
        // add student
        if (tolower(input[0]) == 'a') {
          cout << "Student ID?: ";
          getline(cin, input);
          string id = input;
          cout << "Student first name?: ";
          getline(cin, input);
          string firstName = input;
          cout << "Student last name?: ";
          getline(cin, input);
          string lastName = input;
          cout << "Student name: " << firstName << " " << lastName
          << " Student ID: " << id << endl;
          course.addStudent(id, firstName, lastName);
        }
        // modify student
        else if (tolower(input[0]) == 'a') {
          cout << "Student ID: ";
          getline(cin, input);
          string id = input;
          cout << "Student first name (or press enter to keep current one): ";
          getline(cin, input);
          string firstName = input;
          cout << "Student last name (or press enter to keep current one): ";
          getline(cin, input);
          string lastName = input;
          cout << "Student name: " << firstName << " " << lastName
          << " Student ID: " << id << endl;
          course.updateStudent(id, firstName, lastName);
        }
        // drop student
        else if (tolower(input[0]) == 'r') {
          cout << "Remove student with ID: ";
          getline(cin, input);
          string id = input;
          
          // call drop student function on that student
          course.deleteStudent(id);
        }
        // up
        else if (tolower(input[0]) == 'u') {
          break;
        }
        // quit
        else if (tolower(input[0]) == 'q') {
          cout << "Goodbye\n";
          isOpen = false;
          break;
        }
      }
    }
    // ASSIGNMENTS HANDLER
    else if (tolower(input[0]) == 'a') {
      while (true) {
        course.printAssignments();
        cout << "\tADD assignment [A]\n\tREMOVE assignment [R]\n\tMODIFY "
        "assignment [M]\n\tUP [U]\n\tQUIT [Q]\n\t$: ";
        getline(cin, input);
        // add assignment
        if (tolower(input[0]) == 'a') {
          cout << "Adding a new assignment:\n";
          cout << "Assignment name: ";
          getline(cin, input);
          string name = input;
          course.printCategories();
          cout << "Category ID: ";
          getline(cin, input);
          int category = input.size() ? stoi(input) : -1;
          cout << "Points possible: ";
          getline(cin, input);
          int weight = input.size() ? stoi(input) : -1;
          course.addAssignment(category, name, weight);
        }
        // modify assignment
        else if (tolower(input[0]) == 'm') {
          cout << "Modify assignment with ID: ";
          getline(cin, input);
          int id = input.size() ? stoi(input) : -1;
          cout << "Assignment name (or press enter to keep current one): ";
          getline(cin, input);
          string name = input;
          course.printCategories();
          cout << "Category ID (or press enter to keep current one): ";
          getline(cin, input);
          int category = input.size() ? stoi(input) : -1;
          cout << "Points possible (or press enter to keep current one): ";
          getline(cin, input);
          int weight = input.size() ? stoi(input) : -1;
          course.updateAssignment(id, category, name, weight);
        }
        // remove assignment
        else if (tolower(input[0]) == 'r') {
          cout << "Remove assignment with ID: ";
          getline(cin, input);
          int id = input.size() ? stoi(input) : -1;
          course.deleteAssignment(id);
        }
        // up
        else if (tolower(input[0]) == 'u') {
          break;
        }
        // quit
        else if (tolower(input[0]) == 'q') {
          cout << "Goodbye\n";
          isOpen = false;
          break;
        }
        // invalid
        else {
          cout << "Invalid entry: " << input << endl;
        }
      }
    }

    // CATEGORIES HANDLER
    else if (tolower(input[0]) == 'c') {
      while (true) {
        course.printCategories();
        cout << "\tADD category [A]\n\tREMOVE category [R]\n\tMODIFY category "
        "[M]\n\tUP [U]\n\tQUIT [Q]\n\t$: ";
        getline(cin, input);
        // add category
        if (tolower(input[0]) == 'a') {
          cout << "Adding a new category:\n";
          cout << "Category name: ";
          getline(cin, input);
          string name = input;
          cout << "Weight: ";
          getline(cin, input);
          int weight = input.size() ? stoi(input) : -1;
          course.addCategory(name, weight);
        }
        // modify category
        else if (tolower(input[0]) == 'm') {
          cout << "Modify category with ID: ";
          getline(cin, input);
          int id = input.size() ? stoi(input) : -1;
          cout << "Category name (or press enter to keep current one): ";
          getline(cin, input);
          string name = input;
          cout << "Weight (or press enter to keep current one): ";
          getline(cin, input);
          int weight = input.size() ? stoi(input) : -1;
          course.updateCategory(id, name, weight);
        }
        // remove category
        else if (tolower(input[0]) == 'r') {
          cout << "Remove category with ID: ";
          getline(cin, input);
          int id = input.size() ? stoi(input) : -1;
          course.deleteCategory(id);
        }
        // up
        else if (tolower(input[0]) == 'u') {
          break;
        }
        // quit
        else if (tolower(input[0]) == 'q') {
          cout << "Goodbye\n";
          isOpen = false;
          break;
        }
        // invalid
        else {
          cout << "Invalid entry: " << input << endl;
        }
      }
    }

    // SUBMITTED HANDLER
    else if (tolower(input[0]) == 'b') {
      while (true) {
        course.printSubmitted();
        char option;
        do {
          cout << "\tSELECT student [S]\n\tSELECT assignment [T]\n\tADD "
          "submission [A]\n\tREMOVE submission [R]\n\tMODIFY submission "
          "[M]\n\tGRADE submission [G]\n\tUP [U]\n\tQUIT [Q]\n\t$: ";
          getline(cin, input);
          // filter by student
          option = tolower(input[0]);
          if (option == 's') {
            cout << "Student ID: ";
            getline(cin, input);
            string studentId = input;
            course.printSubmittedOfStudent(studentId);
          }
          // filter by assignment
          else if (option == 't') {
            cout << "Assignment ID: ";
            getline(cin, input);
            int assignmentId = input.size() ? stoi(input) : -1;
            course.printSubmittedOfAssignment(assignmentId);
          }
        } while (option == 's' || option == 't');
        // add submitted
        if (tolower(input[0]) == 'a') {
          cout << "Adding a new submission:\n";
          course.printAssignments();
          cout << "Assignment ID: ";
          getline(cin, input);
          int assignmentId = input.size() ? stoi(input) : -1;
          course.printStudents();
          cout << "Student ID: ";
          getline(cin, input);
          string studentId = input;
          course.addSubmitted(assignmentId, studentId, 0);
        }
        // modify submitted
        else if (tolower(input[0]) == 'm') {
          cout << "Modify submission with ID: ";
          getline(cin, input);
          int id = input.size() ? stoi(input) : -1;
          course.printAssignments();
          cout << "Assignment ID (or press enter to keep current one): ";
          getline(cin, input);
          int assignmentId = input.size() ? stoi(input) : -1;
          course.printStudents();
          cout << "Student ID (or press enter to keep current one): ";
          getline(cin, input);
          string studentId = input;
          course.updateSubmitted(id, assignmentId, studentId, 0);
        }
        // remove submitted
        else if (tolower(input[0]) == 'r') {
          cout << "Remove submission with ID: ";
          getline(cin, input);
          int id = input.size() ? stoi(input) : -1;
          course.deleteSubmitted(id);
        }
        // grade submitted
        else if (tolower(input[0]) == 'g') {
          cout << "Grade submission with ID: ";
          getline(cin, input);
          int id = input.size() ? stoi(input) : -1;
          cout << "Points earned: ";
          getline(cin, input);
          double pointsEarned = stod(input);
          course.updateSubmitted(id, -1, "", pointsEarned);
        }
        // up
        else if (tolower(input[0]) == 'u') {
          break;
        }
        // quit
        else if (tolower(input[0]) == 'q') {
          cout << "Goodbye\n";
          isOpen = false;
          break;
        }
        // invalid
        else {
          cout << "Invalid entry: " << input << endl;
        }
      }
    }
    
    // quit
    else if (tolower(input[0]) == 'q') {
      cout << "Goodbye\n";
      isOpen = false;
    }

    // else invalid
    else {
      cout << "Invalid entry: " << input << endl;
    }
  } // while course is open
}
