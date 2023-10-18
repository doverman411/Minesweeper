#ifndef human_h
#define human_h

#include "player.hpp"

class Human: public Player
{
public:
    std::string getMove() const
    {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }
};

#endif
