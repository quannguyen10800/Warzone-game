#include "Map.h"
#include <iostream>
#include <fstream>
#include <vector>

Territory::Territory() {
    *name = "";
    *t_ID = 0;
    *numberOfArmies = 0;
    *owner = 0;
    *continent = 0;
}

Territory::Territory(int* id, string* n, int* cont) {
    this->t_ID = id;
    this->name = n;
    this->continent = cont;
    this->numberOfArmies = 0;
    this->owner = 0;
}

Territory::~Territory() {
    delete[] t_ID;
    delete[] name;
    delete[] numberOfArmies;
    delete[] owner;
    delete[] continent;
}

Territory::Territory(const Territory& t1) {
    this->t_ID = new int(*(t1.t_ID));
    this->name = new string(*(t1.name));
    this->numberOfArmies = new int(*(t1.numberOfArmies));
    this->owner = new int(*(t1.owner));
    this->continent = new int(*(t1.continent));
}

Territory& Territory::operator=(const Territory& t1) {
    this->t_ID = new int(*(t1.t_ID));
    this->name = new string(*(t1.name));
    this->numberOfArmies = new int(*(t1.numberOfArmies));
    this->owner = new int(*(t1.owner));
    this->continent = new int(*(t1.continent));
}

std::ostream& operator<<(std::ostream& out, const Territory& t1) {
    out << std::endl << "\tTerritory ID: " << t1.t_ID << std::endl;
    out << "\tTerritory Name: " << t1.name;
    out << "\tTerritory Number of Armies: " << t1.numberOfArmies;
    out << "\tTerritory Owner: " << t1.owner;
    out << "\tTerritory Continent: " << t1.continent;
    return out;
}






void Map::addEdge(Territory* t1, Territory* t2) {
    map[t1].push_back(t2);
}

Map::Map() {
    *name = "";
}

Map::Map(string* name){
    this->name = name;
}
Map::~Map(){
    delete[] map;
    delete name;
}

void Map::DFS(int n, bool visited[]) {
    visited[n] = true;

    vector<int>::iterator i;
    for (i = map[n].begin(); i != map[n].end(); ++i) {
        if (!visited[*i])
            DFS(*i, visited);
    }
}
bool Map::isConnected() {
    //declare an array on boolean with the size of the map and initialize all members to false
    bool visited[map.size()] = {0};

    //if a node is not visited, run DFS on that node;
    for(int i = 0; i<map.size(); i++){
        if (visited[i] == false)
            DFS(i, visited);
    }

    //traverse through the visited list and return false if a node is not visited
    for(int i2 = 0; i2<map.size(); i2++){
        if (visited[i2] == false)
            return false;
    }
    return true;

    delete[] visited;
}

bool Map::validate(){
    bool b1, b2 = false;
    b1 = map.isConnected();

    //for each subgraph in the continentsList, run validate and return true if all of them are valid.
    for(int i=0; i< continentsList.size(); i++)
        if (!continentsList[i]->isConnected())  //why is this always true???????????
            b2 =false;

    return b1 && b2;
}





void MapLoader::readMap (const string& filename){
    ifstream input(filename);
    Map *map = new Map();

    vector<Territory*> territoryList;
    string cont;
    string str;
    int *id = 0;
    string *terr;
    int *terrcont = 0;
    int *edge = 0;

    while(!input.eof()) {
        getline(input, str);

        if (str == "[continents]\n"){
            getline(input, str);
            while (true){

                //read line until a space char and save the continent name to the cont string.
                for(int i=0; i != ' '; i++)
                        cont += str[i];

                //create continent graph objects and push them to the ContinentsList.
                Map* continent = new Map();
                map->continentsList.push_back(continent);

                //read the next line and break the loop if it's an empty line (end of the continents list)
                getline(input, str);
                if (str == "\n") {
                    cont = "";
                    break;
                }
            }
        }


        // for now, this code only works for maps with less than 100 continents and 100 countries.
        if (str == "[countries]\n"){
            getline(input, str);
            while(true){

                int i = 0;
                //read line until a space char and save the territory ID to id int.
                for(i; str[i] != ' '; i++) {
                    if (*id == 0)
                        *id = str[i] - '0'; //ASCII code of numbers minus ASCII code of '0'
                    else if (*id > 9)
                        *id = *id * 10 + (str[i] - '0');
                }

                //skip the space char and read until the next space and save the territory name to terr.
                for(++i; str[i] != ' '; i++)
                    *terr += str[i];

                //skip space and read and save the continent id of each territory to terrcont.
                for(++i; str[i] != ' '; i++){
                    if (*terrcont == 0)
                        *terrcont = str[i] - '0';
                    else if (*terrcont > 9)
                        *terrcont = *terrcont * 10 + (str[i] - '0');
                }

                //Create territory objects then push them into the territorylist
                Territory* t = new Territory(id, terr, terrcont);
                territoryList.push_back(t);

                //read the next line and break the loop if it's an empty line (end of the countries list)
                getline(input, str);
                if (str == "\n") {
                    *id = 0;
                    *terr = "";
                    *terrcont = 0;
                    break;
                }
            }
        }

        if(str == "[boarders]\n"){
            getline(input, str);
            while(true){
                int i = 0;
                *id = 0;
                for(i=0; str[i] != ' '; i++) {
                    if (*id == 0)
                        *id = str[i] - '0';
                    else if (*id > 9)
                        *id = *id * 10 + (str[i] - '0');
                }

                while(str[i] != '\n') {
                    for (++i; str[i] != ' '; i++) {
                        if (*edge == 0)
                            *edge = str[i] - '0';
                        else if (*edge > 9)
                            *edge = *edge * 10 + (str[i] - '0');

                        //for each neighbour of the current id, add the edge to the map and the continent subgraph
                        map->addEdge(territoryList[*id], territoryList[*edge]);

                        //For continents, add the edge only if the neighbour is in the same continent.
                        if (territoryList[*id]->getContinent() == territoryList[*edge]->getContinent())
                            map->continentsList[territoryList[*id]->getContinent()]-> addEdge(territoryList[*id], territoryList[*edge]);

                        *edge = 0;
                    }
                }

                //read the next line and break the loop if it's the end of the input file
                if(input.eof())
                    break;
            }
        }

    }
    input.close();
}

