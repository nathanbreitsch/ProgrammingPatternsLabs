

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

using std::cout; using std::endl;
using std::cin; using std::string;

// template for any game where players take turns to make moves
// and there is a winner
class Game{
public:
    Game():playersCount_(0), movesCount_(0), playerWon_(-1){}

    // template method
    void playGame(const int playersCount = 0) {
        if(playersCount) playersCount_ = playersCount;
        movesCount_=0;
        playerWon_=-1;

        initializeGame();

        for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
            makeMove(i);
            if (i==0) ++movesCount_;
        }
        printWinner();
    }

    virtual ~Game(){}

protected:
    // primitive operations
    virtual void initializeGame() = 0;
    virtual void makeMove(int player) = 0;
    virtual bool endOfGame() = 0;
    virtual void printWinner() = 0;

    int playersCount_;
    int movesCount_;
    int playerWon_;
};

// Monopoly - a concrete game implementing primitive
// operations for the template method
class Monopoly: public Game {
public:
    // implementing concrete methods
    void initializeGame(){
        playersCount_ = rand() % NumPlayers + 1 ; // initialize players
    }

    void makeMove(int player) {
        if (movesCount_ > MinMoves){
            const int chance = MinMoves + rand() % (MaxMoves - MinMoves);
            if (chance < movesCount_) playerWon_= player;
        }
    }

    bool endOfGame(){
        return playerWon_ != -1; // returns true if winner is decided
    }

    void printWinner(){
        cout << "Monopoly, player "<< playerWon_<< " won in "
        << movesCount_<< " moves." <<endl;
    }

private:
    static const int NumPlayers = 8; // max number of players
    static const int MinMoves = 20; // nobody wins before MinMoves
    static const int MaxMoves = 200; // somebody wins before MaxMoves
};

// Chess - another game implementing primitive operations
class Chess: public Game {
public:
    void initializeGame(){
        playersCount_ = NumPlayers; // initalize players
        for(int i=0; i < NumPlayers; ++i)
            experience_[i] = rand() % MaxExperience + 1 ;
    }

    void makeMove(int player){
        if (movesCount_ > MinMoves){
            const int chance = rand() % MaxMoves / experience_[player];

            if (chance < movesCount_) playerWon_= player;
        }
    }

    bool endOfGame(){
        return playerWon_ != -1; // returns true if winner is decided
    }

    void printWinner(){
        cout << "Chess, player " << playerWon_
        << " with experience " << experience_[playerWon_]
        << " won in "<< movesCount_ << " moves." <<endl;
    }

private:
    static const int NumPlayers = 2;
    static const int MinMoves = 2; // nobody wins before MinMoves
    static const int MaxMoves = 99; // somebody wins before MaxMoves
    static const int MaxExperience = 3; // player's experience
    // the higher, the greater probability of winning
    int experience_[NumPlayers];
};

class Dice : public Game{
public:
    void initializeGame(){
        //intitalize scores
        for(int i = 0; i < 5; ++i){
            p1roll[i] = 0;
            p2roll[i] = 0;
        }
        playersCount_ = 2;
    }

    void makeMove(int player){
        int numRolls = 1;
        int roll = 1 + rand() % 6;
        char answer;
        while(numRolls < 3){
            cout << "Player: " << player + 1
            << " round:" << movesCount_ + 1 - player << endl;
            cout << "You rolled a " << roll <<
            ". Would you like to roll again? Type 'n' for no." << endl;
            if (player) {
                cin >> answer;
            }
            else{
                answer = (rand()%2) ? 'y' : 'n';
                cout << answer << endl;
            }


            if(answer == 'n'){
                break;
            }
            roll = 1 + rand() % 6;
            ++numRolls;
        }
        if (player) {
            p1roll[movesCount_ - 1] = roll;
        }
        else{
            p2roll[movesCount_] = roll;
        }
    }

    bool endOfGame(){
        return (p1roll[4] > 0 && p2roll[4] > 0);
    }

    void printWinner(){
        int sum1, sum2 = 0;
        for(int i = 0; i < 5; ++i){
            sum1 += p1roll[i];
            sum2 += p2roll[i];
        }
        if(sum1 > sum2){
            cout << "Computer Wins! Horray!" << endl;
        }
        else if (sum1 < sum2){
            cout << "Player 2 Wins! Woop-De-Doo!" << endl;
        }
        else{
            cout << "It's a tie! Everybody wins! Neat-o!!!" << endl;
        }
    }

protected:
    int p1roll[5];
    int p2roll[5];

};

int main() {
    srand(time(0));


    for (int i = 0; i < 10; ++i){ // play chess 10 times
        Chess* chessGame = new Chess;
        chessGame->playGame();
        delete chessGame;
    }



    for (int i = 0; i < 5; ++i){ // play monopoly 5 times
        Monopoly* monopolyGame = new Monopoly;
        monopolyGame->playGame();
        delete monopolyGame;
    }

    for (int i = 0; i < 5; ++i){ // play monopoly 5 times
        Dice* diceGame = new Dice;
        diceGame->playGame();
        delete diceGame;
    }
}
