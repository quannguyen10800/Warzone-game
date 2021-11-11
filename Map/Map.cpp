#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include "Map.h"

class Player;

using namespace std;

/*
 * ==============================
 * Continent Class Implementation
 * ==============================
 */


// Constructors and Destructor

Continent::Continent() {
    name = "";
    army_bonus = 0;
}
Continent::Continent(string name, int army_bonus){
    this->name = name;
    this->army_bonus = army_bonus;
}
Continent::Continent(Continent &c) {
    this->name = c.name;
    this->army_bonus =  c.army_bonus;
    for (int i=0; i<c.territories.size(); i++)
        this->territories.at(i) = new Territory(*c.territories.at(i));
}
Continent::~Continent(){
    for (Territory *territory: territories)
        delete territory;
}

// Accessors and Mutators

string Continent::get_name() {
    return name;
}
int Continent::get_army_bonus() {
    return army_bonus;
}
vector<Territory *> Continent::get_territories() {
    return territories;
}

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
    this->name = c.name;
    this->army_bonus =  c.army_bonus;
    for (int i=0; i<c.territories.size(); i++)
        this->territories.at(i) = new Territory(*c.territories.at(i));

    return *this;
}


/*
 * ==============================
 * Territory Class Implementation
 * ==============================
 */


// Constructors and destructor


Territory::Territory() {
    name = "";
    id = 0;
    continent_id = 0;
    armies = 0;
    player = nullptr;
}

Territory::Territory(int id, string name, int continent) : id(id), name(name), continent_id(continent) {
    player = nullptr;
}

Territory::Territory(const Territory& t) {
    this->id = t.id;
    this->continent_id = t.continent_id;
    this->name = t.name;
    this->armies = t.armies;
    this->player = t.player;
    for (Territory *neighbour: t.neighbours) {
        this->neighbours.push_back(neighbour);
    }
}

Territory::~Territory() {
    delete player;
    for (Territory *neighbour: neighbours)
        delete neighbour;
}


// Accessor and Getters

string Territory::get_name() {
    return name;
}

int Territory::get_id() const {
    return id;
}

Continent *Territory::get_continent() {
    return continent;
}

int Territory::get_continent_id() const {
    return continent_id;
}

int Territory::get_armies() const {
    return armies;
}

void Territory::set_armies(int amount) {
    armies = amount;
}

void Territory::setPlayer(Player *player) {
    this->player = player;
}

Player* Territory::getPlayer() {
    return player;
}

void Territory::set_continent(Continent *continent) {
    continent = continent;
}

vector<Territory *> Territory::get_bordering_territory() {
    return neighbours;
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
    this->id = t.id;
    this->continent_id = t.continent_id;
    this->name = t.name;
    this->armies = t.armies;
    for (Territory *neighbour: t.neighbours) {
        this->neighbours.push_back(neighbour);
    }
    return *this;
}


/*
 * ========================
 * Map Class Implementation
 * ========================
 */


// Constructors and Destructor

Map::Map() {};

