#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <array>
#include "Map.h"

class Player;

using namespace std;

// Constructors
Continent::Continent(string& name, int army_bonus){
    this->name = &name;
    this->army_bonus = &army_bonus;
}
Continent::Continent(Continent &c) {
    this->name = new string(*(c.name));
    this->territories = c.territories;
    this->army_bonus =  new int(*(c.army_bonus));
}
Continent::Continent() {
    this->name = nullptr;
    this->army_bonus = nullptr;
}

// Accessor functions
string Continent::get_name() {
    return *name;
}
int Continent::get_army_bonus() {
    return *army_bonus;
}
vector<Territory *> Continent::get_territories() {
    return territories;
}

// Other functions
void Continent::add_territory(Territory *territory) {
    territories.push_back(territory);
}

// Stream insertion operator
ostream &operator<<(std::ostream& strm, const Continent &continent) {
    return strm << "Continent("
                << "name: " << continent.name
                << ")";
}

// Assignment operator

Continent& Continent::operator=(const Continent& c) {
    for (Territory *territory: territories) {
        delete territory;
    }
    this->name = new string(*(c.name));
    this->territories = c.territories;
    this->army_bonus =  new int(*(c.army_bonus));

    return *this;
}




// Constructors
Territory::Territory() {
    *name = "";
    *id = 0;
    *continent_id = 0;
    *armies = 0;
}

Territory::Territory(Territory& t) {
    this->id = new int(*(t.id));
    this->continent_id = new int(*(t.continent_id));
    this->name = new string(*(t.name));
    this->armies = new int(*(t.armies));
    this->neighbours = t.neighbours;
}

Territory::~Territory() {
    delete[] id;
    delete[] continent_id;
    delete[] name;
    delete[] armies;
    delete[] player;
}

// Accessors and Mutators
string Territory::get_name() {
    return *name;
}

int Territory::get_id() {
    return *id;
}

Continent *Territory::get_continent() {
    return continent;
}

int Territory::get_continent_id() {
    return *continent_id;
}

int Territory::get_armies() {
    return *armies;
}

void Territory::set_armies(int amount) {
    *armies = amount;
}

void Territory::setPlayer(Player *player) {
    this->player = player;
}

Player* Territory::getPlayer() {
    return player;
}

void Territory::set_continent(Continent *continent) {
    this->continent = continent;
}

vector<Territory *> Territory::get_bordering_territory() {
    return this->neighbours;
}

void Territory::add_neighbour(Territory *neighbour) {
    this->neighbours.push_back(neighbour);
}

// Stream insertion operator
ostream &operator<<(std::ostream &strm, const Territory &territory) {
    return strm << "\tID: " << territory.id << " | "
                << territory.name << " | "
                << (!territory.continent ? "()" : territory.continent->get_name()) << " | "
                << "Number of armies: " << territory.armies
                << "\n";
}

// Assignment operator
Territory& Territory::operator=(const Territory& t) {
    for (Territory *neighbour: neighbours) {
        delete neighbour;
    }

    this->id = new int(*(t.id));
    this->continent_id = new int(*(t.continent_id));
    this->name = new string(*(t.name));
    this->neighbours = t.neighbours;
    return *this;
}





// Constructors and Destructor
Map::Map() {};

Map::Map(const Map &map) {
    this->territories = map.territories;
    this->continents = map.continents;
}

Map::~Map() {
    for (Territory *territory: territories) {
        delete territory;
    }
    for (Continent *continent: continents) {
        delete continent;
    }
}

// Accessors and Mutators
vector<Territory *> Map::get_territories() {
    return territories;
}

vector<Continent *> Map::get_continents() {
    return continents;
}

// Other functions
void Map::add_territory(Territory *t) {
    this->territories.push_back(t);
}

void Map::add_continent(Continent *c) {
    this->continents.push_back(c);
}

