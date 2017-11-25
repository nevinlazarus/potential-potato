#ifndef ALPHA
#define ALPHA
#include <iostream>
#include <vector>
#include <time.h>       /* time */
#include "connect4.h"

class AlphaBeta {
    public:
    AlphaBeta(int t);
    
    int getBestMove(Game g);    
    
    private:
    std::vector<double> runThread(Game g); 
    int trials;   

};

#endif
