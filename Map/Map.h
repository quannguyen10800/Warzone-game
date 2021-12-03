#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;
class Player;
class Continent;
class Territory{
private:
    int id, continent_id, armies;
    string name;
    Continent* continent;
    Player* player;
    vector<Territory*> neighbours;
    int numArmies;
    int numberOfArmies_;
    int pendingIncomingArmies_;
    int pendingOutgoingArmies_;
    std::string name_;


public:
    Territory(int id, string name, int continent);
    Territory(const Territory& obj);
    Territory();
    ~Territory();

    int get_continent_id() const;
    int get_id() const;
    string get_name();
    int get_armies() const;
    void set_armies(int);
    void setPlayer(Player* player);
    Player* getPlayer();
    vector<Territory*> get_bordering_territory();
    Continent* get_continent();
    void set_continent(Continent *continent);

    void add_neighbour(Territory *neighbour);

    Territory& operator=(const Territory &c);
    void addArmies(int armies);
    friend ostream& operator<<(ostream&, const Territory&);
    int getNumberOfMovableArmies();
    int getNumberOfArmies() const;




    void addPendingIncomingArmies(int armies);

    void addPendingOutgoingArmies(int armies);
    int getPendingIncomingArmies() const;
    std::string getName() const;
};

class Continent{
private:
    int army_bonus;
    string name;
    vector<Territory*> territories;

public:
    Continent(string name, int army_bonus);
    Continent(Continent &obj);
    Continent();
    ~Continent();

    string get_name();
    int get_army_bonus();
    vector<Territory*> get_territories();

    void add_territory(Territory* territory);

    Continent& operator=(const Continent &c);
    friend ostream& operator<<(ostream&, const Continent&);
    void addPendingIncomingArmies(int armies);
    void addPendingOutgoingArmies(int armies);
};



class Map{
public:
    vector<Continent*> continents;
    vector<Territory*> territories;

    Map();
    Map(const Map& map);
    ~Map();

    vector<Territory*> get_territories() const;
    vector<Continent*> get_continents() const;

    void add_territory(Territory* new_territory);
    void add_continent(Continent* new_continent);
    bool static validate(Map* map);
    bool verify_map_connected_graph();
    bool verify_continent_connected_subgraph();
    bool verify_unique_continents();

    Territory* random_territory(const string& continent_name);
    void DFSUtil(Territory *terr, bool visited[], bool connected_continent);

    Map& operator=(const Map& m);
    friend ostream& operator<<(ostream&, const Map&);
    friend class MapLoader;

    vector<Territory *> getAdjacentTerritories(Territory *territory);

//    std::unordered_map<Territory*, std::vector<Territory*>> getAdjacencyList() const;
//    std::vector<Territory*> getAdjacentTerritories(Territory* territory);

private:

//    std::unordered_map<Territory*, std::vector<Territory*>> adjacencyList_;


    unordered_map<Territory *, vector<Territory *>> getAdjacencyList() const;
    std::unordered_map<Territory*, std::vector<Territory*>> adjacencyList_;
};



class MapLoader{
public:
    static Map parse(string file_name, Map *map);
    static vector<string> split(const string&);
    static vector<string> split(const string&, char);
};