Map::Map(const Map &map) {

    //Allocating new memory to each of the territory and continent objects
    //to prevent memory leak.
    for (int i=0; i<map.territories.size(); i++)
        this->territories.at(i) = new Territory(*map.territories.at(i));

    for (int i=0; i<map.continents.size(); i++)
        this->continents.at(i) = new Continent(*map.continents.at(i));
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

vector<Territory *> Map::get_territories() const {
    return territories;
}

vector<Continent *> Map::get_continents() const {
    return continents;
}

void Map::add_territory(Territory *t) {
    this->territories.push_back(t);
}

void Map::add_continent(Continent *c) {
    this->continents.push_back(c);
}

// assignment operator
Map& Map::operator=(const Map& map) {
    for (int i=0; i<map.territories.size(); i++)
        this->territories.at(i) = new Territory(*map.territories.at(i));

    for (int i=0; i<map.continents.size(); i++)
        this->continents.at(i) = new Continent(*map.continents.at(i));

    return *this;
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


void Map::DFSUtil(Territory *terr, bool visited[], bool connected_continent){
    visited[terr->get_id()-1] = true;
    for(Territory *neighbour : terr->get_bordering_territory()){
        //In case we are verifying connected components, disregard neighbours of the territory
        //that are not in the same continent.
        if (connected_continent && neighbour->get_continent_id() != terr->get_continent_id()){
            continue;
        }

        if(!visited[neighbour->get_id()-1]){
            DFSUtil(neighbour, visited, connected_continent);
        }
    }
}

bool Map::verify_map_connected_graph() {

    // Boolean array to keep track of territories that have been visited
    int const total_territories = territories.size();
    bool visited_territories[total_territories];

    // Initialize all values to false except the starting value
    for (int i = 1; i < total_territories; i++)
        visited_territories[i] = false;
    visited_territories[0] = true;

    //Run DFS for each territory
    for(Territory *terr : territories){
        if(!visited_territories[terr->get_id() -1])
            DFSUtil(terr, visited_territories, false);
    }

    //Check that all territories are visited
    for (int i = 0; i < total_territories; i++) {
        if (!visited_territories[i])
            return false;
    }
    return true;
}

bool Map::verify_continent_connected_subgraph() {
    for(Continent *cont : continents){

        if (cont->get_territories().empty())
            return false;

        // Boolean array to keep track of territories that have been visited
        int const total_territories = cont->get_territories().size();
        bool visited_territories[total_territories];

        // Initialize all values to false except the starting value
        for (int i = 1; i < total_territories; i++)
            visited_territories[i] = false;
        visited_territories[0] = true;

        //Run DFS for each territory
        for(Territory *terr : cont->get_territories()){
            if(!visited_territories[terr->get_id() -1])
                DFSUtil(terr, visited_territories, true);
        }

        //Check that all territories are visited
        for (int i = 0; i < total_territories; i++) {
            if (!visited_territories[i])
                return false;
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
        cout << "Error loading map -> Reason: Map is not a connected graph." << endl;
        return false;
    }
    // check if continents are a connected subgraph
    if (map->verify_continent_connected_subgraph()) {
        cout << "Continents are connected subgraphs." << endl;
    } else {
        cout << "Error loading map -> Reason: Continents are not connected subgraphs." << endl;
        return false;
    }
    // check if territories are connected by at most 1 continent
    if (map->verify_unique_continents())
        cout << "Territories all have unique continents." << endl;
    //} else {
    //    throw invalid_argument("Error loading map -> Reason: Territories do not have unique continents.");
    //}
    return true;
}

// Function to return a random territory in a given continent.
Territory *Map::random_territory(const string& continent_name){
    for(Continent *continent: continents){
        if (continent->get_name() == continent_name){
            int r = rand() % (continent->get_territories().size() -1);
            return continent->get_territories().at(r);
        }
    }
}


/*
 * ==============================
 * MapLoader Class Implementation
 * ==============================
 */

vector<string> MapLoader::split(const string &str, char delim) {
    stringstream stream(str);
    string token;
    vector<string> tokens;

    while (getline(stream, token, delim)) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> MapLoader::split(const string &str) {
    return split(str, ' ');
}

Map* MapLoader::parse(string file_name, Map *map) {

    ifstream file_reader(file_name);
    string line;

    if (file_reader.fail()) {
        throw runtime_error("Error reading file: " + file_name);
    } else {
        // Read up until the continents section
        while (getline(file_reader, line) && line != "[continents]") {}

        if (file_reader.eof()) {
            throw invalid_argument("Error loading map: Cannot find continents.");
        }

        // For each line in the continents section
        while (getline(file_reader, line) && !line.empty()) {

            vector<string> words = split(line);

            // There should be three 'words' in each line
            if (words.size() != 3) {
                throw invalid_argument("Error loading map: Missing data for continent.");
            }
            // No 'word' should be empty
            for (string &x: words) {
                if (x.empty()) {
                    throw invalid_argument("Error loading map: Missing data for continent.");
                }
            }

            // Declare and initialize a continent object and push to the map
            auto *new_continent = new Continent(words.at(0), stoi(words.at(1)));
            map->add_continent(new_continent);
        }


        // Read up until the Countries section
        while (getline(file_reader, line) && line != "[countries]") {}
        if (file_reader.eof()) {
            throw invalid_argument("Error loading map: Cannot find territories.");
        }

        // For each line in the territory section:
        while (getline(file_reader, line) && !line.empty()) {
            vector<string> words = split(line);

            // Verify that all data for territories in map file are available
            if (words.size() != 5) {
                throw invalid_argument("Error loading map: Missing data for territory.");
            }
            for (const string &x: words) {
                if (x.empty()) {
                    throw invalid_argument("Error loading map: Missing data for territory.");
                }
            }

            if (stoi(words.at(2)) > map->get_continents().size()) {
                throw invalid_argument("Error loading map: Territory with invalid continent id.");
            }

            auto *new_territory = new Territory(stoi(words.at(0)), words.at(1), stoi(words.at(2)));

            //add the new territory to the continent and map subgraph
            map->get_continents()[stoi(words.at(0)) - 1]->add_territory(new_territory);
            map->add_territory(new_territory);
        }


        // Read up until the boarders
        while (getline(file_reader, line) && line != "[borders]") {}
        if (file_reader.eof()) {
            throw invalid_argument("Error loading map: Cannot find borders.");
        }

        vector<Territory *> all_territories = map->get_territories();

        while (getline(file_reader, line) && !line.empty()) {
            vector<string> words = split(line);

            if (words.size() < 2) {
                throw invalid_argument(
                        "Error loading map: Territory is missing its borders or territory id is missing.");
            }
            for (string &x: words) {
                if (x.empty()) {
                    throw invalid_argument(
                            "Error loading map: Territory is missing its borders or territory id is missing.");
                }
            }
            // Verify that the territory id and its neighbours are within bounds
            if (stoi(words[0]) > all_territories.size()) {
                throw invalid_argument("Error loading map: Initial territory index out of range.");
            }

            Territory *t = all_territories[stoi(words[0]) - 1];

            for (int i = 1; i < words.size(); i++) {
                if (stoi(words.at(i)) > all_territories.size()) {
                    throw invalid_argument("Error loading map: Bordering territory id doesn't exist.");
                }
                t->add_neighbour(all_territories[stoi(words[i]) - 1]);
            }
        }
    }
    return *map;
}