#include <cmath>
#include <iostream>
#include "../GNN/include/neuron.hpp"


GNN::neuron::neuron(int connections){
    static std::uniform_real_distribution<float> randomDistribution(-1, 1.0);
    connectionVec.resize(connections);
    int inputIter = -1;
    for(auto&& i: connectionVec){
        i.weight = randomDistribution(GNN::engine);
        i.input = ++inputIter;
    }
}

GNN::neuron::neuron(const GNN::neuron &neuron) = default;

GNN::neuron::~neuron()= default;

std::vector<GNN::neuron::connection> GNN::neuron::getConnectionVec(){
    return connectionVec;
}

void GNN::neuron::sigmoid() { // runs when a neuron is fed from all previous neurons
    value = value / (1 + (std::abs(value)));
}

void GNN::neuron::tanh() const { // runs when a neuron is fed from all previous neurons
    std::tanh(value);
}

void GNN::neuron::activation(func activationFunc) const{
    activationFunc(value);
}