#include <iostream>
#include "Map.h"

using namespace std;

int main() {

    Map *map = new Map();
    map = MapLoader::parse();

    return 0;
}
