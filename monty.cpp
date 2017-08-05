#include <iostream>
#include <vector>
#include <time.h>       /* time */
#include "monty.h"
#include "connect4.h"
#include <mutex>

#include <random>
#include <thread>



Monty::Monty(int numtrials) {
    srand (time(NULL));
    trials = numtrials;
}

std::vector<double> Monty::runThread(Game g) {
    double result[7] = {0};
    double count[7] = {0};
    bool badMoves[7] = {false};
    int whoAmI = g.getWhoseTurn();
    std::vector<double> ret(7, 0);
    for (int i = 0; i < trials; ++i) {
        Game copy = g;
        bool moved = false;
        int move;
        int firstMove = -1;
        int turns = 0;
        while (!copy.ended()) {
            moved = false;
            
            while (!moved) {
                move = rand() % 7;                

                moved = copy.makeMove(move);                   
                ++turns;
            }                                           
            if (firstMove == -1) {
                firstMove = move;
            }
        }

        //I WON
        count[firstMove]++;
        if (copy.result() == whoAmI) {
            result[firstMove] += 10000.0/log2(turns + 10);

        } else if (copy.result() == 0) {
            //DRAW
            result[firstMove] -= 0;
        } else {
            //I LOST :(
            result[firstMove] -= 10000.0/log2(turns + 10);
        }                   
                         
    }
    for (int i = 0; i < 7; ++i) {
        if (count[i] == 0) {
            ret[i] = -100000;
        } else {
            ret[i] = result[i] / count[i];
        }   
        //std::cout << result[i] << " " << count[i] << std::endl;
    }
    
    return ret;

}

int Monty::getBestMove(Game g) {


    
    int numThreads = std::thread::hardware_concurrency();
    
    std::vector<std::thread> threads;
    std::vector<std::vector<double> > results(numThreads, std::vector<double>(7));

    for (int i = 0; i < numThreads; ++i) {
        std::thread t ([g, &results, i, this]{            
            results[i] = Monty::runThread(g);

        });
        threads.push_back(std::move(t));
    }
    
    double overall[7] = {0.0};

    for (int i = 0; i < numThreads; ++i) {
        threads.front().join();
        threads.erase(threads.begin());    
        for (int j = 0; j < 7; ++j) {
            overall[j] += results[i][j];
        }

        
        
    }
    
    
    int best = -1;   
    for (int i = 0; i < 7; ++i) {
        if (best == -1 || (overall[i]) > (overall[best])) {
            best = i;
        }
    }
    std::cout << "Player: " << g.getWhoseTurn() << std::endl;    
    std::cout << "BEST: " << overall[best] << std::endl;
    return best;
}
  
