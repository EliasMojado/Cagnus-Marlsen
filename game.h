#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <list>
#include "board.h"
using namespace std;

class game {
private:
    board board;
public:
    game(){
        board.initialize();
        //initialize the board i guess
    }

    game (string position){
        board.initialize(position);
    }

    

    int positionEvaluator(){

    }

    void move(string move){
        board.update(move);
    }
    
};

#endif
