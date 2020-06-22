#include <cmath>
#include <iostream>
#include "../include/neuron.hpp"


neuron::neuron(int connections){

    static std::uniform_real_distribution<float> randomDistribution(0, 1.0); // TODO: implement negative weights
    connectionVec.resize(connections);
    int inputIter = -1;
    for(auto&& i: connectionVec){
        i.weight = randomDistribution(engine);
        i.input = ++inputIter;
    }
}

neuron::neuron(const neuron &neuron) = default;

neuron::~neuron()= default;

std::vector<neuron::connection> neuron::getConnectionVec(){
    return connectionVec;
}

void neuron::sigmoid() { // runs when a neuron is fed from all previous neurons
    //std::cout << "v0" << value;
    value = value / (1 + (std::abs(value)));
    //std::cout << "v1" << value;
}

void neuron::activation(){
    
    
    
}



