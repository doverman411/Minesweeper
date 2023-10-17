#ifndef TILE_H
#define TILE_H

#include <iosfwd>

class Tile
{
public:
  bool hasMine, isSwept, hasFlag;
  int number;

  Tile();

  bool canSweep() const;
};

#endif 
