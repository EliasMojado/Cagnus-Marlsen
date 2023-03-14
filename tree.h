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

    ~tree(){
        head->kill();
    }

    tree(board mother_board, int depth){
        turn = mother_board.turn;
        head = new node(mother_board, "", turn, nullptr);
        this->depth = depth;
    }

    int run (){
        expand(head, depth);
        return branch_strength(head, 0);
    }

    void expand(node* selected_node, int depth){
        for(int i = 0; i < depth; i++){
            selected_node->expand();
        }
    }

    int branch_strength(node* selected_node, int num_nodes){
        list <node*> children = selected_node->children;
        int num = children.size() + 1;
        int total; 
        if(num_nodes == 0){
            total = 0;
        }else{
            total = selected_node->deep_position_strength;
        }

        if(num != 0){
            for (auto it = children.begin(); it != children.end(); ++it) {
                total += branch_strength(*it, num_nodes + 5);
            }
        }
        return total/num + (num_nodes * selected_node->color);
    }
};

#endif