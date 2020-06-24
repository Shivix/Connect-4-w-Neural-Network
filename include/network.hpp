#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP

#include <vector>
#include "layer.hpp"


class network{ // TODO: MAYBE TRY LAYER BASE CLASS HIDDEN? OUTPUT ETC LAYERS AS CHILD CLASSES. layer class alone could help ALOT with scalability
public:
    network(const std::vector<int>&);
    ~network();

    int fitness = 0;
    
    void crossover(const network&);
    void drawNetwork();
    void feedForward();
    void mutate();
    /*bool operator > (const network& networkVar) const
    {
        return fitness > networkVar.fitness;
    }*/
    std::vector<layer> layerVec = {};
    
private:
    static constexpr int INPUTSIZE = 42; // set to the amount of positions on a connect4 board
    float highestOutput();
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP