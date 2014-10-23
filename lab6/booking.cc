#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using std::string;
using std::ifstream;
using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::for_each;
using std::unique_copy;
using std::sort;


struct Record {
   string flight_;
   string name_;
   string seat_;
   int price_;
};

int main(){
   vector<Record> tickets;

   // inputing the ticketing records
   ifstream fin("log.txt");
   do{
      Record r;
      string first, last;
      fin >> r.flight_ >> r.seat_>> first >> last >> r.price_;
      if(fin.eof())break;
      r.name_ = first + ' ' + last;
      tickets.push_back(r);
   }while(true);
   fin.close();

  //sort the tickets for unique name
	sort(tickets.begin(), tickets.end(), [](const Record& r1, const Record& r2){
		return(r1.name_ < r2.name_);
	});

  //place to put copies
  vector<Record> unique_names(tickets.size());

	//put unique passengers in passengers vector
   vector<Record>::iterator unique_end = unique_copy(tickets.begin(), tickets.end(), unique_names.begin(),
	[](const Record& r1, const Record& r2){
		return(r1.name_ == r2.name_);
	});

   //print out itinerary
   cout << "ITINERARIES\n" << endl;
   for_each(unique_names.begin(), unique_end, [&](Record& passenger){
		cout << passenger.name_ << ":" << endl;
		int totalPrice = 0;
		for_each(tickets.begin(), tickets.end(), [&](Record & ticket){
			if(ticket.name_ == passenger.name_){
				cout << ticket.flight_ << "\t" << ticket.seat_ << endl;
				totalPrice += ticket.price_;
			}
		});
		cout << "total price: " << totalPrice << endl << endl;
   });

    //sort the tickets for unique flight/seat
   sort(tickets.begin(), tickets.end(), [](const Record& r1, const Record& r2){
		if(r1.seat_ == r2.seat_){
			return r1.flight_ < r2.flight_;
		}
		else{
			return r1.seat_ < r2.seat_;
		}
   });



   //print duplicates/conflicts
   Record previous;
   cout << "\nDUPLICATES\n" << endl;
   bool doubleDuplicate = false;
   for_each(tickets.begin(), tickets.end(), [&](const Record& r){
     if(r.seat_ == previous.seat_ && r.flight_ == previous.flight_){
       if(!doubleDuplicate){
         doubleDuplicate = true;
         cout << previous.flight_ << "\t" << previous.seat_ << "\t" << previous.name_ <<endl;
       }
       cout << r.flight_ << "\t" << r.seat_ << "\t" << r.name_  <<endl;
     }
     else{
       doubleDuplicate = false;
     }
     previous = r;

   });

}
