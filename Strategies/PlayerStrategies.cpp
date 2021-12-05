//
// Created by Quan Nguyen on 2021-11-27.
//

#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include <algorithm>
#include <math.h>
#include <time.h>
#include <unordered_set>


// Operator overloading for PLayerStrategy
std::ostream &operator<<(std::ostream &output, const PlayerStrategy &strategy)
{
    return strategy.print_(output);
}


// Operator overloading for AggressivePlayerStrategy
std::ostream &AggressivePlayerStrategy::print_(std::ostream &output) const
{
    output << "[AggressivePlayerStrategy]";
    return output;
}

// Return a pointer to a new instance of AggressivePlayerStrategy.
PlayerStrategy* AggressivePlayerStrategy::clone() const
{
    return new AggressivePlayerStrategy();
}


namespace
{
    // Custom comparator to sort Territories by the number of armies and then by the number of adjacent enemy territories.
    bool compareTerritoriesByEnemiesAndArmies(Territory* t1, Territory* t2, const Player* owner)
    {
        Map* map = GameEngine::getMap();
        int t1EnemyNeighbors = 0;
        for (const auto &territory : map->getAdjacentTerritories(t1))
        {
            if (GameEngine::getOwnerOf(territory) != owner)
            {
                t1EnemyNeighbors++;
            }
        }

        int t2EnemyNeighbors = 0;
        for (const auto &territory : map->getAdjacentTerritories(t2))
        {
            if (GameEngine::getOwnerOf(territory) != owner)
            {
                t2EnemyNeighbors++;
            }
        }

        if (t1->get_armies() != t2->get_armies())
        {
            return t1->get_armies() > t2->get_armies();
        }

        return t1EnemyNeighbors > t2EnemyNeighbors;
    }
}



// Give me a list of regions I should attack.
std::vector<Territory*> AggressivePlayerStrategy::toAttack(const Player* player) const
{
    std::vector<Territory*> sources = toDefend(player);
    std::vector<Territory*> territoriesToAttack;
    std::unordered_set<Territory*> territoriesSeen;
    Map* map = GameEngine::getMap();

    for (const auto &territory : sources)
    {
        std::vector<Territory*> adjacentTerritories = map->getAdjacentTerritories(territory);
        auto sortLambda = [&player](auto t1, auto t2){ return compareTerritoriesByEnemiesAndArmies(t1, t2, player); };
        sort(adjacentTerritories.begin(), adjacentTerritories.end(), sortLambda);

        for (const auto &neighbor : adjacentTerritories)
        {
            bool isEnemyOwned = find(sources.begin(), sources.end(), neighbor) == sources.end();
            bool alreadySeen = territoriesSeen.find(neighbor) != territoriesSeen.end();

            if (isEnemyOwned && !alreadySeen)
            {
                territoriesToAttack.push_back(neighbor);
                territoriesSeen.insert(neighbor);
            }
        }
    }

    return territoriesToAttack;
}


// Give me a list of regions I should defend.
std::vector<Territory*> AggressivePlayerStrategy::toDefend(const Player* player) const
{
    std::vector<Territory*> territoriesToDefend = player->ownedTerritories_;
    auto sortLambda = [](auto t1, auto t2){ return t1->getNumberOfArmies() > t2->getNumberOfArmies(); };
    sort(territoriesToDefend.begin(), territoriesToDefend.end(), sortLambda);
    return territoriesToDefend;
}


// Issue an order to either:
// - Deploy to strongest territory
// - Play a card from the hand
// - Attack an enemy territory with the strongest territory
// - Advance all armies from the strongest territory to another territory
void AggressivePlayerStrategy::issueOrder(Player* player)
{
    std::vector<Territory*> territoriesToAttack = toAttack(player);
    std::vector<Territory*> territoriesToDefend = toDefend(player);

    bool finishedDeploying = deployToTT(player, territoriesToDefend);
    if (finishedDeploying)
    {
        bool finishedPlayingCards = playCard_(player, territoriesToDefend);
        if (finishedPlayingCards)
        {
            bool finishedAttacking = attackFromTT(player, territoriesToDefend.front(), territoriesToAttack);
            if (finishedAttacking)
            {
                bool finishedIssuingOrders = advanceToRandomTerritory_(player, territoriesToDefend);
                player->committed_ = finishedIssuingOrders;
            }
        }

    }
}


