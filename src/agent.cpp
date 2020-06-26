#include <algorithm>
#include "../include/agent.hpp"


agent::agent(std::vector<int>* input){ // TODO: make agent base class. Use by inheriting and adding specific functions for use case.
    for(auto i = 0; i < maxPop; ++i){
        generation.emplace_back(network(input));
    }
}

agent::~agent()= default;

void agent::cullPopulation(){
    sortFittest();
    generation.erase(generation.begin() + (maxPop / 2), generation.end()); // removes half of the networks with the lowest fitness.
}

void agent::sortFittest(){ // find fittest networks to keep
    
    std::sort(generation.begin(), generation.end(), [](const network& a, const network& b) { // sorts networks in descending order by fitness
        return a.fitness > b.fitness;
    });
}


