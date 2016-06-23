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
