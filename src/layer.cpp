#include "../include/layer.hpp"

layer::layer(int neurons){
    for(auto i = 0; i < neurons; ++i){
        neuronVec.emplace_back(neuron(neurons));
    }
}

layer::~layer()= default;

void layer::feed(const layer& prevLayer){ 
    for(auto&& i: this->neuronVec){
        for(auto&& j: i.getConnectionVec()){ 
            i.value += (j.weight * prevLayer.neuronVec[j.input].value);
        }
        i.sigmoid();
    }
}
