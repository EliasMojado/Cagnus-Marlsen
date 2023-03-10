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

    tree(){

    }

    tree(board mother_board, int depth){
        // node* head = new node(mother_board, "", -1, nullptr);
        head = new node(mother_board, "", -1, nullptr);
        this->depth = depth;
    }

    void start (){
        cout << "tree is now expanding..." << endl;
        for(int i = 0; i <depth; i++){
            head->expand();
        }
    }


};

#endif