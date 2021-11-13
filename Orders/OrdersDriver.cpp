


//
// Created by Quan Nguyen on 2021-10-11.
//

#pragma once


#include "../orders/Orders.h"
#include "../gameengine/GameEngine.h"

void  orderDriver()
{
    // Setup
    Territory* quebec = new Territory(1, "Quebec", 101);
    Territory* bc = new Territory(2, "BC", 102);
    Territory* ontario = new Territory(3, "Ontario",103);



    //Adding Players
    Player* player = new Player("A");
    std::cout << "===== " << "Player 2: B is added =====" << std::endl;
    Player* enemy = new Player("B");

    quebec->addArmies(10);
    bc->addArmies(5);
    ontario->addArmies(10);

    // Add
    std::cout << "===== " << "Assign Player A with Quebec and BC=====" << std::endl;
    player->addTerritory(quebec);
    player->addTerritory(bc);
    std::cout << "===== " << "Assign Player B with Ontario =====" << std::endl;
    enemy->addTerritory(ontario);

    OrdersList ordersList;

    //Generate all orders
    ordersList.add(new DeployOrder(player, 3, quebec));
    ordersList.add(new AdvanceOrder(player, 1, quebec, bc));
    ordersList.add(new BombOrder(player, bc));
    ordersList.add(new BlockadeOrder(player, quebec));
    ordersList.add(new AirliftOrder(player, 6, quebec, ontario));
    ordersList.add(new NegotiateOrder(player, enemy));


    // Test invalid
    //  ordersList.add(new DeployOrder(player, 3, california));

    std::cout << "All orders has been generated." << std::endl;

    std::cout << "========== " << "Here is original orders list: " << ordersList << " ==========" << std::endl;
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

    std::cout  << "One card is given to a player if he wins at least 1 territory" << std::endl;

    //(3) one card is given to a player if they conquer at least one territory in a turn (not more than one card per turn)
    if (player->getTerritories().size() >0) {
        cout<<"player get 1 card because he has at least one territory"<<endl;
        vector<Card*>cards;
        // Add random card
        cards.push_back(new Card("randomCard"));
        Hand * handOfCards = new Hand(cards);
        player->setPlayerCards(handOfCards);
    } else if (enemy->getTerritories().size() >0) {
        cout<<"Enemy get 1 card because he has at least one territory"<<endl;
        vector<Card*>cards;
        // Add random card
        cards.push_back(new Card("randomCard"));
        Hand * handOfCards = new Hand(cards);
        enemy->setPlayerCards(handOfCards);
    }

    // Move the order from index 2 to 4
    ordersList.move(2, 4);

    // Display the OrderList after moving order
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
    quebec = NULL;

    delete bc;
    bc = NULL;

    delete ontario;
    ontario = NULL;

//    GameEngine::clearPlayerList();
}