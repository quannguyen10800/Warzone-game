#include <sstream>
#include <fstream>

#include "MapLoader.h"
#include "Map.cpp"

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

Map *MapLoader::parse(string file_name){
    Map *map = new Map();

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

    //Validate map
    if (map->validate(map))
        return map;
}
