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
        //the hardest part
    }

    void move(string move, int color){
        board.update(move, color);
        //also implement to make that node the new root of the tree
    }
    
};

#endif
