#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#include "board.h"
#include "positionEvaluator.h"
#include "tree.h"

using namespace std;

struct boardmove{
    string move;
    int strength;
};

bool cmpStrength(boardmove a, boardmove b){
    return a.strength > b.strength;
}

class game {
public:
    board motherboard;
    vector <boardmove> topMoves;
    
    game(){
        motherboard.initialize();
    }

    game (string position){
        motherboard.initialize(position);
    }

    void start(){
        string move;
        bool hasMoved = true;
        while(true){
            if(hasMoved){
                cout << "thinking..." << endl;
                list <string> moves = motherboard.possibleMoves(motherboard.turn * -1);
                for(auto it = moves.begin(); it != moves.end(); ++it){
                    board possibleBoard = board(motherboard);
                    possibleBoard.update(*it);
                    tree* possibleTree = new tree(possibleBoard, 2);
                    int strength = possibleTree->run();
                    delete possibleTree;

                    boardmove newmove = {*it, strength};
                    topMoves.push_back(newmove);
                }

                sort(topMoves.begin(), topMoves.end(), cmpStrength);

                for (const auto& m : topMoves) {
                    cout << m.move << " " << m.strength << endl;
                }

                hasMoved = false;
            }else{
                cout << "your move: " << endl;
                cin >> move;
                motherboard.update(move);
                topMoves.clear();
                hasMoved = true;
                system("CLS");
            }
        }
    }

};

#endif
