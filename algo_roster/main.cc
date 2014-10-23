

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::find_if;
using std::sort; using std::for_each;


void addStudents(vector<list<string> > & roster, string fileName);  // reading a list from a fileName
void removeStudents(vector<list<string> > & roster, string fileName);
void printRoster(const vector<list<string> > & roster); // printing a list out

int main(){
    vector <list<string> > roster; // vector of students of course
    addStudents(roster, "cs1");  
    addStudents(roster, "cs2"); 
    addStudents(roster, "cs3"); 
    // reading in dropouts
    removeStudents(roster, "dropouts");
    sort(roster.begin(), roster.end(), [](const list<string> & stud1, const list<string> & stud2){
        if(stud1.size() < 2){return false;}
        if(stud2.size() < 2){return true;}
        return(std::next(stud1.begin())->compare(*std::next(stud2.begin())) < 0);
    });
    printRoster(roster);
}

// reading a list from fileName
void addStudents(vector<list<string > >& roster, string fileName){
   ifstream course((fileName + ".txt").c_str());
   while(!course.eof()){
      string firstName, lastName;
       
      course >> firstName >> lastName;
      const auto & it = find_if(roster.begin(), roster.end(), [firstName, lastName](const list<string>& x){
          if(x.size() < 2){return false;}
          return (x.front() == firstName && *std::next(x.begin()) == lastName);
      });
        
      if(it == roster.end()){//no match, insert new student list
          list<string> * newStudent = new list<string>();
          newStudent->push_back(firstName);
          newStudent->push_back(lastName);
          newStudent->push_back(fileName);
          roster.push_back(*newStudent);
      }
       else{//match
           it->push_back(fileName);
       }
   }
   course.close();
}

void removeStudents(vector <list <string> > & roster, string fileName){
    ifstream course((fileName + ".txt").c_str());
   while(!course.eof()){
        string firstName, lastName;
        course >> firstName >> lastName;
        auto it = find_if(roster.begin(), roster.end(), 
        [firstName, lastName](const list<string> & x){
            if(x.size() < 2){return true;}
            return (x.front() == firstName && *std::next(x.begin()) == lastName);
       });
       if(it!=roster.end()){roster.erase(it);}
   }
   course.close();
}

// printing a list out
void printRoster(const vector< list <string> >& roster){
   for_each(roster.begin(), roster.end(), [](const list<string> & student){
       for_each(student.begin(), student.end(), [](const string & name){
            cout << name << "\t";
       });
       cout << endl;
   });
}
