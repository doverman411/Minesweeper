#ifndef RANDOM_H
#define RANDOM_H 

#include <iostream>
#include <random>

// returns a number from min to max, including min, but excluding max. 
int randInt(int min, int max) {
    std::random_device rd;
    std::mt19937 generator(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<int> distribution;

    return distribution(generator) % (max-min) + min;
}

#endif
