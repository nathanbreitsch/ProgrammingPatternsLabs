#include <map>
#include <iostream>
#include <string>
#include <fstream>
using std::cout; using std::cin;
using std::endl; using std::string;
using std::map; using std::multimap;

class UniqueSchedule{
public:
  static UniqueSchedule& instance(){//meyer's pattern
    static UniqueSchedule theOnlyOne;
    return theOnlyOne;
  }

  void addRequest(string & time, string & name){
    if(! (validTime(time) && schedule_.insert({time, name}).second)){
      denied_requests_.insert({time, name});
    }
  }

  void printSchedule(){
    auto times = {"8:00", "9:00","10:00","11:00","13:00","14:00","15:00", "16:00"};

    cout << "ROOM SCHEDULE" << endl;
    for(string time : times){
      if(schedule_.find(time)!= schedule_.end())
        cout << time << " " << schedule_[time] << endl;
    }
    cout << endl;
    cout << "OPEN TIMES" << endl;
    for(string time : times){
      if(schedule_.find(time) == schedule_.end()){
        cout << time << endl;
      }
    }
    cout << endl;
    cout << "DENIED REQUESTS" << endl;
    for(auto& kvpair : denied_requests_){
      cout << kvpair.first << " " << kvpair.second << endl;
    }
  }

private:
  map<string, string> schedule_;
  multimap<string, string> denied_requests_;
  UniqueSchedule(){}//no creation
  UniqueSchedule(UniqueSchedule&);//no copy construction
  UniqueSchedule& operator=(UniqueSchedule&);//no copy assignment
  bool validTime(string & time){
    return (time =="8:00"||
            time == "9:00" ||
            time =="10:00"||
            time == "11:00" ||
            time == "13:00" ||
            time =="14:00"||
            time == "15:00" ||
            time =="16:00");
  }
};

int main(int argc, char* argv[]){
  if(argc != 2){//4=1+3 because program name counts as argument
    std::cout << "usage: ./main <filename>" << std::endl;
    return 1;
  }

  UniqueSchedule& schedule= UniqueSchedule::instance();

  std::ifstream source(argv[1], std::ios_base::in);
  string name, time;
  char cLine[64];
  while(source.getline(cLine, 64)){
    string line(cLine);
    size_t splitIndex = line.find("\t");
    time = line.substr(0,splitIndex);
    name = line.substr(splitIndex+1);
    schedule.addRequest(time, name);
  }

  schedule.printSchedule();

  return 0;
}
