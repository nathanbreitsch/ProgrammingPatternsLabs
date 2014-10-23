#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <utility>

using std::ifstream; using std::getline;
using std::cout; using std::endl;
using std::string; using std::map;
using std::list; using std::pair;
using std::make_pair;

typedef struct student{string firstName; string lastName;} student;
void addStudents(map<student, list<string> > & roster, const string & className);
void removeStudents(map<student, list<string> >& roster, const string & className);
void printRoster(map<student, list<string> > &);

bool operator < (const student & left, const student & right){
    return (left.lastName.compare(right.lastName) < 0);   
}

int main(){
    map<student, list<string>> roster;
    addStudents(roster, "cs1");  
    addStudents(roster, "cs2"); 
    addStudents(roster, "cs3"); 
    removeStudents(roster, "dropouts"); 
    printRoster(roster);
}

void addStudents(map<student, list<string> > & roster, const string & className){
    ifstream file((className + ".txt").c_str());
    while(!file.eof()){
        string name;
        student stud;
        getline(file, name);
        stud.firstName = name.substr(0, name.find("\t"));
        stud.lastName = name.substr(name.find("\t"));
        roster[stud].push_back(className);
    }
}

void removeStudents(map<student, list<string> > &roster, const string & className){
    ifstream file((className + ".txt").c_str());
    while(!file.eof()){
        string name;
        student stud;
        getline(file, name);
        stud.firstName = name.substr(0, name.find("\t"));
        stud.lastName = name.substr(name.find("\t"));
        roster.erase(stud);
    }
}

void printRoster(map<student, list<string> > & roster){
    for (const auto & kvPair : roster){
        cout << kvPair.first.firstName << "\t";
        cout << kvPair.first.lastName << "\t";
        for (const auto & course : kvPair.second){
            cout << course << "\t";
        }
        cout << endl;
    }
}


