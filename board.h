#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <list>

#include "piece.h"
using namespace std;

class tile{
public:
    piece* unit;
    int x, y;

    tile();

    tile(int x, int y){
        this->x = x;
        this->y = y;
        this->unit = nullptr;
    }
    
    void update(piece* p){
        this->unit = p;
    }
    
};

class board {
public:
    tile tiles[8][8];

    board(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                tiles[i][j] = tile(i, j);
            }
        }
    }

    void update(string move){
        
    }

    void initialize(){
        for(int y = 0; y < 8; y++){
            piece *whitePawn = new piece('p', 1, 6, y);
            piece *blackPawn = new piece('p', -1, 1, y);

            tiles[6][y].update(whitePawn);
            tiles[1][y].update(blackPawn);
        }

        piece *whiteRook = new piece('R', 1, 7, 0);
        piece *blackRook = new piece('R', -1, 0, 0);
        piece *whiteKnight = new piece('N', 1, 7, 1);
        piece *blackKnight = new piece('N', -1, 0, 1);
        piece *whiteBishop = new piece('B', 1, 7, 2);
        piece *blackBishop = new piece('B', -1, 0, 2);
        piece *whiteQueen = new piece('Q', 1, 7, 3);
        piece *blackQueen = new piece('Q', -1, 0, 3);
        piece *whiteKing = new piece('K', 1, 7, 4);
        piece *blackKing = new piece('K', -1, 0, 4);
        piece *whiteBishop2 = new piece('B', 1, 7, 5);
        piece *blackBishop2 = new piece('B', -1, 0, 5);
        piece *whiteKnight2 = new piece('N', 1, 7, 6);
        piece *blackKnight2 = new piece('N', -1, 0, 6);
        piece *whiteRook2 = new piece('R', 1, 7, 7);
        piece *blackRook2 = new piece('R', -1, 0, 7);

        tiles[7][0].update(whiteRook);
        tiles[0][0].update(blackRook);
        tiles[7][1].update(whiteKnight);
        tiles[0][1].update(blackKnight);
        tiles[7][2].update(whiteBishop);
        tiles[0][2].update(blackBishop);
        tiles[7][3].update(whiteQueen);
        tiles[0][3].update(blackQueen);
        tiles[7][4].update(whiteKing);
        tiles[0][4].update(blackKing);
        tiles[7][5].update(whiteBishop2);
        tiles[0][5].update(blackBishop2);
        tiles[7][6].update(whiteKnight2);
        tiles[0][6].update(blackKnight2);
        tiles[7][7].update(whiteRook2);
        tiles[0][7].update(blackRook2);
    }

    void initialize(string position){

    }

    list <string> possibleMoves(int color){
        list <string> legalMoves;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                char piece = tiles[i][j].unit->type;
                int unitColor = tiles[i][j].unit->color;

                if(color == unitColor){

                }
            }
        }
    }


};

#endif
