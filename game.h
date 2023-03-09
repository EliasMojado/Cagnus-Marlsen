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
        cout << "initial position: " << positionEvaluator(board) << endl;

        board.update("pe2-pe4");
        cout << "after e4: " << positionEvaluator(board) << endl;
        
        board.update("pd7-pd5");
        cout << "after d5: " << positionEvaluator(board) << endl;

        board.update("pe4xpd5");
        cout << "after pxd5: " << positionEvaluator(board) << endl;

        board.update("Qd8xpd5");
        cout <<"after Qxd5: " << positionEvaluator(board) << endl;

        board.update("Ng1-Nf3");
        cout << "after Nf3: " << positionEvaluator(board) << endl;

        // list<string> moves = board.possibleMoves(1);
        // for(auto it = moves.begin(); it != moves.end(); ++it){
        //     cout << *it << endl;
        // }

        cout << sizeof(board) << endl;
    }

    void move(string move){
        board.update(move);
        //also implement to make that node the new root of the tree
    }
    
};

#endif
