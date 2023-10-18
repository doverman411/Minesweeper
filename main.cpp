//NOTE: ONLY WORKS FOR LINUX/MAC (due to the clearscreen feature)

#include "game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "human.h"
#include "bot.hpp"

using namespace std;
int main()
{
  // These are the variables you wanna change.
  Board BOARD(16,16,40);
  const Player* p = new Human();
  
  string input;
  while(BOARD.running)
  {
    cout << BOARD << '\n';
    input = p->getMove();
    move(input, BOARD);
    std::system("clear"); 
  }
  cout << BOARD;
  cout << "YOU " << (BOARD.won ? "WIN!" : "LOSE!") << '\n';

  return 0;
}
