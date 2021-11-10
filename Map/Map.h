#pragma once

#include <vector>
#include <string>

using namespace std;
class Player;
class Territory;

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

    string get_name() const;
    int get_army_bonus();
    vector<Territory*> get_territories();

    void add_territory(Territory* territory);

    Continent& operator=(const Continent &c);
    friend ostream& operator<<(ostream&, const Continent&);



};

class Territory{
private:
    int id, continent_id, armies;
    string name;
    Continent* continent;
    Player* player;
    vector<Territory*> neighbours;

    //Quan Nguyen
    int pendingIncomingArmies;
    int pendingOutgoingArmies;
    int numArmies;

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
    friend ostream& operator<<(ostream&, const Territory&);

    string getName() const;

    void addArmies(int armies);

    void setPendingIncomingArmies(int armies);

    int getPendingIncomingArmies() const;

    int getNumberOfArmies() const;

    void removeArmies(int armies);

    void setPendingOutgoingArmies(int armies);

    int getPendingOutgoingArmies() const;

    int getNumberOfMovableArmies() const;
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

/*    Map* parse(string file_name);
    vector<string> split(const string&);
    vector<string> split(const string&, char);
*/
    Territory* random_territory(const string& continent_name);
    void DFSUtil(Territory *terr, bool visited[], bool connected_continent);

    Map& operator=(const Map& m);
    friend ostream& operator<<(ostream&, const Map&);
    friend class MapLoader;
};


class MapLoader{
public:
    static bool parse(string file_name, Map *map);
    static vector<string> split(const string&);
    static vector<string> split(const string&, char);
};