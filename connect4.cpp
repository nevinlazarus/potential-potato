#include <iostream>
#include <vector>
#include "monty.h"
#include "connect4.h"


Game::Game(int width, int height) {
    board = std::vector<std::vector<int> >(width, std::vector<int>(height, 0));
    WIDTH = width;
    HEIGHT = height;
    turn = 0;
}

bool Game::makeMove(int x) {

    if (x < 0 || x >= WIDTH) return false;
    //if the board is full
    if (turn == WIDTH * HEIGHT) return false;

    int player = getWhoseTurn();
    for (int i = 0; i < HEIGHT; ++i) {
        if (board[x][i] == 0) {
            board[x][i] = player;
            turn++;
            lastMove = std::make_pair(x, i);
            checkForWinner();
            return true;
        }
    }
    return false;
    
}

void Game::checkForWinner() {

    if (winner) return;
    int startX = lastMove.first;
    int startY = lastMove.second;
    int player = board[startX][startY];
    int right = 0;
    int down = 0;
    
    //horizontal
    for (int i = startX + 1; i < WIDTH; ++i) {
        if (board[i][startY] == player) {
            ++right;
        } else {
            break;
        }
    }        
    for (int i = startX - 1; i >= 0; --i) {
        if (board[i][startY] == player) {
            ++right;
        } else {
            break;
        }
    }
    //vertical
    for (int i = startY - 1; i >= 0; --i) {
        if (board[startX][i] == player) {
            ++down;
        } else {
            break;
        }
    }
    
    
    //4 diagonals
    int tr = 0;
    for (int i = 1; i <= 3; ++i) {
        if (startX + i < WIDTH && startY + i < HEIGHT) {
            if (board[startX + i][startY + i] == player) { 
                ++tr;
            } else {
                break;
            }
        }
    }
    for (int i = 1; i <= 3; ++i) {
        if (startX - i >= 0 && startY - i >= 0) {
            if (board[startX - i][startY - i] == player) { 
                ++tr;
            } else {
                break;
            }
        }
    }

    int tl = 0;
    for (int i = 1; i <= 3; ++i) {
        if (startX + i < WIDTH && startY - i >= 0) {
            if (board[startX + i][startY - i] == player) { 
                ++tl;
            } else {
                break;
            }
        }
    }
    for (int i = 1; i <= 3; ++i) {
        if (startX - i >= 0 && startY + i < HEIGHT) {
            if (board[startX - i][startY + i] == player) { 
                ++tl;
            } else {
                break;
            }
        }
    }


    if (right >= 3 || down >= 3 || tr >= 3 || tl >= 3) {
        winner = player;
    }
    
}

void Game::printBoard() {
    for (int i = HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << board[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

int Game::result() {
    return winner;
}

bool Game::ended() {        
    return (turn == WIDTH * HEIGHT || winner);
}

int Game::getTurn() {
    return turn;
}

int Game::getWhoseTurn() {
    return (turn % 2) + 1;
}    


int main() {

    Game g = Game(7, 6);
    Monty monty(1000);
    Monty monty2(1000);
    int turn = 0;    
    int move;
    while (!g.ended()) {
        if (turn % 2) {
            move = monty2.getBestMove(g);       
        } else {
            move = monty.getBestMove(g);       
        }
        g.makeMove(move);
        ++turn;
        g.printBoard();
//        int move;
/*        std::cout << "Please make a move: ";
        bool moved = false;
        while (!moved) {
            std::cin >> move;
            moved = g.makeMove(move);    
        }*/

        
    }

    std::cout << "Player " << g.result() << " Wins" << std::endl;


}
