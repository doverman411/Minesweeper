#ifndef BOARD_H
#define BOARD_H 

#include "location.h"
#include "tile.h"
#include <functional>
#include <string>
#include <vector>

class Board
{
public: 
  bool running, won;
  Board(int numRows, int numColumns, int numMines); 

  void placeMines(const Location & safeSpace);
  bool sweep(const Location & location);
  bool chord(const Location & location);
  void flag(const Location & location);
  bool isValidLocation(const Location & location) const;
  
  std::string tileString(const Location & location) const; 

  ~Board();
  
  friend std::ostream& operator<<(std::ostream& out, const Board& boardObj);
  

private:
  Tile** board; 
  int numRows, numColumns, numMines, flagsLeft, numHiddenTiles;
  bool setup; 

  Tile& tileAt(const Location & Location) const;
  std::vector<Tile*> tilesAround(const Location & location) const;
  std::vector<Location> locationsAround(const Location & location) const;
  int numAround(const Location& location, const std::function<bool(const Tile&)>& fn) const; 
  char inside(const Tile& tile) const;
  bool canChord(const Location & location) const;
};

std::string numSpaces(int num);

#endif 
