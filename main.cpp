#include <iostream>
#include "agent.hpp"


int main(){
    

    
    std::cout << "Hello, World!" << std::endl;
    board board;
    network network;
    network.feedforward(board.boardVec);
    network.drawNetwork();
    
    
    
    return 0;
}
