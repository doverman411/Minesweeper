//NOTE: ONLY WORKS FOR LINUX/MAC (due to the clearscreen feature)

#include "game.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
int main()
{
  Board BOARD(16,16,40);
  
  string input;
  while(BOARD.running)
  {
    cout << BOARD << '\n';
    std::getline(cin, input);
    move(input, BOARD);
    std::system("clear"); 
  }
  cout << BOARD;
  cout << "YOU " << (BOARD.won ? "WIN!" : "LOSE!") << '\n';

  return 0;
}