// Deploy all reinforcements to the strongest territory.
// If the deployment is complete and no additional orders have been given, this method returns true.
// If an order was issued, this method returns 'false.'
bool AggressivePlayerStrategy::deployToTT(Player* player, std::vector<Territory*> territoriesToDefend)
{
    if (player->reinforcements_ == 0)
    {
        return true;
    }

    Territory* topTerritory = territoriesToDefend.front();
    DeployOrder* order = new DeployOrder(player, player->reinforcements_, topTerritory);
    player->addOrder(order);
    topTerritory->addPendingIncomingArmies(player->reinforcements_);
    player->reinforcements_ = 0;

    std::cout << "Issued: " << *order << std::endl;
    return false;
}


// Advance all armies from strongest territory to an enemy territory.
// If the deployment is complete and no additional orders have been given, this method returns true.
// If an order was issued, this method returns 'false.'
bool AggressivePlayerStrategy::attackFromTT(Player* player, Territory* attackFrom, std::vector<Territory*> territoriesToAttack)
{
    Map* map = GameEngine::getMap();
    int movableArmies = attackFrom->getNumberOfMovableArmies();

    if (movableArmies > 0)
    {
        for (const auto &territory : map->getAdjacentTerritories(attackFrom))
        {
            bool isEnemyTerritory = find(territoriesToAttack.begin(), territoriesToAttack.end(), territory) != territoriesToAttack.end();
            bool alreadyAdvancedToTerritory = player->advancePairingExists_(attackFrom, territory);

            if (isEnemyTerritory && !alreadyAdvancedToTerritory)
            {
                AdvanceOrder* order = new AdvanceOrder(player, movableArmies, attackFrom, territory);
                player->addOrder(order);
                attackFrom->addPendingOutgoingArmies(movableArmies);
                player->issuedDeploymentsAndAdvancements_[attackFrom].push_back(territory);

                std::cout << "Issued: " << *order << std::endl;
                return false;
            }
        }
    }

    return true;
}


// Advance armies from the top/strongest territory to another adjacent fristd::endly territory.
// This will prevent the player from becoming trapped endlessly deploying to the top territory
// when there are no nearby enemy territories to assault.
// If the deployment is complete and no additional orders have been given, this method returns true.
// If an order was issued, this method returns 'false.'
bool AggressivePlayerStrategy::advanceToRandomTerritory_(Player* player, std::vector<Territory*> territoriesToDefend)
{
    Territory* topTerritory = territoriesToDefend.front();
    int movableArmies = topTerritory->getNumberOfMovableArmies();

    // If the player hasn't already moved all the armies to attack an enemy, move to another fristd::endly territory
    if (movableArmies > 0)
    {
        std::vector<Territory*> adjacentTerritories = GameEngine::getMap()->getAdjacentTerritories(topTerritory);

        // Pick a random destination
        srand(time(nullptr));
        int randomIndex = rand() % adjacentTerritories.size();
        Territory* destination = adjacentTerritories.at(randomIndex);

        AdvanceOrder* order = new AdvanceOrder(player, movableArmies, topTerritory, destination);
        player->addOrder(order);
        topTerritory->addPendingOutgoingArmies(movableArmies);
        player->issuedDeploymentsAndAdvancements_[topTerritory].push_back(destination);

        std::cout << "Issued: " << *order << std::endl;
        return false;
    }

    return true;
}


// Helper method to play a random Card from the Player's hand, if any.
// If the deployment is complete and no additional orders have been given, this method returns true.
// If an order was issued, this method returns 'false.'
bool AggressivePlayerStrategy::playCard_(Player* player, std::vector<Territory*> territoriesToDefend)
{
    Hand* playerHand = player->hand_;
    if (playerHand->size() == 0)
    {
        return true;
    }

    // Play a random card from hand
    int randomCardIndex = rand() % playerHand->size();
    Card* card = playerHand->removeCard(randomCardIndex);
    Order* order = card->play();
//    std::cout << "Played: " << *card << std::endl;

    // Return the played card back to the deck
    card->setOwner(nullptr);
    GameEngine::getDeck()->addCard(card);

    if (order != nullptr)
    {
        player->addOrder(order);
        std::cout << "Issued: " << *order << std::endl;
    }
    else if (player->reinforcements_ > 0)
    {
        // Reinforcement card played: deploy the additional reinforcements
        deployToTT(player, territoriesToDefend);
    }

    return false;
}







//***************** Human PLayer***************************************

// Operator overloading
std::ostream &HumanPlayerStrategy::print_(std::ostream &output) const
{
    output << "[HumanPlayerStrategy]";
    return output;
}

