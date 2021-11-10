#include <iostream>
#include "Map.h"

using namespace std;

int main() {

    Map *map = new Map();
    if (!MapLoader::parse("europe.map", map))
        delete map;
    else {
        cout << map;
    }
    return 0;
}

