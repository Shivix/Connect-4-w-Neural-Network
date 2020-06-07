#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP

#include "neuron.hpp"
#include <vector>
#include "board.hpp" // remove dependency on board class.

class network{
public:
    network();
    ~network();

    int fitness = 0;
    
    void drawNetwork();
    float feedforward(const std::vector<std::vector<board::counter>>&);
    void mutate();
    /*bool operator > (const network & networkVar) const
    {
        return fitness > networkVar.fitness;
    }*/
    
private:
    std::vector<neuron> hiddenLayer = {}; // TODO: improve scalability of adding layers // parameter in constructor for how many hidden layers after first.
    std::vector<neuron> hiddenLayer2 = {};
    std::vector<neuron> outputLayer = {};

    const static int INPUTSIZE = 42; // set to the amount of positions on a connect4 board
    void crossover(const network&);
    void fitnessTest();
    float highestOutput();
    
    
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP
