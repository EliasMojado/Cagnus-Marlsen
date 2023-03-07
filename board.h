#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <list>

#include "tile.h"
#include "piece.h"

using namespace std;

class board {
public:
    tile tiles[8][8];
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
                this->tiles[x][y].update(this->white[i]);
            }

            if(origin.black[i]->isAlive){
                char type = origin.black[i]->type;
                int x = origin.black[i]->x;
                int y = origin.black[i]->y;

                this->black[i] = new piece(type, -1, x, y);
                this->tiles[x][y].update(this->black[i]);
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
        char piece1 = move[0];
        int ySource = move[1] - 'a';
        int xSource = (move[2] - '0' - 8 ) * -1;
        char mode = move[3];
        char piece2 = move[4];
        int yDestination = move[5] - 'a';
        int xDestination = (move[6] - '0' - 8 ) * -1;


        piece* movingPiece = tiles[xSource][ySource].tilePiece;
        tiles[xSource][ySource].update(nullptr);
        if(mode == '-'){
            movingPiece->update(true, xDestination, yDestination);
            tiles[xDestination][yDestination].update(movingPiece);
        }else if (mode == 'x'){
            piece* takenPiece = tiles[xDestination][yDestination].tilePiece;
            takenPiece->update(false, xDestination, yDestination);
            movingPiece->update(true, xDestination, yDestination);
            tiles[xDestination][yDestination].update(movingPiece);
        }

        //castle & en passant needs to be implemented
    }

    void initialize(){
        for(int y = 0; y < 8; y++){
            white[y] = new piece('p', 1, 6, y);
            tiles[6][7].update(white[y]);

            black[y] = new piece('p', -1, 1, y);
            tiles[1][y].update(black[y]);
        }

        white[8] = new piece('R', 1, 7, 0);
        tiles[7][0].update(white[8]);
        white[9] = new piece('N', 1, 7, 1);
        tiles[7][1].update(white[9]);
        white[10] = new piece('B', 1, 7, 2);
        tiles[7][2].update(white[10]);
        white[11] = new piece('Q', 1, 7, 3);
        tiles[7][3].update(white[11]);
        white[12] = new piece('K', 1, 7, 4);
        tiles[7][4].update(white[12]);
        white[13] = new piece('B', 1, 7, 5);
        tiles[7][5].update(white[13]);
        white[14] = new piece('N', 1, 7, 6);
        tiles[7][6].update(white[14]);
        white[15] = new piece('R', 1, 7, 7);
        tiles[7][7].update(white[15]);

        black[8] = new piece('R', -1, 0, 0);
        tiles[0][0].update(black[8]);
        black[9] = new piece('N', -1, 0, 1);
        tiles[0][1].update(black[9]);
        black[10] = new piece('B', -1, 0, 2);
        tiles[0][2].update(black[10]);
        black[11] = new piece('Q', -1, 0, 3);
        tiles[0][3].update(black[11]);
        black[12] = new piece('K', -1, 0, 4);
        tiles[0][4].update(black[12]);
        black[13] = new piece('B', -1, 0, 5);
        tiles[0][5].update(black[13]);
        black[14] = new piece('N', -1, 0, 6);
        tiles[0][6].update(black[14]);
        black[15] = new piece('R', -1, 0, 7);
        tiles[0][7].update(black[15]);
    }

    void initialize(string position){

    }

    list <string> possibleMoves(int color){
        list <string> moves;
        for(int i = 0; i < 16; i++){
            char type;
            int x, y;

            if(color == 1){
                type = white[i]->type;
                x = white[i]->x;
                y = white[i]->y;
            }else{
                type = black[i]->type;
                x = black[i]->x;
                y = black[i]->y;
            }

            // if pawn
            if(type == 'p'){

                //promotion

                //forward
                if(color == 1){
                    piece* front = tiles[x-1][y].tilePiece;
                    if(front == nullptr){
                        moves.push_back("p" + to_string('a' + y) + to_string('8' - x) + "-" 
                        + "p" + to_string('a' + y) + to_string('8' - x + 1));
                    }
                }else{
                    piece* front = tiles[x+1][y].tilePiece;
                    if(front == nullptr){
                        moves.push_back("p" + to_string('a' + y) + to_string('8' - x) + "-" 
                        + "p" + to_string('a' + y) + to_string('8' - x - 1));
                    }
                }

                //capture
                if(y > 0){
                    piece* left;
                    if(color == 1){
                        left = tiles[x-1][y-1].tilePiece;
                        if(left != nullptr && left->color == -1){
                            moves.push_back("p" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(left->type) + to_string('a' + y - 1) + to_string('8' - x + 1));
                        }
                    }else{
                        left = tiles[x+1][y-1].tilePiece;
                        if(left != nullptr && left->color == 1){
                            moves.push_back("p" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(left->type) + to_string('a' + y - 1) + to_string('8' - x - 1));
                        }
                    }

                }

                if(y < 7){
                    piece* right;
                    if(color == 1){
                        right = tiles[x-1][y+1].tilePiece;
                        if(left != nullptr && right->color == -1){
                            moves.push_back("p" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(right->type) + to_string('a' + y + 1) + to_string('8' - x + 1));
                        }
                    }else{
                        right = tiles[x+1][y+1].tilePiece;
                        if(left != nullptr && right->color == 1){
                            moves.push_back("p" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(right->type) + to_string('a' + y + 1) + to_string('8' - x - 1));
                        }
                    }

                }
                
                // en passant

            }else if (type == 'R'){
                //traverse to the left
                int tempY = y;
                while(tempY > 0){
                    tempY--;
                    piece* left;
                    left = tiles[x][tempY].tilePiece;
                    if(left == nullptr){
                        moves.push_back("R" + to_string('a' + y) + to_string('8'- x) + "-"
                        + "R" + to_string('a' + tempY) + to_string('8'- x));
                    }else if(left != nullptr){
                        if(color + left->color != 0){
                            break;
                        }else if (color + left->color == 0){
                            moves.push_back("R" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(left->type) + to_string('a' + tempY) + to_string('8' - x));
                            break;
                        }
                    }
                }

                //traverse to the right
                tempY = y;
                while(tempY < 7){
                    tempY++;
                    piece* right;
                    right = tiles[x][tempY].tilePiece;
                    if(right == nullptr){
                        moves.push_back("R" + to_string('a' + y) + to_string('8'- x) + "-"
                        + "R" + to_string('a' + tempY) + to_string('8'- x));
                    }else if(right != nullptr){
                        if(color + right->color != 0){
                            break;
                        }else if (color + right->color == 0){
                            moves.push_back("R" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(right->type) + to_string('a' + tempY) + to_string('8' - x));
                            break;
                        }
                    }
                }
                
                //traverse up
                int tempX = x;
                while(tempX > 0){
                    tempX--;
                    piece* up;
                    up = tiles[tempX][y].tilePiece;
                    if(up == nullptr){
                        moves.push_back("R" + to_string('a' + y) + to_string('8'- x) + "-"
                        + "R" + to_string('a' + y) + to_string('8'- tempX));
                    }else if(up != nullptr){
                        if(color + up->color != 0){
                            break;
                        }else if (color + up->color == 0){
                            moves.push_back("R" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(up->type) + to_string('a' + y) + to_string('8' - tempX));
                            break;
                        }
                    }
                }

                //traverse down
                tempX = x;
                while(tempX < 7){
                    tempX++;
                    piece* down;
                    down = tiles[tempX][y].tilePiece;
                    if(down == nullptr){
                        moves.push_back("R" + to_string('a' + y) + to_string('8'- x) + "-"
                        + "R" + to_string('a' + y) + to_string('8'- tempX));
                    }else if(down != nullptr){
                        if(color + down->color != 0){
                            break;
                        }else if (color + down->color == 0){
                            moves.push_back("R" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(down->type) + to_string('a' + y) + to_string('8' - tempX));
                            break;
                        }
                    }
                }
            }else if (type == 'N'){
                piece* temp;

                if(x > 1 && y > 0){
                    temp = tiles[x-2][y-1].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "N" + to_string('a' + y - 1) + to_string('8' - x + 2));
                    }else if (temp != nullptr){
                        if(color + temp->color == 0){
                            moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(temp->type) + to_string('a' + y - 1) + to_string('8' - x + 2));
                        }
                    }
                }

                if(x > 0 && y > 1){
                    temp = tiles[x-1][y-2].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "N" + to_string('a' + y - 2) + to_string('8' - x + 1));
                    }else if (temp != nullptr){
                        if(color + temp->color == 0){
                            moves.push_back("K" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(temp->type) + to_string('a' + y - 2) + to_string('8' - x + 1));
                        }
                    }
                }

                if(x < 7 && y > 1){
                    temp = tiles[x + 1][y-2].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "N" + to_string('a' + y - 2) + to_string('8' - x - 1));
                    }else if (temp != nullptr){
                        if(color + temp->color == 0){
                            moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(temp->type) + to_string('a' + y - 2) + to_string('8' - x - 1));
                        }
                    }
                }

                if(x < 6 && y > 0){
                    temp = tiles[x+2][y-1].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "N" + to_string('a' + y - 1) + to_string('8' - x - 2));
                    }else if (temp != nullptr){
                        if(color + temp->color == 0){
                            moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(temp->type) + to_string('a' + y - 1) + to_string('8' - x - 2));
                        }
                    }
                }

                //

                if(x > 1 && y < 7){
                    temp = tiles[x-2][y+1].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "N" + to_string('a' + y + 1) + to_string('8' - x + 2));
                    }else if (temp != nullptr){
                        if(color + temp->color == 0){
                            moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(temp->type) + to_string('a' + y + 1) + to_string('8' - x + 2));
                        }
                    }
                }

                if(x > 0 && y < 6){
                    temp = tiles[x-1][y+2].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "N" + to_string('a' + y + 2) + to_string('8' - x + 1));
                    }else if (temp != nullptr){
                        if(color + temp->color == 0){
                            moves.push_back("K" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(temp->type) + to_string('a' + y + 2) + to_string('8' - x + 1));
                        }
                    }
                }

                if(x < 7 && y < 6){
                    temp = tiles[x + 1][y+2].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "N" + to_string('a' + y + 2) + to_string('8' - x - 1));
                    }else if (temp != nullptr){
                        if(color + temp->color == 0){
                            moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(temp->type) + to_string('a' + y + 2) + to_string('8' - x - 1));
                        }
                    }
                }

                if(x < 6 && y < 7){
                    temp = tiles[x+2][y+1].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "N" + to_string('a' + y + 1) + to_string('8' - x - 2));
                    }else if (temp != nullptr){
                        if(color + temp->color == 0){
                            moves.push_back("N" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(temp->type) + to_string('a' + y + 1) + to_string('8' - x - 2));
                        }
                    }
                }
            }else if (type == 'B'){
                int tempY = y;
                int tempX = x;

                //traverse upper right
                while(tempX > 0 && tempY < 7){
                    tempX--;
                    tempY++;
                    piece* temp = tiles[tempX][tempY].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("B" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "B" + to_string('a' + tempY) + to_string('8' - tempX));
                    }else if (temp->color + color != 0){
                        break;
                    }else if (temp->color + color == 0){
                        moves.push_back("B" + to_string('a' + y) + to_string('8' - x) +
                        "x" + to_string(temp->type) + to_string('a' + tempY) + to_string('8' - tempX));
                        break;
                    }
                }

                //traverse lower right
                tempY = y;
                tempX = x;
                while(tempX < 7 && tempY < 7){
                    tempX++;
                    tempY++;
                    piece* temp = tiles[tempX][tempY].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("B" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "B" + to_string('a' + tempY) + to_string('8' - tempX));
                    }else if (temp->color + color != 0){
                        break;
                    }else if (temp->color + color == 0){
                        moves.push_back("B" + to_string('a' + y) + to_string('8' - x) +
                        "x" + to_string(temp->type) + to_string('a' + tempY) + to_string('8' - tempX));
                        break;
                    }
                }

                //traverse upper left
                tempX = x;
                tempY = y;
                while(tempX > 0 && tempY > 0){
                    tempX--;
                    tempY--;
                    piece* temp = tiles[tempX][tempY].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("B" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "B" + to_string('a' + tempY) + to_string('8' - tempX));
                    }else if (temp->color + color != 0){
                        break;
                    }else if (temp->color + color == 0){
                        moves.push_back("B" + to_string('a' + y) + to_string('8' - x) +
                        "x" + to_string(temp->type) + to_string('a' + tempY) + to_string('8' - tempX));
                        break;
                    }
                }

                //traverse lower left
                tempX = x;
                tempY = y;
                while(tempX < 7 && tempY > 0){
                    tempX++;
                    tempY--;
                    piece* temp = tiles[tempX][tempY].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("B" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "B" + to_string('a' + tempY) + to_string('8' - tempX));
                    }else if (temp->color + color != 0){
                        break;
                    }else if (temp->color + color == 0){
                        moves.push_back("B" + to_string('a' + y) + to_string('8' - x) +
                        "x" + to_string(temp->type) + to_string('a' + tempY) + to_string('8' - tempX));
                        break;
                    }
                }
            }else if (type == 'Q'){
                int tempY = y;
                int tempX = x;

                //traverse upper right
                while(tempX > 0 && tempY < 7){
                    tempX--;
                    tempY++;
                    piece* temp = tiles[tempX][tempY].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "Q" + to_string('a' + tempY) + to_string('8' - tempX));
                    }else if (temp->color + color != 0){
                        break;
                    }else if (temp->color + color == 0){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                        "x" + to_string(temp->type) + to_string('a' + tempY) + to_string('8' - tempX));
                        break;
                    }
                }

                //traverse lower right
                tempY = y;
                tempX = x;
                while(tempX < 7 && tempY < 7){
                    tempX++;
                    tempY++;
                    piece* temp = tiles[tempX][tempY].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "Q" + to_string('a' + tempY) + to_string('8' - tempX));
                    }else if (temp->color + color != 0){
                        break;
                    }else if (temp->color + color == 0){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                        "x" + to_string(temp->type) + to_string('a' + tempY) + to_string('8' - tempX));
                        break;
                    }
                }

                //traverse upper left
                tempX = x;
                tempY = y;
                while(tempX > 0 && tempY > 0){
                    tempX--;
                    tempY--;
                    piece* temp = tiles[tempX][tempY].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "Q" + to_string('a' + tempY) + to_string('8' - tempX));
                    }else if (temp->color + color != 0){
                        break;
                    }else if (temp->color + color == 0){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                        "x" + to_string(temp->type) + to_string('a' + tempY) + to_string('8' - tempX));
                        break;
                    }
                }

                //traverse lower left
                tempX = x;
                tempY = y;
                while(tempX < 7 && tempY > 0){
                    tempX++;
                    tempY--;
                    piece* temp = tiles[tempX][tempY].tilePiece;
                    if(temp == nullptr){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                        "-" + "Q" + to_string('a' + tempY) + to_string('8' - tempX));
                    }else if (temp->color + color != 0){
                        break;
                    }else if (temp->color + color == 0){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                        "x" + to_string(temp->type) + to_string('a' + tempY) + to_string('8' - tempX));
                        break;
                    }
                }
                
                //traverse left
                tempY = y;
                while(tempY > 0){
                    tempY--;
                    piece* left;
                    left = tiles[x][tempY].tilePiece;
                    if(left == nullptr){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8'- x) + "-"
                        + "Q" + to_string('a' + tempY) + to_string('8'- x));
                    }else if(left != nullptr){
                        if(color + left->color != 0){
                            break;
                        }else if (color + left->color == 0){
                            moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(left->type) + to_string('a' + tempY) + to_string('8' - x));
                            break;
                        }
                    }
                }

                //traverse to the right
                tempY = y;
                while(tempY < 7){
                    tempY++;
                    piece* right;
                    right = tiles[x][tempY].tilePiece;
                    if(right == nullptr){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8'- x) + "-"
                        + "Q" + to_string('a' + tempY) + to_string('8'- x));
                    }else if(right != nullptr){
                        if(color + right->color != 0){
                            break;
                        }else if (color + right->color == 0){
                            moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(right->type) + to_string('a' + tempY) + to_string('8' - x));
                            break;
                        }
                    }
                }
                
                //traverse up
                tempX = x;
                while(tempX > 0){
                    tempX--;
                    piece* up;
                    up = tiles[tempX][y].tilePiece;
                    if(up == nullptr){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8'- x) + "-"
                        + "Q" + to_string('a' + y) + to_string('8'- tempX));
                    }else if(up != nullptr){
                        if(color + up->color != 0){
                            break;
                        }else if (color + up->color == 0){
                            moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(up->type) + to_string('a' + y) + to_string('8' - tempX));
                            break;
                        }
                    }
                }

                //traverse down
                tempX = x;
                while(tempX < 7){
                    tempX++;
                    piece* down;
                    down = tiles[tempX][y].tilePiece;
                    if(down == nullptr){
                        moves.push_back("Q" + to_string('a' + y) + to_string('8'- x) + "-"
                        + "Q" + to_string('a' + y) + to_string('8'- tempX));
                    }else if(down != nullptr){
                        if(color + down->color != 0){
                            break;
                        }else if (color + down->color == 0){
                            moves.push_back("Q" + to_string('a' + y) + to_string('8' - x) +
                            "x" + to_string(down->type) + to_string('a' + y) + to_string('8' - tempX));
                            break;
                        }
                    }
                }
            }else if (type == 'K'){
                //castle

                //long castle

                //regular moves
                
            }
        }

        return moves;
    }


};

#endif
