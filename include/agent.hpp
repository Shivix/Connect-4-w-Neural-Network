#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP

#include "network.hpp"
#include "board.hpp"

class agent{
public:
    explicit agent(std::vector<int>*); // give agent all the networks?
    ~agent();
    std::vector<network> generation;
    
private:
    const int maxPop = 10;
    void sortFittest(); // order networkVec in descending order of fitness Run for offspring AND parents together to ensure no regression
    void cullPopulation();
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
