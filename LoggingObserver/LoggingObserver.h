#pragma once

#include <string>
#include <list>
using namespace std;

class Iloggable{
public:
    virtual string stringToLog() = 0;

//protected:
//    string log;
};


class Observer {
public:
    ~Observer();
    virtual void Update() = 0;
protected:
    Observer();
};

class Subject {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();
private:
    list<Observer*> *_observers;
};

class LogObserver: public Observer{
public:
    void Update(Iloggable _Iloggable);
};