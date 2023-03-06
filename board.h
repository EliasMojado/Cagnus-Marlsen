#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <list>

#include "piece.h"
using namespace std;

class board {
public:
    piece* black[16];
    piece* white[16];
    bool bCheck, wCheck, b_sCastle, b_lCastle, w_sCastle, w_lCastle;

    board(){
        bCheck = false;
        wCheck = false;
        b_sCastle = true;
        b_lCastle = true;
        w_sCastle = true;
        w_lCastle = true;
    }

    board(const board &origin){
        bCheck = origin.bCheck;
        wCheck = origin.wCheck;
        b_sCastle = origin.b_sCastle;
        b_lCastle = origin.b_lCastle;
        w_sCastle = origin.w_sCastle;
        w_lCastle = origin.w_lCastle;

        for(int i = 0; i < 16; i++){
            if(origin.white[i]->isAlive){
                char type = origin.white[i]->type;
                int x = origin.white[i]->x;
                int y = origin.white[i]->y;

                this->white[i] = new piece(type, 1, x, y);
            }

            if(origin.black[i]->isAlive){
                char type = origin.black[i]->type;
                int x = origin.black[i]->x;
                int y = origin.black[i]->y;

                this->black[i] = new piece(type, -1, x, y);
            }
        }
    }

    ~board(){
        for(int i = 0; i < 16; i++){
            if(black[i] != nullptr){
                delete black[i];
            }

            if (white[i] != nullptr) {
                delete white[i];
            }
        }
    }

    void update(string move, int color){
        char piece = move[0];
        int ySource = move[1] - 'a';
        int xSource = (move[2] - '0' - 8 ) * -1;
        char mode = move[3];
        char piece2 = move[4];
        int yDestination = move[5] - 'a';
        int xDestination = (move[6] - '0' - 8 ) * -1;

        if(color == 1){
            for(int i = 0; i < 16; i++){
                if(white[i]->type == piece && white[i]->x == xSource && white[i]->y == ySource){
                    if(mode == '-'){
                        white[i]->update(true, xDestination, yDestination);
                    }else if (mode == 'x'){
                        white[i]->update(true, xDestination, yDestination);
                        for(int j = 0; j < 16; j++){
                            if(black[j]->type == piece2 && black[j]->x == xDestination && black[j]->y == yDestination){
                                black[j]->update(false, xDestination, yDestination);
                            }
                        }
                    }
                    //castle needs to be implemented
                    //en passant needs to be implemented too
                    break;
                }
            }
        }else{
            for(int i = 0; i < 16; i++){
                if(black[i]->type == piece && black[i]->x == xSource && black[i]->y == ySource){
                    if(mode == '-'){
                        black[i]->update(true, xDestination, yDestination);
                    }else if (mode == 'x'){
                        black[i]->update(true, xDestination, yDestination);
                        for(int j = 0; j < 16; j++){
                            if(white[j]->type == piece2 && white[j]->x == xDestination && white[j]->y == yDestination){
                                white[j]->update(false, xDestination, yDestination);
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    void initialize(){
        for(int y = 0; y < 8; y++){
            white[y] = new piece('p', 1, 6, y);
            black[y] = new piece('p', -1, 1, y);
        }

        white[8] = new piece('R', 1, 7, 0);
        white[9] = new piece('N', 1, 7, 1);
        white[10] = new piece('B', 1, 7, 2);
        white[11] = new piece('Q', 1, 7, 3);
        white[12] = new piece('K', 1, 7, 4);
        white[13] = new piece('B', 1, 7, 5);
        white[14] = new piece('N', 1, 7, 6);
        white[15] = new piece('R', 1, 7, 7);

        black[8] = new piece('R', -1, 0, 0);
        black[9] = new piece('N', -1, 0, 1);
        black[10] = new piece('B', -1, 0, 2);
        black[11] = new piece('Q', -1, 0, 3);
        black[12] = new piece('K', -1, 0, 4);
        black[13] = new piece('B', -1, 0, 5);
        black[14] = new piece('N', -1, 0, 6);
        black[15] = new piece('R', -1, 0, 7);
    }

    void initialize(string position){

    }

    list <string> possibleMoves(int color){
        list <string> moves;


        return moves;
    }


};

#endif
