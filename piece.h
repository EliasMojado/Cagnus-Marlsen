#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
using namespace std;

class piece{
public:
    char type;
    int color, value, x, y;
    bool isAlive;

    piece(){
        isAlive = false;
        int value = 0;
    }
    
    piece(char type, int color, int x, int y){
        isAlive = true;
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

    void update(bool isAlive, int x, int y){
        this->isAlive = isAlive;
        this->x = x;
        this->y = y;
        if(!isAlive){
            value = 0;
        }
    }
};

#endif
