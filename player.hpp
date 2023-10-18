#ifndef PLAYER_H
#define PLAYER_H

#include <string>
class Player
{
public:
    virtual std::string getMove() const = 0;
};

#endif 
