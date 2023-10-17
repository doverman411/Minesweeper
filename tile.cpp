#include "tile.h"
#include <iostream>

Tile::Tile() : hasMine{false}, isSwept{false}, hasFlag{false}, number{0} {}
  
bool Tile::canSweep() const
{
  return !hasFlag && !isSwept;
}

std::ostream& operator<<(std::ostream& out, const Tile& tileObj)
{
    char first = !tileObj.isSwept ? '[' : ' ';
    char last = !tileObj.isSwept ? ']' : ' ';

    return std::string("") + first + inside(tileObj) + last;
    return out;
}
