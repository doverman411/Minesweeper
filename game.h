#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <sstream>

bool can_stoi(std::string s)
{
  try
  {
    std::stoi(s);
    return true;
  }
  catch (const std::invalid_argument& e) {return false;}
  catch (const std::out_of_range& e) {return false;}

  return false; 
}

void move(std::string input, Board &b)
{
  size_t space1 = input.find(' ');
  size_t space2 = input.find(' ', space1 + 1);
  
  char option = input[0];
  
  std::string rowStr{input.substr(space1 + 1, space2 - space1 - 1)}; 
  if (!can_stoi(rowStr)) return; 
  int row = std::stoi(rowStr);

  std::string colStr{input.substr(space2 + 1)};
  if(!can_stoi(colStr)) return; 
  int col = std::stoi(colStr);

  Location loc(row,col);
  
  switch(option)
  {
    case 'S':
      b.sweep(loc);
      break;
    case 'F':
      b.flag(loc);
      break;
    case 'C':
      b.chord(loc);
      break;
  }
}

#endif