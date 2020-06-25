#include <algorithm>
#include "../include/agent.hpp"


agent::agent(std::vector<int>* input){
    for(auto i = 0; i < maxPop; ++i){
        networkVec.emplace_back(network(input));
    }
}

agent::~agent()= default;

void agent::cullPopulation(){
    sortFittest();
    networkVec.erase(networkVec.begin() + (maxPop / 2), networkVec.end()); // removes half of the networks with the lowest fitness.
}

void agent::playGame(network network, board gameBoard, bool isRed){

    int netMove;

    // plug current board state into feedforward function // game state class?
    while(!gameBoard.gameWon){
        //netMove = network.feedForward();

        // applymove function on feedforward output? LOOP WITH ABOVE UNTIL GAME OVER

        while(!gameBoard.applyMove(netMove, isRed)){ //repeats if move is illegal //TODO: may loop forever if game is drawn (use recursion?)
            
        }
        gameBoard.evaluateBoard();
    }


    network.fitness = gameBoard.evaluateBoard();
}

void agent::sortFittest(){ // find fittest networks to keep
    
    std::sort(networkVec.begin(), networkVec.end(), [](const network& a, const network& b) { // sorts networks in descending order by fitness
        return a.fitness > b.fitness;
    });
}


