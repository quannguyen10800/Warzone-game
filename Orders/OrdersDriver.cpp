//
// Created by Quan Nguyen on 2021-10-11.
//

#include "OrdersDriver.h"
#include "../Card/Card.h"
#include "../orders/Orders.h"
#include "../GameEngine/GameEngine.h"


void  orderDriver()
{
    // Setup
    Territory* quebec = new Territory(1, "Quebec", 101);
    Territory* bc = new Territory(2, "BC",  102);
    Territory* ontario = new Territory(3, "Ontario", 103);

    quebec->addArmies(10);
    bc->addArmies(5);
    ontario->addArmies(10);

    Player* player = new Player("A");
    Player* enemy = new Player("B");

    // Add
    player->addTerritory(quebec);
    player->addTerritory(bc);
    enemy->addTerritory(ontario);

    OrdersList ordersList;
    ordersList.add(new DeployOrder(player, 3, quebec));
    ordersList.add(new AdvanceOrder(player, 1, quebec, ontario));
    ordersList.add(new BombOrder(player, bc));
    ordersList.add(new BlockadeOrder(player, quebec));
    ordersList.add(new AirliftOrder(player, 6, quebec, ontario));
    ordersList.add(new NegotiateOrder(player, enemy));

    // add 2 random cards to player
    vector<Card*>cards;
    cards.push_back(new Card("blockade"));
    cards.push_back(new Card("airlift"));
    Hand * handOfCards = new Hand(cards);
    player -> setPlayerCards(handOfCards);

    // add 2 random cards to enemy
    vector<Card*>cardsEnemy;
    cards.push_back(new Card("bomb"));
    cards.push_back(new Card("airlift"));
    Hand * handOfCardsEnemy = new Hand(cardsEnemy);
    enemy -> setPlayerCards(handOfCardsEnemy);


    std::cout << "All orders has been generated." << std::endl;

    std::cout << "========== " << "Original Order List: " << ordersList << " ==========" << std::endl;
    for (const auto &order : ordersList.getOrders())
    {
        std::cout << *order << std::endl;
        std::cout << "===== " << "(1) Verify if order is validated before being executed =====" << std::endl;
        if (order->validate()) {
            std::cout << std::boolalpha << "Order is valid. Execute the order."<< std::endl;
            try{
                order->execute();
            }catch(int e) {
                cout << "An exception occurred. Exception Number: " << e << '\n';
            }
        } else {
            std::cout << std::boolalpha << "Order is not valid. No execution!" << std::endl;
        }

        std::cout << std::endl;
    }

    // Move the order from index 2 to 4
    ordersList.move(2, 4);

    // Display the OrderList after moving order
    std::cout << "===== " << "Orders List after moving an order: " << ordersList << " =====" << std::endl;
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
    quebec = NULL;

    delete bc;
    bc = NULL;

    delete ontario;
    ontario = NULL;

//    GameEngine::clearPlayerList();
}