
#include "Orders.h"

int OrdersDriver()
{
    // Setup
    Territory* quebec = new Territory();
    quebec->setName("Quebec");
    quebec->setNumberOfArmies(10);

    Territory* bc = new Territory();
    bc->setNumberOfArmies(5);
    bc->setName("BC");

    Territory* ontario = new Territory();
    ontario->setNumberOfArmies(10);
    ontario->setName("Ontario");

    Player* player = new Player("Player");
    Player* enemy = new Player("Enemy");
    player->addTerritory(quebec);
    player->addTerritory(bc);
    enemy->addTerritory(ontario);

   // GameEngine::setPlayers({ player, enemy });

    OrdersList ordersList;
    ordersList.add(new DeployOrder(player, 5, quebec));
    ordersList.add(new AdvanceOrder(player, 5, quebec, ontario));
    ordersList.add(new BombOrder(player, ontario));
    ordersList.add(new AirliftOrder(player, 5, quebec, bc));
    ordersList.add(new BlockadeOrder(player, quebec));
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

    delete quebec;
    delete ontario;
    delete bc;

    return 0;
}