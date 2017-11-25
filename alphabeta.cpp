#include <iostream>
#include <vector>
#include <time.h>       /* time */
#include "alphabeta.h"
#include "connect4.h"
#include <mutex>
#include <climits>

#include <random>
#include <thread>

long long alphaBeta( long long alpha, long long beta, int depthleft, Game g);
long long evaluate(Game g);



AlphaBeta::AlphaBeta(int numTrials) {
    srand (time(NULL));
    trials = numTrials;
    std::cout << "HERE I AM" << std::endl;
}

std::vector<double> AlphaBeta::runThread(Game g) {
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
            result[firstMove] += 10000.0/turns;

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

int AlphaBeta::getBestMove(Game g) {

    int numThreads = std::thread::hardware_concurrency();
    
    std::vector<std::thread> threads;
    std::vector<std::vector<double> > results(numThreads, std::vector<double>(7));
    std::cout << numThreads << " Threads" << std::endl;
    std::cout << numThreads * trials << " Trials" << std::endl;
/*    for (int i = 0; i < numThreads; ++i) {
        std::thread t ([g, &results, i, this]{            
            results[i] = AlphaBeta::runThread(g);

        });
        threads.push_back(std::move(t));
    }*/
    long long overall[7];
    for (int i = 0; i < 7; ++i) {
        Game copy = Game(g);
        if (copy.makeMove(i))
            overall[i] = -alphaBeta(LLONG_MIN + 1, LLONG_MAX, 5, copy);
        else 
            overall[i] = LLONG_MIN;
        std::cout << overall[i] << std::endl;
    }

    long long best = -1;   
    for (int i = 0; i < 7; ++i) {
        if (best == -1 || (overall[i]) > (overall[best])) {
            best = i;
        }
    }

    std::cout << "Player: " << g.getWhoseTurn() << std::endl;    
    std::cout << "BEST: " << overall[best] << std::endl;
    return best;
}

long long alphaBeta( long long alpha, long long beta, int depthleft, Game g) {
    if( depthleft == 0 || g.ended()) return evaluate(g);
    for (int i = 0; i < 7; ++i)  {
        Game copy = g;
        copy.makeMove(i);
        long long score = -alphaBeta( -beta, -alpha, depthleft - 1 , copy);
        if( score >= beta )
            return beta;   //  fail hard beta-cutoff
        if( score > alpha )
            alpha = score; // alpha acts like max in MiniMax
    }
    return alpha;
}

long long evalCell(Game g, int col, int row) {
    int player = g.getWhoseTurn();
    auto board = g.getBoard();
    int cellVal = board[col][row];
    
    long long totalScore = 0;
    long long score = 1;
    // horizontal
    for (int i = 1; col + i < g.width() && i < 4; ++i) {
        if (board[col + i][row] == cellVal)
            score *= 10;
        else if (board[col + i][row] == 0)
            score *= 2;
        else
        {
            score = 0;
            break;
        }
    }
    totalScore += score;
    
    for (int i = 1; row + i < g.height() && i < 4; ++i) {
        if (board[col][row + i] == cellVal)
            score *= 10;
        else if (board[col][row + i] == 0)
            score *= 2;
        else
        {
            score = 0;
            break;
        }
    }
    totalScore += score;
    
    for (int i = 1; col + i < g.width() && row + i < g.height() && i < 4; ++i) {
        if (board[col + i][row + i] == cellVal)
            score *= 10;
        else if (board[col + i][row + i] == 0)
            score *= 2;
        else
        {
            score = 0;
            break;
        }
    }
    totalScore += score;
    
    for (int i = 1; col - i >= 0 && row + i < g.height() && i < 4; ++i) {
        if (board[col - i][row + i] == cellVal)
            score *= 10;
        else if (board[col - i][row + i] == 0)
            score *= 2;
        else
        {
            score = 0;
            break;
        }
    }
    totalScore += score;
    return player != cellVal ? totalScore : -totalScore;
}


long long evaluate(Game g) {
    if (g.ended()) {
        return LLONG_MIN + 1;
    }
    long long score = 0;
    for (int i = 0; i < g.width(); ++i) {
        for (int j = 0; j < g.height(); ++j) {
            score += evalCell(g, i, j);
        }
        
    }
    return score;
} 
