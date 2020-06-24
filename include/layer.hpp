#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP

#include "neuron.hpp"

class layer{
public:
    layer();
    ~layer();
public:
    void feed(const layer&); // per layer?
    static constexpr int NEURONSPERLAYER = 30;
    std::vector<neuron> neuronVec = {}; // TODO: improve scalability of adding layers // parameter in constructor for how many hidden layers after first.
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP