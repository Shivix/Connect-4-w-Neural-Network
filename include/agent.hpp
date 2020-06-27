#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP

#include <algorithm>
#include "network.hpp"

template<typename T>
class agent{
public:
    explicit agent(std::vector<T>* input){ // TODO: make agent base class. Use by inheriting and adding specific functions for use case.
        for(auto i = 0; i < maxPop; ++i){
            generation.emplace_back(network(input));
        }
    }
    
    ~agent()= default;
    std::vector<network<T>> generation;
    
private:
    const int maxPop = 10;
    void sortFittest(){ // find fittest networks to keep

        std::sort(generation.begin(), generation.end(), [](const network<T>& a, const network<T>& b) { // sorts networks in descending order by fitness
            return a.fitness > b.fitness;
        });
    } // order networkVec in descending order of fitness Run for offspring AND parents together to ensure no regression

    void cullPopulation(){
        sortFittest();
        generation.erase(generation.begin() + (maxPop / 2), generation.end()); // removes half of the networks with the lowest fitness.
    }


};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
