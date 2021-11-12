
#include "Orders.h"
//#include "../Orders/Orders.h"
//#include "../GameEngine/GameEngine.h"

[[maybe_unused]] int OrdersDriver()
{
    // Setup

    Territory* quebec = new Territory(1, "Quebec", 101);
    Territory* bc = new Territory(2, "bc", 102);
    Territory* ontario = new Territory(3, "Ontario",103);


    Player* player = new Player("Player");
    Player* enemy = new Player("Enemy");
    player->addTerritory(quebec);
    player->addTerritory(bc);
    enemy->addTerritory(ontario);

   // GameEngine::setPlayers({ player, enemy });
   GameEngine::addPlayersToList(player);
   GameEngine::addPlayersToList(enemy);

    OrdersList ordersList;
    ordersList.add(new DeployOrder(player, 5, quebec));
    ordersList.add(new AdvanceOrder(player, 5, quebec, ontario));
    ordersList.add(new BombOrder(player, ontario));
    ordersList.add(new AirliftOrder(player, 5, quebec, bc));
    ordersList.add(new BlockadeOrder(player, quebec));
    ordersList.add(new NegotiateOrder(player, enemy));



    // Show the OrderList as below.
    std::cout << "===== " << "Original orders list: " << ordersList << " =====" << std::endl;
    for (const auto &order : ordersList.getOrders())
    {
        std::cout << *order << std::endl;
        std::cout << std::boolalpha << "Order is valid: " << order->validate() << std::endl;
        order->execute();
        std::cout << std::endl;
    }

    // Move the order from index 2 to 4
    ordersList.move(2, 4);
    std::cout << "===== " << "Orders list after moving an order: " << ordersList << " =====" << std::endl;
    for (const auto &order : ordersList.getOrders())
    {
        std::cout << *order << std::endl;
    }

    // Delete the order at index 3
    ordersList.remove(3);
    std::cout << "\n===== " << "Orders list after deleting an order: " << ordersList << " =====" << std::endl;
    for (const auto &order : ordersList.getOrders())
    {
        std::cout << *order << std::endl;
    }


    // After all, delete all territories
    delete quebec;
    quebec =NULL;

    delete ontario;
    ontario =NULL;

    delete bc;
    bc = NULL;

//    GameEngine::clearPlayerList();
    return 0;
}