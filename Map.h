//
// Created by Mehrsa Yazdani on 2021-10-03.
//

#ifndef UNTITLED19_MAP_H
#define UNTITLED19_MAP_H
#include <string>
#include <vector>

using namespace std;

class Territory{
private:


    string *name{};
    int *t_ID{};
    int *numberOfArmies{};
    int *continent{};
    int *owner{};

public:
    Territory();
    Territory(int *id, string *n, int *cont);
    Territory(const Territory &t);
    Territory& operator=(const Territory& t);
    ~Territory();

    int getID() {return *t_ID;}
    int getNumberOfArmies() { return *numberOfArmies; }
    int getOwner() { return *owner; }
    int getContinent(){ return *continent; } //might error!!!!!!
    void setNumberOfArmies(int n) { *numberOfArmies = n; }
    void setOwner(int n) { *owner = n; }
    void setContinent(int cont) {this->continent = &cont; }; //recheck!!!!
    string  getName(){
        return  name;
    }
    vector<Territory*> neighbours(Territory *t1);

    friend std::ostream& operator<<(std::ostream& out, const Territory& t);

};


class Map {
private:
    vector<Territory *> map[];
    vector<Map*> continentsList;
    string* name{};

public:
    Map();
    Map(string *name);
    ~Map();

    void addEdge(Territory* t1, Territory* t2);
    bool isConnected();
    void DFS(int n, bool *visited);
    bool validate();

    friend class MapLoader;


};

#endif //UNTITLED19_MAP_H
