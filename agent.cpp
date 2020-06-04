#include <algorithm>
#include "agent.hpp"



agent::agent(){

}

agent::~agent()= default;

void agent::playGame(network network, board gameBoard, bool isRed){

    int netMove;

    // plug current board state into feedforward function // game state class?
    while(!gameBoard.gameWon){
        netMove = static_cast<int>(network.feedforward(gameBoard.boardVec));

        // applymove function on feedforward output? LOOP WITH ABOVE UNTIL GAME OVER

        while(!gameBoard.applyMove(netMove, isRed)){ //repeats if move is illegal //TODO: may loop forever if game is drawn (use recursion?)
            
        }
        gameBoard.evaluateBoard();
    }


    network.fitness = gameBoard.evaluateBoard();
}



void agent::getFittest(){ // find fittest networks to keep
    
    std::sort(networkVec.begin(), networkVec.end(), [](const network& a, const network& b) { // TODO: test to see if is descending or ascending
        return a.fitness > b.fitness;
    });
}
