#ifndef MONTY
#define MONTY
#include <iostream>
#include <vector>
#include <time.h>       /* time */
#include "connect4.h"

class Monty {
    public:
    Monty(int t);
    
    int getBestMove(Game g);    
    
    private:
    std::vector<double> runThread(Game g); 
    int trials;   

};

int getBestMove(std::string moves, int width, int height, int numTrials);

#endif