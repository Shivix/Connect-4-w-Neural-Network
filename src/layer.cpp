#include "../include/GNN/layer.hpp"

GNN::layer::layer(int neurons){
    for(auto i = 0; i < neurons; ++i){
        neuronVec.emplace_back(GNN::neuron(neurons));
    }
}

GNN::layer::~layer()= default;

void GNN::layer::feed(const layer& prevLayer){ 
    for(auto&& i: this->neuronVec){
        for(auto&& j: i.getConnectionVec()){ 
            i.value += (j.weight * prevLayer.neuronVec[j.input].value);
        }
        i.sigmoid();
    }
}
