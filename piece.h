#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
using namespace std;

class piece{
public:
    char type;
    int color, value, x, y;
    
    piece(char type, int color, int x, int y){
        this->type = type;
        this->color = color;
        this->x = x;
        this->y = y;

        if(type == 'p'){
            value = 100 * color;
        }else if(type == 'R'){
            value = 500 * color;
        }else if(type == 'N'|| type == 'B'){
            value = 300 * color;
        }else if(type == 'Q'){
            value = 900 * color;
        }else if(type == 'K'){
            value = 10000 * color;
        }
    }
};

#endif