// Return a pointer to a new instance of HumanPlayerStrategy.
PlayerStrategy* HumanPlayerStrategy::clone() const
{
    return new HumanPlayerStrategy();
}


// Return a list of territories to defend
std::vector<Territory*> HumanPlayerStrategy::toDefend(const Player* player) const
{
    return player->ownedTerritories_;
}

// Return a list of territories to attack
std::vector<Territory*> HumanPlayerStrategy::toAttack(const Player* player) const
{
    std::vector<Territory*> ownedTerritories = player->ownedTerritories_;
    std::vector<Territory*> territoriesToAttack;
    std::unordered_set<Territory*> territoriesSeen;
    Map* map = GameEngine::getMap();

    for (const auto &territory : ownedTerritories)
    {
        for (const auto &neighbor : map->getAdjacentTerritories(territory))
        {
            bool isEnemyOwned = find(ownedTerritories.begin(), ownedTerritories.end(), neighbor) == ownedTerritories.end();
            bool alreadySeen = territoriesSeen.find(neighbor) != territoriesSeen.end();

            if (isEnemyOwned && !alreadySeen)
            {
                territoriesToAttack.push_back(neighbor);
                territoriesSeen.insert(neighbor);
            }
        }
    }

    return territoriesToAttack;
}


// Issue an order based on user input
void HumanPlayerStrategy::issueOrder(Player* player)
{
    std::vector<Territory*> territoriesToAttack = toAttack(player);
    std::vector<Territory*> territoriesToDefend = toDefend(player);

    // Only allow deploy if the player still has reinforcements
    if (player->reinforcements_ > 0)
    {
        deployReinforcements_(player, territoriesToDefend);
    }
    else
    {
        std::cout << "Please choose the following options:" << std::endl;
        if (player->getOwnTerritoriesWithMovableArmies().size() > 0)
        {
            std::cout << "[A] Advance" << std::endl;
        }
        if (player->hand_->size() > 0)
        {
            std::cout << "[P] Play a card" << std::endl;
        }
        std::cout << "[X] Commit" << std::endl;

        while (true)
        {
            std::string selection;
            std::cin >> selection;
            std::transform(selection.begin(), selection.end(), selection.begin(), ::toupper);

            if (selection == "A")
            {
                issueAdvance_(player, territoriesToDefend);
                break;
            }
            else if (selection == "P")
            {
                playCard_(player, territoriesToDefend);
                break;
            }
            else if (selection == "X")
            {
                player->committed_ = true;
                break;
            }
        }
    }
}


// Give an order to fortify or attack a region in advance.
void HumanPlayerStrategy::issueAdvance_(Player* player, std::vector<Territory*> territoriesToDefend)
{
    std::vector<Territory*> possibleSources = player->getOwnTerritoriesWithMovableArmies();

    std::cout << "\nFrom which territory do you wish to advance?" << std::endl;
    for (int i = 0; i < possibleSources.size(); i++)
    {
        Territory* territory = possibleSources.at(i);
        std::cout << "[" << i+1 << "] " << territory->getName() << " (" << territory->getNumberOfMovableArmies() << " armies available)" << std::endl;
    }

    Territory* source = nullptr;
    std::cout << "\nEnter the territory to advance from: ";
    while (source == nullptr)
    {
        int selection;
        std::cin >> selection;

        if (std::cin.fail() || selection - 1 < 0 || selection - 1 >= possibleSources.size())
        {
            std::cout << "Invalid option. PLease try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        source = possibleSources.at(selection - 1);
    }

    // Display adjacent territories as either attackable or defendable
    Map* map = GameEngine::getMap();
    std::vector<Territory*> attackable;
    std::vector<Territory*> defendable;
    for (const auto &neighbor : map->getAdjacentTerritories(source))
    {
        if (find(territoriesToDefend.begin(), territoriesToDefend.end(), neighbor) != territoriesToDefend.end())
        {
            defendable.push_back(neighbor);
        }
        else
        {
            attackable.push_back(neighbor);
        }
    }

    int i = 0;
    std::cout << "\nFrom which territory do you wish to advance?" << std::endl;
    if (!defendable.empty())
    {
        std::cout << "~~~ To Defend ~~~" << std::endl;
        for (; i < defendable.size(); i++)
        {
            Territory* territory = defendable.at(i);
            std::cout << "[" << i+1 << "] " << territory->getName() << " (" << territory->get_armies() << " armies)" << std::endl;
        }
        std::cout << std::endl;
    }
    if (!attackable.empty())
    {
        std::cout << "~~~ To Attack ~~~" << std::endl;
        for (; i < defendable.size() + attackable.size(); i++)
        {
            int idx = i - defendable.size();
            Territory* territory = attackable.at(idx);
            std::cout << "[" << i+1 << "] " << territory->getName() << " (" << territory->get_armies() << " armies)" << std::endl;
        }
    }

    Territory* destination = nullptr;
    std::cout << "\nEnter the territory to advance: ";
    while (destination == nullptr)
    {
        int selection;
        std::cin >> selection;

        if (std::cin.fail() || selection - 1 < 0 || selection - 1 >= defendable.size() + attackable.size())
        {
            std::cout << "Invalid option. Try Again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (selection <= defendable.size())
        {
            destination = defendable.at(selection - 1);
        }
        else
        {
            destination = attackable.at(selection - 1 - defendable.size());
        }
    }

    int armiesToMove = 0;
    int movableArmies = source->getNumberOfMovableArmies();
    std::cout << "Number of armies to move:";
    while (armiesToMove == 0)
    {
        int selection;
        std::cin >> selection;

        if (std::cin.fail() || selection < 1 || selection > movableArmies)
        {
            std::cout << "Please enter a number between 1 and " << movableArmies << ": " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        armiesToMove = selection;
    }

    AdvanceOrder* order = new AdvanceOrder(player, armiesToMove, source, destination);
    player->addOrder(order);
    source->addPendingOutgoingArmies(armiesToMove);

    std::cout << "Issued: " << *order << std::endl << std::endl;
}


// Deploy the reinforcements of the player to a certain area.
void HumanPlayerStrategy::deployReinforcements_(Player* player, std::vector<Territory*> territoriesToDefend) {
    std::cout << "You have " << player->reinforcements_ << " reinforcements left." << std::endl;
    std::cout << "\nDeploy to:" << std::endl;
    for (int i = 0; i < territoriesToDefend.size(); i++) {
        Territory *territory = territoriesToDefend.at(i);
        std::cout << "[" << i + 1 << "] " << territory->getName() << " (" << territory->getNumberOfArmies()
                  << " present, " << territory->getPendingIncomingArmies() << " pending)" << std::endl;
    }

    Territory *deployTarget = nullptr;
    std::cout << "\nEnter the territory you wish to deploy to: ";
    while (deployTarget == nullptr) {
        int selection;
        std::cin >> selection;

        if (std::cin.fail() || selection - 1 < 0 || selection - 1 >= territoriesToDefend.size()) {
            std::cout << "Invalid option. Try Again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        deployTarget = territoriesToDefend.at(selection - 1);
    }
}


// Play a card from a player's hand.
void HumanPlayerStrategy::playCard_(Player* player, std::vector<Territory*> territoriesToDefend)
{
    Hand* playerHand = player->hand_;

    std::cout << "\nWhich card would you like to play?" << std::endl;
    for (int i = 0; i < playerHand->size(); i++)
    {
        Card* card = playerHand->getCards().at(i);
//        std::cout << "[" << i+1 << "] " << *card << std::endl;
    }

    Card* card = nullptr;
    std::cout << "\nEnter the card to play: ";
    while (card == nullptr)
    {
        int selection;
        std::cin >> selection;

        if (std::cin.fail() || selection - 1 < 0 || selection - 1 >= playerHand->size())
        {
            std::cout << "That was not a valid option. Please try again:" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        card = playerHand->removeCard(selection - 1);
    }

    Order* order = card->play();

    // Return the played card back to the deck
    card->setOwner(nullptr);
    GameEngine::getDeck()->addCard(card);

    if (order != nullptr)
    {
        player->addOrder(order);
        std::cout << "Issued: " << *order << std::endl << std::endl;
    }
    else if (player->reinforcements_ > 0)
    {
        deployReinforcements_(player, territoriesToDefend);
    }
}
//*****************************************************


//***************** Benevolent PLayer *****************
PlayerStrategy* BenevolentPlayerStrategy::clone() const
{
    return new BenevolentPlayerStrategy();
}


//***************** Neutral PLayer *****************
PlayerStrategy* NeutralPLayerStrategy::clone() const
{
    return new NeutralPLayerStrategy();
}
//*****************************************************

//***************** Cheater PLayer *****************
PlayerStrategy* CheaterPlayerStrategy::clone() const
{
    return new CheaterPlayerStrategy();
}
//*****************************************************


