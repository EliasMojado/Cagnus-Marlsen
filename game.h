#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <list>

#include "board.h"
#include "positionEvaluator.h"
#include "tree.h"

using namespace std;

class game {
public:
    tree *game_tree;
    board board;
    
    game(){
        board.initialize();
        game_tree = new tree(board, 4);
    }

    game (string position){
        board.initialize(position);
    }

    void start(){
        game_tree->start();
    }

    void move(string move){
        board.update(move);
        //also implement to make that node the new root of the tree
    }
    
};

#endif
