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
 
    for(int i = 0; i < 16; i++){
        piece* black = board_state.black[i];
        char type = black->type;
        int x = black->x;
        int y = black ->y;

        //raw piece value
        bScore += black->value;
        
        if(type == 'p'  && black->isAlive == true){
            //if a pawn is advanced
            bScore -= pow(x-1, 3);

            //center pawns are more valuable
            if(y == 4 || y == 3){
                bScore -= 30 + (x-1)*10;
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
        }else if (type == 'R' && black->isAlive == true){
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
                        bScore += left->value / 20; 
                        break;
                    }else if(black->color + left->color == 0){
                        bScore -= left->value / 20;
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
                        bScore += right->value/20;
                        break;
                    }else if (black->color + right->color == 0){
                        bScore -= right ->value/20;
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
                        bScore += up->value/20;
                        break;
                    }else if (black->color + up->color == 0){
                        bScore -= up->value/20;
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
                        bScore += down->value/20;
                        break;
                    }else if (black->color + down->color == 0){
                        bScore -= down->value/20;
                        break;
                    }
                }
            }

            bScore -= possible_moves * 5;
        }
    }

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
            
            if(isPassedPawn){
                wScore += 50;
            }
        }else if (type == 'R' && white->isAlive == true){
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
                        wScore += left->value / 20; 
                        break;
                    }else if(white->color + left->color == 0){
                        wScore -= left->value / 20;
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
                        wScore += right->value/20;
                        break;
                    }else if (white->color + right->color == 0){
                        wScore -= right ->value/20;
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
                        wScore += up->value/20;
                        break;
                    }else if (white->color + up->color == 0){
                        wScore -= up->value/20;
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
                        wScore += down->value/20;
                        break;
                    }else if (white->color + down->color == 0){
                        wScore -= down->value/20;
                        break;
                    }
                }
            }

            wScore += possible_moves * 5;
        }
    }

    

    return bScore + wScore;
}