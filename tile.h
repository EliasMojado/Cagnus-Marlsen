#ifndef TILE_H
#define TILE_H

#include <string>
#include "piece.h"

class tile{
public:
    piece* tilePiece;

    tile(){
        this->tilePiece = nullptr;
    }

    void update(piece* occupyingPiece){
        this->tilePiece = occupyingPiece;
    }
};


#endif