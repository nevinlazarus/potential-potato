import connect4_ai

class connect4:
    
    def __init__(self, width, height):
        self.board = [[0 for i in range(height)] for j in range(width)]
        print(self.board)
        self.width = width;
        self.height = height;
        self.turn = 0;
        self.winner = 0;
    
    def makeMove(self, x):
        if (x < 0 or x >= self.width): 
            return False;
        #if the board is full
        if (self.turn == self.width * self.height): 
            return False;

        player = self.getWhoseTurn();
        for i in range(0, self.height):
            if (self.board[x][i] == 0):
                self.board[x][i] = player;
                self.turn += 1
                self.lastMove = x, i;
                if (self.turn >= 7):
                    self.checkForWinner()
                return True;
        return False;

    def checkForWinner(self):
        if (self.winner):
            return
        startX, startY = self.lastMove
        player = self.board[startX][startY];
        right = 0;
        down = 0;
        board = self.board
        
        #horizontal
        for i in range(startX + 1, self.width):
            if (board[i][startY] == player):
                right += 1;
            else:
                break;
        for i in range(startX - 1, -1, -1):
            if (board[i][startY] == player):
                right += 1;
            else:
                break
        #vertical
        for i in range(startY - 1, -1, -1):
            if (board[startX][i] == player):
                down += 1
            else:
                break;
        
        
        #4 diagonals
        tr = 0;
        for i in range(1, 4):
            if (startX + i < self.width and startY + i < self.height):
                if board[startX + i][startY + i] == player:
                    tr += 1
                else:
                    break;

        for i in range(1, 4):
            if startX - i >= 0 and startY - i >= 0:
                if board[startX - i][startY - i] == player:
                    tr += 1;
                else:
                    break
                    
        tl = 0;
        for i in range(1, 4):
            if (startX + i < self.width and startY - i >= 0):
                if (board[startX + i][startY - i] == player):
                    tl += 1;
                else:
                    break
                    
        for i in range(1, 4):
            if (startX - i >= 0 and startY + i < self.height):
                if (board[startX - i][startY + i] == player):
                    tl += 1;
                else:
                    break

        if (right >= 3 or down >= 3 or tr >= 3 or tl >= 3):
            self.winner = player;
        

    def printBoard(self):
        for i in range(self.height - 1, -1, -1):
            for j in range(0, self.height):
                print(str(self.board[j][i]), end='', flush=True),
            print("")

    def result(self):
        return self.winner;

    def ended(self):
        return (self.turn == self.width * self.height or self.winner);

    def getTurn(self):
        return self.turn;

    def getWhoseTurn(self):
        return (self.turn % 2) + 1;

def main():
    a = connect4_ai
    game = connect4(7, 6)
    move = 0
    moveList = ""
    while (not game.ended()):
        game.printBoard()
        if (game.getWhoseTurn() == 1):
            moved = False;
            while not moved:
                move = int(input("Please make a move: ")) 
                moved = game.makeMove(move)
        else:
            move = a.get_best_move(moveList, 7, 6, 1000)
            game.makeMove(move);

        moveList += str(move);        

    game.printBoard()
    if not game.result() == 0:
        print("Player " + str(game.result()) + " Wins")
    else:
        print("Draw")

if __name__ == "__main__":
    main();