bool Map::verify_map_connected_graph() {
    int total_territories = territories.size();
    // Boolean array to keep track of territories that have been visited
    bool* visited_territories = new bool[total_territories];

    // Initialize all values to false except the starting value
    for (int i = 0; i < total_territories; i++) {
        visited_territories[i] = false;
    }
    visited_territories[0] = true;

    list<int> queue = { 0 };

    while (!queue.empty()) {
        // Get the current value at the front and then remove it from our queue
        int current = queue.front();
        queue.pop_front();

        Territory *current_territory = territories[current];

        // Get the border territories from the current territory being traversed
        vector<Territory *> bordering_territories = current_territory->get_bordering_territory();
        int bordering_count = current_territory->get_bordering_territory().size();

        // Iterate through each bordering territory
        for (int i = 0; i < bordering_count; i++) {
            Territory *bordering_territory = bordering_territories[i];

            // If the territory wasn't already visited,
            if (!visited_territories[bordering_territory->get_id() - 1]) {
                 queue.push_back(bordering_territory->get_id() - 1);
                 visited_territories[bordering_territory->get_id() - 1] = true;
            }
        }
    }

    // Check that all territories and continents were marked as visited, if not return false
    for (int i = 0; i < total_territories; i++) {
        if (!visited_territories[i]) return false;
    }

    return true;
}

bool Map::verify_continent_connected_subgraph() {
    for (Continent *continent: continents) {
        vector<Territory*> continent_territories = continent->get_territories();

        // If the continent has no territories it is unreachable
        if (continent_territories.empty()) {
            return false;
        }

        // Iterate through each territory belonging to the continent
        for (Territory *_: continent_territories) {
            map<int, bool> visited_territories; //Can't use array as we don't have the size

            // Initialize each territory to false in our map
            for (Territory *territory: continent_territories) {
                visited_territories.insert({territory->get_id() - 1, false });
            }


            list<int> queue;
            queue.push_back(continent_territories[0]->get_id() - 1);

            while (!queue.empty()) {
                // Get the current value at the front and then remove it from our queue
                int current = queue.front();
                queue.pop_front();

                Territory *current_territory = territories[current];

                // Get the border territories from the current territory being traversed
                vector<Territory *> bordering_territories = current_territory->get_bordering_territory();
                int bordering_count = current_territory->get_bordering_territory().size();

                // Iterate through each bordering territory
                for (int j = 0; j < bordering_count; j++) {
                    Territory *bordering_territory = bordering_territories[j];

                    // If the territory wasn't already visited, process it
                    if (!visited_territories[bordering_territory->get_id() - 1]) {
                        // Add it to the queue to be processed on following iterations
                        queue.push_back(bordering_territory->get_id() - 1);
                        visited_territories[bordering_territory->get_id() - 1] = true;

                    }
                }
            }

            for (Territory *territory: continent_territories) {
                if (!visited_territories[territory->get_id() - 1]) return false;
            }
        }
    }

    return true;
}

bool Map::verify_unique_continents(){
    return true;
}

bool Map::validate(Map* map) {
    if (map->verify_map_connected_graph()) {
        cout << "Map is a connected graph." << endl;
    } else {
        throw invalid_argument("Error loading map -> Reason: Map is not a connected graph.");
    }
    // check if continents are a connected subgraph
    if (map->verify_continent_connected_subgraph()) {
        cout << "Continents are connected subgraphs." << endl;
    } else {
        throw invalid_argument("Error loading map -> Reason: Continents are not connected subgraphs.");
    }
    // check if territories are connected by at most 1 continent
    if (map->verify_unique_continents()) {
        cout << "Territories all have unique continents." << endl;
    } else {
        throw invalid_argument("Error loading map -> Reason: Territories do not have unique continents.");
    }
}

// Function to return a random territory in a given continent.
Territory *Map::random_territory(string continent_name){
    for(Continent *continent: continents){
        if (continent->get_name() == continent_name){
            int r = rand() % (continent->get_territories().size() -1);
            return continent->get_territories().at(r);
        }
    }
}

// stream insertion operator
ostream &operator<<(std::ostream& strm, const Map &map) {
    strm << "Map(Territory info: { ";
    for (Territory *territory: map.territories) {
        strm << *territory << (territory == map.territories.back() ? "" : ", ");
    }
    strm << "} Continent info: { ";
    for (Continent *continent: map.continents) {
        strm << *continent << (continent == map.continents.back() ? "" : ", ");
    }
    return strm << " }";
}

// assignment operator
Map& Map::operator=(const Map& m) {
    for (Territory *territory: territories) {
        delete territory;
    }
    for (Continent *continent: continents) {
        delete continent;
    }
    this->territories = m.territories;
    this->continents = m.continents;

    return *this;
}
