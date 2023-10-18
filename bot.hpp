#ifndef BOT_H
#define BOT_H

#include "player.hpp"

class Bot: public Player
{
public:
    std::string getMove() const
    {
        // implementation here
        return std::string(); 
    }
};

#endif
