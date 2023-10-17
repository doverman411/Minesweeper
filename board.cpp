#include "board.h"
#include "random.h"
#include <iostream>

Board::Board(int numRows, int numColumns, int numMines) 
  : numRows{numRows}, numColumns{numColumns}, numMines(numMines), flagsLeft{numMines}, running{true}, won{false}, numHiddenTiles{numRows * numColumns}, setup{false}
{
  // Initializing board with empty tiles 
  board = new Tile*[numRows];
  for(int i{0}; i < numRows; ++i)
  {
    board[i] = new Tile[numColumns];
    for(int j{0}; j < numColumns; ++j)
      board[i][j] = Tile();
  }
}

void Board::placeMines(const Location & safeSpace)
{
  // Getting a list of all locations that are on the board and that isn't the safespace
  std::vector<Location> locations;
  int length = 0;
  for(int r = 0; r < numRows; ++r)
  {
    for(int c = 0; c < numColumns; ++c)
    {
      if (!(r == safeSpace.row && c == safeSpace.column))
      {
        locations.push_back( Location(r,c) );
        ++length;
      }
    }
  }
  //placing mines randomly 
  for(int i = 0; i < numMines; ++i)
  {
    int randint = randInt(0, length--);
    const Location randomLocation{ locations[randint] };
    locations.erase(locations.begin() + randint);

    tileAt(randomLocation).hasMine = true;
    std::vector<Tile*> surroundingTiles( tilesAround(randomLocation) );
    for (Tile *t : surroundingTiles)
      ++t->number;

    setup = true;
  }
}

bool Board::sweep(const Location & location)
{
  if(!setup)
    placeMines(location);
  
  Tile &tile(tileAt(location));
  // Ignore already swept tiles and flagged tiles.
  if(tile.isSwept || tile.hasFlag)
  {
    return false;
  }
   
  tile.isSwept = true;
  --numHiddenTiles;
  
  if(tile.hasMine)
  {
    running = false;
    return true; 
  }

  // It's a number now
  if(tile.number == 0)
    for(Location l : locationsAround(location))
      sweep(l);

  if (numHiddenTiles == numMines)
  {
    won = true;
    flagsLeft = 0;
    running = false;
  }
  return true; 
}

bool Board::canChord(const Location & location) const
{
  Tile &tile(tileAt(location));
  return tile.isSwept && !tile.hasMine 
    && numAround(location, [](const Tile &t){return t.hasFlag;} ) == tile.number; 
}

bool Board::chord(const Location & location)
{
  std::vector<Location> locations(locationsAround(location));
  Tile &tile(tileAt(location)); 
  
  // Checking if it can chord
  // Does not call canchord because that would be less efficient (it calculates locsaround twice)
  if(!(tile.isSwept && !tile.hasMine)) return false;
  
  int numFlags{0};
  for(Location l : locations)
    if(tileAt(l).hasFlag)
      ++numFlags; 
  if(numFlags != tile.number) return false; 

  //Chording
  for(Location l : locations)
    sweep(l);

  return true;
}

void Board::flag(const Location & location)
{
  Tile &tile(tileAt(location));
  if(tile.isSwept)
    return; // can't flag a swept tile
  
  tile.hasFlag = !tile.hasFlag;
  if(tile.hasFlag)
    --flagsLeft;  
  else
    ++flagsLeft;
}

Tile& Board::tileAt(const Location & location) const
{
  return board[location.row][location.column];
}

std::vector<Tile*> Board::tilesAround(const Location & location) const
{
  std::vector<Tile*> tilesAround = std::vector<Tile*>();
  for(int r = location.row-1; r < location.row + 2; ++r)
  {
    for(int c = location.column-1; c < location.column + 2; ++c)
    {
      Location locationAround(r,c);
      if (isValidLocation( locationAround ) && !(r == location.row && c == location.column))
        tilesAround.push_back( &tileAt(locationAround) );
    }
  }
  return tilesAround;
}

std::vector<Location> Board::locationsAround(const Location & location) const
{
  std::vector<Location> locationsAround; 
  for(int r = location.row-1; r < location.row + 2; ++r)
  {
    for(int c = location.column-1; c < location.column + 2; ++c)
    {
      Location locationAround(r,c);
      if (isValidLocation( locationAround ) && !(r == location.row && c == location.column))
        locationsAround.push_back( locationAround );
    }
  }
  return locationsAround;
}

int Board::numAround(const Location & location, const std::function<bool(const Tile &)>& fn) const
  {
    int count{0};
    for(Tile *t : tilesAround(location) )
      if(fn(*t))
        ++count; 
    return count;
  }

bool Board::isValidLocation(const Location &location) const 
{
  return location.row >= 0 && location.row < numRows
    && location.column >= 0 && location.column < numColumns;
}

char Board::inside(const Tile& tile) const
{
  if (won)
    return tile.isSwept ? (tile.number == 0 ? ' ' : tile.number + 48) : 'P';
  
  if ( (!running && !won && !tile.isSwept && !tile.hasMine && !tile.hasFlag)
    || (running && !tile.isSwept && !tile.hasFlag) 
    || (tile.isSwept && !tile.hasMine && tile.number == 0) )
    return ' ';
  
  if (tile.hasFlag)
    return (!running && !tile.hasMine) ? 'X' : 'P';
  
  if (tile.hasMine)
    return '*';

  return tile.number + 48;
}

std::string Board::tileString(const Location & location) const
{
  Tile &tile(tileAt(location));
  char first = !tile.isSwept ? '[' : ' ';
  char last = !tile.isSwept ? ']' : ' ';

  return std::string("") + first + inside(tile) + last;
}

Board::~Board()
{
  // Freeing the memory allocated for the board array
  for (int i = 0; i < numRows; ++i)
  {
    delete[] board[i];
  }
  delete[] board;
}

std::string numSpaces(int num)
{ 
  std::string ret;
  if (num < 100)
    ret += ' ';
  if (num < 10)
    ret += ' ';
  return ret;
}

std::ostream& operator<<(std::ostream& out, const Board& boardObj)
{
  out << "P " << boardObj.flagsLeft << '\n'; 
  out << "   ";
  for(int c = 0; c < boardObj.numColumns; ++c)
    out << c << numSpaces(c); 
  out << '\n';
    
  for(int r = 0; r < boardObj.numRows; ++r)
  {
    out << r << numSpaces(r);
    for(int c = 0; c < boardObj.numColumns; ++c)
      out << boardObj.tileString( Location(r,c) );
    out << '\n';
  }
  return out;
}
