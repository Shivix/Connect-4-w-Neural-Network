#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP

#include "network.hpp"
#include "board.hpp"

class agent{
public:
    agent(const std::vector<int>&); // give agent all the networks?
    ~agent();
    
private:
    
    const int maxPop = 10;
    std::vector<network> networkVec;
    void playGame(network, board, bool); // will call copy constructor for both board and network
    void sortFittest(); // order networkVec in descending order of fitness Run for offspring AND parents together to ensure no regression
    void cullPopulation();
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
