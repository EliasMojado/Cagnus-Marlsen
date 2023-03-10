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
    int min_depth;
    int max_depth;
    int turn;
    float sieve_factor;
    int current_depth;

    tree(){

    }

    tree(board mother_board, int min_depth, int max_depth, int sieve_factor){
        turn = -1;
        head = new node(mother_board, "", turn, nullptr);
        this->min_depth = min_depth;
        this->max_depth = max_depth;
        this->sieve_factor = sieve_factor;
        current_depth = 0;
    }

    void start() {
        expand(head, min_depth);

        int num = 0;
        cout << "branch strength: " << branch_strength(head, num) << endl;

        sort(head, turn);

        num = 0;
        for (auto it = head->children.begin(); it != head->children.end() && num < 5; ++it) {
            cout << (*it)->move << " " << (*it)->position_strength << " " << (*it)->deep_position_strength << endl;
            num++;
        }
    }


    void run (){
        
    }

    void expand(node* selected_node, int depth){
        for(int i = 0; i < depth; i++){
            selected_node->expand();
            current_depth++;
        }
    }

    void prune(node* selected_node, float sieve_factor) {
        int prune = selected_node->children.size() * sieve_factor;
        sort(selected_node, selected_node->color);
        list <node*> nodes = selected_node->children; 
        for(auto it = nodes.begin(); it != nodes.end() && prune > 0; ++it){
            (*it)->killSucceeding();
            --prune;
        }
    }


    void sort(node* selected_node, int turn) {
        if (selected_node->children.empty()) {
            return;
        }
        if (turn == 1) {
            selected_node->children.sort([this](node* a, node* b) {
                int num_nodes_a = 0, num_nodes_b = 0;
                double branch_strength_a = branch_strength(a, num_nodes_a);
                double branch_strength_b = branch_strength(b, num_nodes_b);
                return branch_strength_a < branch_strength_b;
            });
        } else if (turn == -1) {
            selected_node->children.sort([this](node* a, node* b) {
                int num_nodes_a = 0, num_nodes_b = 0;
                double branch_strength_a = branch_strength(a, num_nodes_a);
                double branch_strength_b = branch_strength(b, num_nodes_b);
                return branch_strength_a > branch_strength_b;
            });
        }
    }



    // int branch_strength(node* selected_node, int& num_nodes){
    //     list <node*> children = selected_node->children;
    //     double total = selected_node->deep_position_strength;
    //     num_nodes = 1;
    //     for (auto it = children.begin(); it != children.end(); ++it) {
    //         int child_nodes;
    //         total += branch_strength(*it, child_nodes);
    //         num_nodes += child_nodes;
    //     }
    //     return total/num_nodes;
    //     // return selected_node->deep_position_strength;
    // }

    int branch_strength(node* selected_node, int num_nodes){
        list <node*> children = selected_node->children;
        int num = children.size() + 1;
        int total = selected_node->deep_position_strength;
        if(num != 0){
            for (auto it = children.begin(); it != children.end(); ++it) {
                total += branch_strength(*it, num_nodes + 5);
            }
        }
        return total/num + (num_nodes * selected_node->color);
    }

    void update(string move){
        current_depth--;
    }

    list <node*> getTopN(int n) {

    }
};

#endif