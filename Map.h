#pragma once

#include <vector>
#include <string>

using namespace std;
class Player;
class Territory;

class Continent{
private:
    int *army_bonus = nullptr;
    string *name;
    vector<Territory*> territories;

public:
    Continent(string& name, int army_bonus);
    Continent(Continent &obj);
    Continent();

    string get_name();
    int get_army_bonus();
    vector<Territory*> get_territories();

    void add_territory(Territory* territory);

    Continent& operator=(const Continent &c);
    friend ostream& operator<<(ostream&, const Continent&);

};

class Territory{
private:
    int *id, *continent_id, *armies = nullptr;
    string *name;
    Continent* continent = nullptr;
    Player* player = nullptr;
    vector<Territory*> neighbours;

public:
    Territory(int id, string name, int continent);
    Territory(Territory &obj);
    Territory();
    ~Territory();

    int get_continent_id();
    int get_id();
    string get_name();
    int get_armies();
    void set_armies(int);
    void setPlayer(Player* player);
    Player* getPlayer();
    vector<Territory*> get_bordering_territory();
    Continent* get_continent();
    void set_continent(Continent *continent);

    void add_neighbour(Territory *neighbour);

    Territory& operator=(const Territory &c);
    friend ostream& operator<<(ostream&, const Territory&);

};

class Map{
public:
    vector<Continent*> continents;
    vector<Territory*> territories;

    Map();
    Map(const Map& map);
    ~Map();

    vector<Territory*> get_territories();
    vector<Continent*> get_continents();

    void add_territory(Territory* new_territory);
    void add_continent(Continent* new_continent);
    bool validate(Map* map);
    bool verify_map_connected_graph();
    bool verify_continent_connected_subgraph();
    bool verify_unique_continents();

    Territory* random_territory(string continent_name);

    Map& operator=(const Map& m);
    friend ostream& operator<<(ostream&, const Map&);
};