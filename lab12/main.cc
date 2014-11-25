#include <iostream>
using std::cout; using std::endl;

class Process;

class State{
public:
    virtual void admit(Process * p){}
    virtual void dispatch(Process * p){}
    virtual void interrupt(Process * p){}
    virtual void block(Process * p){}
    virtual void unblock(Process * p){}
    virtual void exit(Process * p){}
    virtual void report() = 0;
};

class Process{
public:
    Process(State* state) : state_(state){}
    void report(){
        state_->report();
    }
    
    void admit(){state_->admit(this);}
    void dispatch(){state_->dispatch(this);}
    void interrupt(){state_->interrupt(this);}
    void block(){state_->block(this);}
    void unblock(){state_->unblock(this);}
    void exit(){state_->exit(this);}
    void setState(State * s){this->state_ = s;}
    

private:
    State * state_;
};

class Ready : public State{
     
public:
    void dispatch(Process * p);
    static State * instance(){
        return new Ready();
    }
    void report(){cout << "Ready" << endl;}
};

class Running : public State{

 public:
    void interrupt(Process * p){
        cout << "Process interrupted" << endl;
        p->setState(Ready::instance());
    }
    void block(Process * p);
    void exit(Process * p);
    static State * instance(){
        return new Running();
    }
    void report(){cout << "Running" << endl;}
};

class Terminated : public State{
 public:
    static State * instance(){
        return new Terminated();
    }
    void report(){cout << "Terminated" << endl;}
};

class Waiting : public State{
        friend class Ready;
 public:
    void unblock(Process * p){
        cout << "Process dependencies have been cleared" << endl;
        p->setState(Ready::instance());
    }
    static State * instance(){
        return new Waiting();
    }
    void report(){cout << "Waiting" << endl;}
};

class New : public State{
public:    
    void admit(Process * p){
        cout << "Process admitted" << endl;
       p->setState(Ready::instance());
    }
    
    static State * instance(){
        return new New();
    }
    void report(){cout << "New" << endl;}
};

void Ready::dispatch(Process * p){
        cout << "Process scheduled" << endl;
        p->setState(Running::instance());
}

void Running::block(Process * p){
        cout << "Process blocked by dependency" << endl;
        p->setState(Waiting::instance());
}

void Running::exit(Process * p){//move to bottom
        cout << "Process terminated" << endl;
        p->setState(Terminated::instance());
}

int main(){
    Process p = * new Process(New::instance());
    p.report();
    p.admit();
    p.report();
    p.exit();
    p.report();
    p.dispatch();
    p.report();
    p.block();
    p.report();
    p.unblock();
    p.report();
    p.exit();
    p.report();
}