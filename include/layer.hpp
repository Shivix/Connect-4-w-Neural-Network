#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP

#include "neuron.hpp"

class layer{
public:
    layer(int);
    ~layer();
public:
    void feed(const layer&);
    template<typename T>
    void feed(const std::vector<T>& inputLayer){
        for(auto&& i: this->neuronVec){ // iterate through neurons
            for(auto&& j: i.getConnectionVec()){ // iterate through connections
                i.value += (j.weight * inputLayer[j.input]);
            }
            i.sigmoid();
        }
    }
    std::vector<neuron> neuronVec = {};
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP