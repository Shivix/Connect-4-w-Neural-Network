#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP

#include <vector>
#include "layer.hpp"


class network{
public:
    explicit network(std::vector<int>*);
    ~network();

    int fitness = 0;
    
    void crossover(const network&);
    void drawNetwork();
    float feedForward();
    void mutate();
    /*bool operator > (const network& networkVar) const
    {
        return fitness > networkVar.fitness;
    }*/
    std::vector<layer> layerVec = {}; // contains hidden layers and output layer.
    
private:
    static constexpr int INPUTSIZE = 42; // set to the amount of positions on a connect4 board
    static constexpr int NEURONS_PER_LAYER = 30;
    static constexpr int MUTATES_PER_LAYER = 3;
    std::vector<int>* inputLayer; // stored as pointer to the source of the input layer to ensure layer is kept up to date
    float highestOutput();
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP