cmake_minimum_required(VERSION 3.20)
project(Local_COMP345)

set(CMAKE_CXX_STANDARD 17)

add_executable(Local_COMP345
        main.cpp
        Player/Player.cpp Player/Player.h  Player/PlayerDriver.cpp
        LoggingObserver/LoggingObserver.h LoggingObserver/LoggingObserver.cpp
        Orders/Orders.cpp Orders/Orders.h Orders/OrdersDriver.cpp
        CommandProcessor/CommandProcessor.cpp CommandProcessor/CommandProcessor.h CommandProcessor/CommandProcessorDriver.cpp
        Card/CardsDriver.cpp Card/Card.h Card/Card.cpp
        Map/MapDriver.cpp Map/Map.cpp Map/Map.h
        GameEngine/GameEngine.cpp GameEngine/GameEngine.h main.h Card/CardsDriver.h CommandProcessor/CommandProcessorDriver.h GameEngine/GameEngineDriver.h Map/MapDriver.h Player/PLayerDriver.h LoggingObserver/LoggingDriver.cpp Strategies/PlayerStrategies.cpp Strategies/PlayerStrategies.h Strategies/PlayerStrategiesDriver.cpp)
