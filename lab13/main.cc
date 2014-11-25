#include <set>
#include <iostream>
#include <string>


using std::string;
using std::set;
using std::cout; using std::endl;

//
// abstract classes describing the mechanism of subscription and notification
// 

class Subject; // forward class declaration

class Observer{
public:
   virtual void update(string newName) const = 0;
};

class Subject{
public: 
   void registerObserver(Observer *o){views_.insert(o);}
   void deregiserObserver(Observer *o){views_.erase(o);}
   void updateObservers() const {for(auto e: views_)e->update(name_);}
   Subject(const string& name): name_(name){};
protected:
    string name_;
private:
   set <Observer *> views_;
};




//
// concrete classes describing the content of subject/observer
//

class ConcreteSubject;

class ConcreteObserver: public Observer {
public:
   ConcreteObserver(const string &);
   void update(string s) const;
private:
   string name_;
   ConcreteSubject *s_;
};

class ConcreteSubject: public Subject {
public:
   ConcreteSubject(const string &name):Subject::Subject(name){}
   void changeName(const string &name){name_=name; updateObservers();}

};



ConcreteObserver::ConcreteObserver(const string &name):
      name_(name){};


void ConcreteObserver::update(string newName) const {
   cout << "observer " << name_ << " reports "
	<< "subject changed name to: " << newName << endl;
}


int main() {
   ConcreteSubject subj("Billy");
   ConcreteObserver obOne("Joe"), obTwo("Jane");
   subj.registerObserver(&obOne);
   subj.registerObserver(&obTwo);

   subj.changeName("Billy");
   subj.changeName("Bill");
   subj.changeName("William");
}