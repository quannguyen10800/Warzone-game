#include "LoggingObserver.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"
#include "../Map/Map.h"


int main(){

    Player* player = new Player();
    Territory* target = new Territory();
    string playername = "Gamer";
    player->setpName(&playername);
    BombOrder* advorder = new BombOrder(player, target);
    OrdersList::add(Or)
    return 0;
}
