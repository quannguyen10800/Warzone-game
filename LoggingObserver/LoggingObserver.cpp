#include "LoggingObserver.h"
#include <list>
#include <fstream>
using std::list;

Observer::Observer(){
};
Observer::~Observer(){
};



Subject::Subject(){
    _observers = new list<Observer*>;
}
Subject::~Subject(){
    delete _observers;
}
void Subject::Attach(Observer* o){
    _observers->push_back(o);
};
void Subject::Detach(Observer* o){
    _observers->remove(o);
};
void Subject::Notify(Iloggable* _Iloggable){
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(_Iloggable);
};


void LogObserver::Update(Iloggable* _Iloggable) {
    string log = "";
    log = _Iloggable->stringToLog();
    ofstream myfile;

    myfile.open("gamelog.txt");
    myfile << log << endl;
    myfile.close();
}
