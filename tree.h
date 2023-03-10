#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <list>

#include "node.h"
#include "board.h"

class tree{
public:
    node* head;
    int depth;
    int turn;

    tree(){

    }

    tree(board mother_board, int depth){
        // node* head = new node(mother_board, "", -1, nullptr);
        turn = -1;
        head = new node(mother_board, "", turn, nullptr);
        this->depth = depth;
    }

    void start (){
        cout << "tree is now expanding..." << endl;
        for(int i = 0; i < depth; i++){
            head->expand();
        }
        
        int maxValue;
        node* maxNode = nullptr;

        if(turn = -1){
            maxValue = -1000000;
        }else{
            maxValue = 1000000;
        }

        for (node* child : head->children) {
            if (child->position_strength > maxValue) {
                maxNode = child;
                maxValue = child->position_strength;
            }
        }

        cout << maxNode->move << " " << maxValue;
    }

};

#endif