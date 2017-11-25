#ifndef GAME
#define GAME

#include <string>

class Game {
    public:
    Game(int width, int height);

    Game(int width, int height, std::string gameState);
    
    bool makeMove(int x);
    
    
    
    void printBoard();
    
    int result();
    
    bool ended();
    
    int getTurn();
    
    int getWhoseTurn();

    int width() { return WIDTH; }

    int height() { return HEIGHT; }
    
    const std::vector<std::vector<int> > &getBoard() { return board; }
    
    
    private:
    
    void checkForWinner();
    std::vector<std::vector<int> > board;
    int WIDTH, HEIGHT;
    int turn;
    int winner = 0;
    std::pair<int, int> lastMove = {-1, -1};
};

#endif
