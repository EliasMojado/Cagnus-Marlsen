#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <list>
#include <cmath>

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
        deep_position_strength = evaluationProcessor(position_strength);
    }

    float evaluationProcessor(int position_strength){
        float multiplier = 1;
        int strength = abs(position_strength);
        if(strength > 5000){
            multiplier = 0.01; 
        }else if(strength > 1500){
            multiplier = 0.1;
        }else if(strength > 1000){
            multiplier = 0.2;
        }else if (strength > 750){
            multiplier = 0.3;
        }else if (strength > 500){
            multiplier = 0.4;
        }else if (strength > 250){
            multiplier = 0.6;
        }else if (strength > 100){
            multiplier = 0.8;
        }

        if(position_strength > 0){
            return position_strength * multiplier;
        }else{
            return position_strength * multiplier * -1;
        }
    }

    void expand(){
        if(color == 1){
            if(parent != nullptr && parent->parent != nullptr){
                if(parent->parent->deep_position_strength > 2 * position_strength){
                    return;
                }
            }
        }else{
            if(parent != nullptr && parent->parent != nullptr){
                if(parent->parent->deep_position_strength < 2 * position_strength){
                    return;
                }
            }
        }

        if(children.size() == 0){
            list <string> moves = node_board->possibleMoves(color * -1);
            for(auto it = moves.begin(); it != moves.end(); ++it){
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
        for(auto it = children.begin(); it != children.end(); ++it){
            (*it)->kill();
        }

        delete this;
    }
};

#endif
