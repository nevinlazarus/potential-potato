#ifndef GAME
#define GAME

class Game {
    public:
    Game(int width, int height);
    
    bool makeMove(int x);
    
    
    
    void printBoard();
    
    int result();
    
    bool ended();
    
    int getTurn();
    
    int getWhoseTurn();
    
    private:
    
    void checkForWinner();
    std::vector<std::vector<int> > board;
    int WIDTH, HEIGHT;
    int turn;
    int winner = 0;
    std::pair<int, int> lastMove = {-1, -1};
};

#endif
