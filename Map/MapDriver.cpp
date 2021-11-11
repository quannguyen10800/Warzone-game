#include <iostream>
#include "Map.h"

using namespace std;

int main() {

    Map *map = new Map();
    map = MapLoader::parse("europe.map", map);

    return 0;
}
