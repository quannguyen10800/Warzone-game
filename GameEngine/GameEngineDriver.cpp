//
// Created by Kai Tran on 2021-09-28
//

#include <iostream>
#include <string.h>
#include "GameEngine.h"

using namespace std;

int main(){

    GameEngine ge;

    do{
        cout<<"Current Game status = "<<ge.getState()<<endl;
        string command;
        cout<<"Please Enter a command = ";
        cin>>command;
        if (ge.transition(command.c_str()) == false){
            cout<<"Invalid command!!!"<<endl;
        }


    }while (ge.getEndStatus() == 0);



}

// g++ GameEngine.cpp GameEngineDriver.cpp -o main
// ./main