#pragma once

#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

class Iloggable{
public:
    virtual string stringToLog() = 0;

protected:
    string log;
};


class Observer {
public:
    ~Observer();
    virtual void Update(Iloggable* _Iloggable) = 0;
protected:
    Observer();
};

class Subject {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify(Iloggable* _Iloggable);
    Subject();
    ~Subject();
private:

    list<Observer*> *_observers;
};

class LogObserver: public Observer{
public:
    void Update(Iloggable* _Iloggable);
};
