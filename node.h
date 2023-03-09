#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <list>

#include "board.h"
#include "positionEvaluator.cpp"

using namespace std;

class node{
public:
    int color;
    int position_strength;
    int deep_position_strength;
    board* node_board;

    node* parent;
    list <node*> children;
    
    node(){

    }

    node(board &mother_board, string move, int color, node* parent){
        this->parent = parent;
        this->color = color;
        node_board = new board(mother_board);
        node_board->update(move);
        position_strength = positionEvaluator(*node_board);
    }

    void expand(){
        list <string> moves = node_board->possibleMoves(color * -1);
        for(auto it = moves.begin(); it != moves.end(); ++it){
            node* child_node = new node(*node_board, *it, color * -1, this);
            children.push_back(child_node);
        }
    }
};

#endif
