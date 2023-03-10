#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <list>

#include "board.h"
#include "positionEvaluator.h"

using namespace std;

class node{
public:
    int color;
    string move;
    int position_strength;
    int deep_position_strength;
    board* node_board;

    node* parent;
    list <node*> children;
    
    node(){
        parent = nullptr;
        node_board = nullptr;
    }

    node(board &mother_board, string move, int color, node* parent){
        this->move = move;
        this->parent = parent;
        this->color = color;
        node_board = new board(mother_board);
        node_board->update(move);
        position_strength = positionEvaluator(*node_board);
    }

    void expand(){
        int i = 0;
        if(children.size() == 0){
            list <string> moves = node_board->possibleMoves(color * -1);
            for(auto it = moves.begin(); it != moves.end(); ++it){
                i++;
                node* child_node = new node(*node_board, *it, color * -1, this);
                children.push_back(child_node);
            }
        }else{
            for(auto it = children.begin(); it != children.end(); ++it){
                if(*it != nullptr){
                    (*it)->expand();
                }
            }
        }
    }

    void kill(){
        node* parent = this->parent;
        
        if(parent != nullptr){
            for(auto it = parent->children.begin(); it != parent->children.end(); ++it){
                if(*it == this){
                    parent->children.erase(it);
                }
            }
        }

        for(auto it = children.begin(); it != children.end(); ++it){
            (*it)->kill();
        }

        delete this;
    }
};

#endif
