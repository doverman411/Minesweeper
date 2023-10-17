#include "tile.h"
#include <iostream>

Tile::Tile() : hasMine{false}, isSwept{false}, hasFlag{false}, number{0} {}
  
bool Tile::canSweep() const
{
  return !hasFlag && !isSwept;
}