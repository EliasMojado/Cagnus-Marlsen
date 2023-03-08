#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <list>
#include "board.h"
#include "positionEvaluator.cpp"

using namespace std;

class game {
public:
    board board;
    game(){
        board.initialize();
        //initialize the board i guess
    }

    game (string position){
        board.initialize(position);
    }

    void start(){
        cout << positionEvaluator(board) << endl;
    }

    void move(string move, int color){
        board.update(move, color);
        //also implement to make that node the new root of the tree
    }
    
};

#endif
