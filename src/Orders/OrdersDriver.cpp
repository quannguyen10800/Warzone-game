//
// Created by Quan Nguyen on 2021-09-26.
//

#include "../Map/Map.h"
#include "Orders.h"
//using namespace std;
int main()
{
    // Setup
    Territory* t1 = new Territory("Japan");
    Territory* t2 = new Territory("US");
    Territory* t3 = new Territory("UK");
    t1->addArmies(10);  //TODO
    t2->addArmies(5);
    t3->addArmies(10);

    Players* player = new Players("Player1");
    Players* enemy = new Players("Player2");
    player->addOwnedTerritory(t1);  //TODO wating for Playerss class
    player->addOwnedTerritory(t2);
    enemy->addOwnedTerritory(t3);

    GameEngine::setPlayers({ player, enemy });  //TODO wating for GameEngine class

    OrdersList ordersList;
    ordersList.add(new DeployOrder(player, 5, t1));
    ordersList.add(new AdvanceOrder(player, 5, t1, t3));
    ordersList.add(new BombOrder(player, t3));
    ordersList.add(new AirliftOrder(player, 5, t1, t2));
    ordersList.add(new BlockadeOrder(player, t1));
    ordersList.add(new NegotiateOrder(player, enemy));



    // Show the OrderList
    std::cout << "===== " << "Original orders list: " << ordersList << " =====" << std::endl;
    for (const auto &order : ordersList.getOrders())
    {
        std::cout << *order << std::endl;
        std::cout << std::boolalpha << "Order is valid: " << order->validate() << std::endl;
        order->execute();
        std::cout << std::endl;
    }

    // Show the OrderList after moving an order from index 1 to index 4
    ordersList.move(1, 4);
    std::cout << "===== " << "Orders list after moving an order: " << ordersList << " =====" << std::endl;
    for (const auto &order : ordersList.getOrders())
    {
        std::cout << *order << std::endl;
    }

    // Show the OrderList after deleting an order at index 5
    ordersList.remove(5);
    std::cout << "\n===== " << "Orders list after deleting an order: " << ordersList << " =====" << std::endl;
    for (const auto &order : ordersList.getOrders())
    {
        std::cout << *order << std::endl;
    }

    delete t1;
    delete t2;
    delete t3;
    GameEngine::resetGameEngine();    //TODO waiting for GameEngine class

    return 0;
}