#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP

#include "neuron.hpp"
#include <vector>

class network{
public:
    network(int);
    ~network();

    int fitness = 0;
    
    void drawNetwork();
    float feedforward(std::vector<std::vector<int>>);
    
    /*bool operator > (const network & networkVar) const
    {
        return fitness > networkVar.fitness;
    }*/
    
private:
    std::vector<neuron> hiddenLayer = {}; // TODO: improve scalability of adding layers // parameter in constructor for how many hidden layers after first.
    std::vector<neuron> hiddenLayer2 = {};
    std::vector<neuron> outputLayer = {};

    int INPUTSIZE;
    void crossover(network);
    void fitnessTest();
    float highestOutput();
    void mutate();

    
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP
