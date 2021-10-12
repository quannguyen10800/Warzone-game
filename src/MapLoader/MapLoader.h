#include <string>
#include "Map.h"

using namespace std;

class MapLoader {
public:

    Map* parse(string file_name);

    vector<string> split(const string&);

    vector<string> split(const string&, char);
};

