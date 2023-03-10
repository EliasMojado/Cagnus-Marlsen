#ifndef POSITIONEVAL_H
#define POSITIONEVAL_H

#include <iostream>
#include <string>
#include <list>
#include <cmath>

#include "board.h"
#include "piece.h"

using namespace std;

int positionEvaluator(board &board_state){
    int bScore = 0;
    int wScore = 0;
    
    //constants
    int defending = 3;
    int attacking = 3;
    int moves = 7;

    /*BLACK PIECES*/

    for(int i = 0; i < 16; i++){
        piece* black = board_state.black[i];
        char type;
        int x;
        int y;

        if(black->isAlive == true){
            char type = black->type;
            int x = black->x;
            int y = black ->y;
        }

        //raw piece value
        bScore += black->value;
        
        if(type == 'p' && black->isAlive == true){
            //if a pawn is advanced
            bScore -= pow(x-1, 3);

            //center pawns are more valuable
            if(y == 4 || y == 3){
                bScore -= 30 + (x-1)*15;
            }else if (y == 5 || y == 2){
                bScore -= 20 + (x-1)*10;
            }else{
                bScore -= 10 + (x-1)*5;
            }

            //doubled pawns punishment && passed pawn advantage
            bool isPassedPawn = true;
            for(int xTemp = x; xTemp < 7; ++xTemp){
                piece* front = board_state.tiles[xTemp][y].tilePiece;
                if(front != nullptr && front->type == 'p' && front->color == -1){
                    bScore += 30;
                }

                if(y > 0){
                    piece* left = board_state.tiles[xTemp + 1][y-1].tilePiece;
                    if(left != nullptr && left->type == 'p' && left->color == 1){
                        isPassedPawn = false;
                    }
                }

                if(y < 7){
                    piece* right = board_state.tiles[xTemp + 1][y+1].tilePiece;
                    if(right != nullptr && right->type == 'p' && right->color == 1){
                        isPassedPawn = false;
                    }
                }
            }
            
            if(isPassedPawn){
                bScore -= 50;
            }
        }else if ((type == 'R'|| type == 'Q')&& black->isAlive == true){
            int possible_moves = 0;
            int tempY = y;
            int tempX = x;
            //traverse to the left
            while(tempY > 0){
                tempY--;
                piece* left = board_state.tiles[tempX][tempY].tilePiece;
                if(left == nullptr){
                    possible_moves++;
                }else if (left != nullptr){
                    if(black->color + left->color != 0){
                        bScore -= defending; 
                        break;
                    }else if(black->color + left->color == 0){
                        bScore -= attacking;
                        break;
                    }
                }
            }

            //traverse to the right
            tempY = y;
            while(tempY < 7){
                tempY++;
                piece* right = board_state.tiles[tempX][tempY].tilePiece;
                if(right == nullptr){
                    possible_moves++;
                }else if(right != nullptr){
                    if(black->color + right->color != 0){
                        bScore -= defending;
                        break;
                    }else if (black->color + right->color == 0){
                        bScore -= attacking;
                        break;
                    }
                }
            }

            //traverse up
            while(tempX > 0){
                tempX--;
                piece* up = board_state.tiles[tempX][y].tilePiece;
                if(up == nullptr){
                    possible_moves++;
                }else if(up != nullptr){
                    if(black->color + up->color != 0){
                        bScore -= defending;
                        break;
                    }else if (black->color + up->color == 0){
                        bScore -= attacking;
                        break;
                    }
                }
            }

            //traverse down
            tempX = x;
            while(tempX < 7){
                tempX++;
                piece* down = board_state.tiles[tempX][y].tilePiece;
                if(down == nullptr){
                    possible_moves++;
                }else if(down != nullptr){
                    if(black->color + down->color != 0){
                        bScore -= defending;
                        break;
                    }else if (black->color + down->color == 0){
                        bScore -= attacking;
                        break;
                    }
                }
            }

            bScore -= possible_moves * moves;
        } else if (type == 'N' && black->isAlive == true){
            int possible_moves = 0;
            piece* temp;

            if(x > 1 && y > 0){
                possible_moves++;
                temp = board_state.tiles[x-2][y-1].tilePiece;
                if(temp != nullptr){
                    if(temp->color == 1){
                        bScore -= attacking;
                    }else{
                        bScore -= defending;
                    }
                }
            }

            if(x > 0 && y > 1){
                possible_moves++;
                temp = board_state.tiles[x-1][y-2].tilePiece;
                if(temp != nullptr){
                    if(temp->color == 1){
                        bScore -= attacking;
                    }else{
                        bScore -= defending;
                    }
                }
            }

            if(x < 7 && y > 1){
                possible_moves++;
                temp = board_state.tiles[x + 1][y-2].tilePiece;
                if(temp != nullptr){
                    if(temp->color == 1){
                        bScore -= attacking;
                    }else{
                        bScore -= defending;
                    }
                }
            }

            if(x < 6 && y > 0){
                possible_moves++;
                temp = board_state.tiles[x+2][y-1].tilePiece;
                if(temp != nullptr){
                    if(temp->color == 1){
                        bScore -= attacking;
                    }else{
                        bScore -= defending;
                    }
                }
            }

            if(x > 1 && y < 7){
                possible_moves++;
                temp = board_state.tiles[x-2][y+1].tilePiece;
                if(temp != nullptr){
                    if(temp->color == 1){
                        bScore -= attacking;
                    }else{
                        bScore -= defending;
                    }
                }
            }

            if(x > 0 && y < 6){
                possible_moves++;
                temp = board_state.tiles[x-1][y+2].tilePiece;
                if(temp != nullptr){
                    if(temp->color == 1){
                        bScore -= attacking;
                    }else{
                        bScore -= defending;
                    }
                }
            }

            if(x < 7 && y < 6){
                possible_moves++;
                temp = board_state.tiles[x + 1][y+2].tilePiece;
                if(temp != nullptr){
                    if(temp->color == 1){
                        bScore -= attacking;
                    }else{
                        bScore -= defending;
                    }
                }
            }

            if(x < 6 && y < 7){
                possible_moves++;
                temp = board_state.tiles[x+2][y+1].tilePiece;
                if(temp != nullptr){
                    if(temp->color == 1){
                        bScore -= attacking;
                    }else{
                        bScore -= defending;
                    }
                }
            }

            bScore -= possible_moves * moves;
        }else if ((type == 'Q' || type == 'B') && black->isAlive == true){
            int possible_moves = 0;
            int tempY = y;
            int tempX = x;

             //traverse upper right
            while(tempX > 0 && tempY < 7){
                tempX--;
                tempY++;
                piece* temp = board_state.tiles[tempX][tempY].tilePiece;
                if(temp == nullptr){
                    possible_moves++;
                }else if (temp->color == -1){
                    bScore -= defending;
                    break;
                }else if (temp->color == 1){
                    bScore -= attacking;
                    break;
                }
            }

            //traverse lower right
            tempY = y;
            tempX = x;
            while(tempX < 7 && tempY < 7){
                tempX++;
                tempY++;
                piece* temp = board_state.tiles[tempX][tempY].tilePiece;
                if(temp == nullptr){
                    possible_moves++;
                }else if (temp->color == -1){
                    bScore -= defending;
                    break;
                }else if (temp->color == 1){
                    bScore -= attacking;
                    break;
                }
            }

            //traverse upper left
            tempX = x;
            tempY = y;
            while(tempX > 0 && tempY > 0){
                tempX--;
                tempY--;
                piece* temp = board_state.tiles[tempX][tempY].tilePiece;
                if(temp == nullptr){
                    possible_moves++;
                }else if (temp->color == -1){
                    bScore -= defending;
                    break;
                }else if (temp->color == 1){
                    bScore -= attacking;
                    break;
                }
            }

            //traverse lower left
            tempX = x;
            tempY = y;
            while(tempX < 7 && tempY > 0){
                tempX++;
                tempY--;
                piece* temp = board_state.tiles[tempX][tempY].tilePiece;
                if(temp == nullptr){
                    possible_moves++;
                }else if (temp->color == -1){
                    bScore -= defending;
                    break;
                }else if (temp->color == 1){
                    bScore -= attacking;
                    break;
                }
            }

            bScore -= possible_moves * moves;
        }
    }

    /*WHITE PIECES*/

    for(int i = 0; i < 16; i++){
        piece* white = board_state.white[i];
        char type = white->type;
        int x = white->x;
        int y = white ->y;

        //raw piece value
        wScore += white->value;
        
        if(type == 'p' && white->isAlive == true){
            //if a pawn is advanced
            wScore += pow(6-x, 3);

            //center pawns are more valuable
            if(y == 4 || y == 3){
                wScore += 30 + (6-x)*10;
            }else if (y == 5 || y == 2){
                wScore += 20 + (6-x)*10;
            }else{
                wScore += 10 + (6-x)*5;
            }

            //doubled pawns punishment && passed pawn advantage
            bool isPassedPawn = true;
            for(int xTemp = x; xTemp > 0; --xTemp){
                piece* front = board_state.tiles[xTemp][y].tilePiece;
                if(front != nullptr && front->type == 'p' && front->color == 1){
                    wScore -= 30;
                }

                if(y > 0){
                    piece* left = board_state.tiles[xTemp - 1][y-1].tilePiece;
                    if(left != nullptr && left->type == 'p' && left->color == -1){
                        isPassedPawn = false;
                    }
                }

                if(y < 7){
                    piece* right = board_state.tiles[xTemp - 1][y+1].tilePiece;
                    if(right != nullptr && right->type == 'p' && right->color == -1){
                        isPassedPawn = false;
                    }
                }
            }

            //if pawn is connected
            
            if(isPassedPawn){
                wScore += 50;
            }
        }else if ((type == 'R'|| type == 'Q') && white->isAlive == true){
            int possible_moves = 0;
            int tempY = y;
            int tempX = x;
            //traverse to the left
            while(tempY > 0){
                tempY--;
                piece* left = board_state.tiles[tempX][tempY].tilePiece;
                if(left == nullptr){
                    possible_moves++;
                }else if (left != nullptr){
                    if(white->color + left->color != 0){
                        wScore += defending; 
                        break;
                    }else if(white->color + left->color == 0){
                        wScore -= attacking;
                        break;
                    }
                }
            }

            //traverse to the right
            tempY = y;
            while(tempY < 7){
                tempY++;
                piece* right = board_state.tiles[tempX][tempY].tilePiece;
                if(right == nullptr){
                    possible_moves++;
                }else if(right != nullptr){
                    if(white->color + right->color != 0){
                        wScore += defending;
                        break;
                    }else if (white->color + right->color == 0){
                        wScore -= attacking;
                        break;
                    }
                }
            }

            //traverse up
            while(tempX > 0){
                tempX--;
                piece* up = board_state.tiles[tempX][y].tilePiece;
                if(up == nullptr){
                    possible_moves++;
                }else if(up != nullptr){
                    if(white->color + up->color != 0){
                        wScore += defending;
                        break;
                    }else if (white->color + up->color == 0){
                        wScore -= attacking;
                        break;
                    }
                }
            }

            //traverse down
            tempX = x;
            while(tempX < 7){
                tempX++;
                piece* down = board_state.tiles[tempX][y].tilePiece;
                if(down == nullptr){
                    possible_moves++;
                }else if(down != nullptr){
                    if(white->color + down->color != 0){
                        wScore += defending;
                        break;
                    }else if (white->color + down->color == 0){
                        wScore -= attacking;
                        break;
                    }
                }
            }

            wScore += possible_moves * moves;
        }else if (type == 'N' && white->isAlive == true){
            int possible_moves = 0;
            piece* temp;

            if(x > 1 && y > 0){
                possible_moves++;
                temp = board_state.tiles[x-2][y-1].tilePiece;
                if(temp != nullptr){
                    if(temp->color == -1){
                        wScore += attacking;
                    }else{
                        wScore += defending;
                    }
                }
            }

            if(x > 0 && y > 1){
                possible_moves++;
                temp = board_state.tiles[x-1][y-2].tilePiece;
                if(temp != nullptr){
                    if(temp->color == -1){
                        wScore += attacking;
                    }else{
                        wScore += defending;
                    }
                }
            }

            if(x < 7 && y > 1){
                possible_moves++;
                temp = board_state.tiles[x + 1][y-2].tilePiece;
                if(temp != nullptr){
                    if(temp->color == -1){
                        wScore += attacking;
                    }else{
                        wScore += defending;
                    }
                }
            }

            if(x < 6 && y > 0){
                possible_moves++;
                temp = board_state.tiles[x+2][y-1].tilePiece;
                if(temp != nullptr){
                    if(temp->color == -1){
                        wScore += attacking;
                    }else{
                        wScore += defending;
                    }
                }
            }

            if(x > 1 && y < 7){
                possible_moves++;
                temp = board_state.tiles[x-2][y+1].tilePiece;
                if(temp != nullptr){
                    if(temp->color == -1){
                        wScore += attacking;
                    }else{
                        wScore += defending;
                    }
                }
            }

            if(x > 0 && y < 6){
                possible_moves++;
                temp = board_state.tiles[x-1][y+2].tilePiece;
                if(temp != nullptr){
                    if(temp->color == -1){
                        wScore += attacking;
                    }else{
                        wScore += defending;
                    }
                }
            }

            if(x < 7 && y < 6){
                possible_moves++;
                temp = board_state.tiles[x + 1][y+2].tilePiece;
                if(temp != nullptr){
                    if(temp->color == -1){
                        wScore += attacking;
                    }else{
                        wScore += defending;
                    }
                }
            }

            if(x < 6 && y < 7){
                possible_moves++;
                temp = board_state.tiles[x+2][y+1].tilePiece;
                if(temp != nullptr){
                    if(temp->color == -1){
                        wScore += attacking;
                    }else{
                        wScore += defending;
                    }
                }
            }

            wScore += possible_moves * moves;
        }else if ((type == 'Q' || type == 'B') && white->isAlive == true){
            int possible_moves = 0;
            int tempY = y;
            int tempX = x;

             //traverse upper right
            while(tempX > 0 && tempY < 7){
                tempX--;
                tempY++;
                piece* temp = board_state.tiles[tempX][tempY].tilePiece;
                if(temp == nullptr){
                    possible_moves++;
                }else if (temp->color == 1){
                    wScore += defending;
                    break;
                }else if (temp->color == -1){
                    wScore += attacking;
                    break;
                }
            }

            //traverse lower right
            tempY = y;
            tempX = x;
            while(tempX < 7 && tempY < 7){
                tempX++;
                tempY++;
                piece* temp = board_state.tiles[tempX][tempY].tilePiece;
                if(temp == nullptr){
                    possible_moves++;
                }else if (temp->color == 1){
                    wScore += defending;
                    break;
                }else if (temp->color == -1){
                    wScore += attacking;
                    break;
                }
            }

            //traverse upper left
            tempX = x;
            tempY = y;
            while(tempX > 0 && tempY > 0){
                tempX--;
                tempY--;
                piece* temp = board_state.tiles[tempX][tempY].tilePiece;
                if(temp == nullptr){
                    possible_moves++;
                }else if (temp->color == 1){
                    wScore += defending;
                    break;
                }else if (temp->color == -1){
                    wScore += attacking;
                    break;
                }
            }

            //traverse lower left
            tempX = x;
            tempY = y;
            while(tempX < 7 && tempY > 0){
                tempX++;
                tempY--;
                piece* temp = board_state.tiles[tempX][tempY].tilePiece;
                if(temp == nullptr){
                    possible_moves++;
                }else if (temp->color == 1){
                    wScore += defending;
                    break;
                }else if (temp->color == -1){
                    wScore += attacking;
                    break;
                }
            }

            wScore += possible_moves * moves;
        }
    }

    

    return bScore + wScore;
}

#endif