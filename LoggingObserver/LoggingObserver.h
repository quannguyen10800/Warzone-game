#pragma once

#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

//class Iloggable{
//public:
//    virtual string stringToLog() = 0;
//
//protected:
//    string log;
//};
//
//
//class Observer {
//public:
//    ~Observer();
//    virtual void Update() = 0;
//protected:
//    Observer();
//};
//
//class Subject {
//public:
//    virtual void Attach(Observer* o);
//    virtual void Detach(Observer* o);
//    virtual void Notify();
//    Subject();
//    ~Subject();
//private:
//    list<Observer*> *_observers;
//};
//
//class LogObserver: public Observer{
//public:
//    void Update(Iloggable _Iloggable);
//};



class Iloggable;
class Subject;

class Observer {
public:
    Observer();
    ~Observer();
    virtual void update(Subject* i) = 0;
};

class Iloggable{
public:
    Iloggable();
    ~Iloggable();
    virtual string stringToLog() = 0;
};

class Subject : public Iloggable{
public:
    string contentToLog;
    Subject();
    ~Subject();
    virtual void attach(Observer* o);
    virtual void detach(Observer* o);
    virtual void notify();
private:
    list<Observer*> * _observers;
};



class LogObserver : public Observer {
public:
    LogObserver(Subject *subject);
    virtual ~LogObserver();
    void update(Subject* s);
private:
    Subject * _subject;
};
