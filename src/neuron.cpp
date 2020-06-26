#include <cmath>
#include <iostream>
#include "../include/neuron.hpp"


neuron::neuron(int connections){
    static std::uniform_real_distribution<float> randomDistribution(-1, 1.0);
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
    value = value / (1 + (std::abs(value)));
}

void neuron::activation(){
    
    
}

std::ostream& operator<<(std::ostream& os, const neuron::connection& connection){
    os << "Weight:" << connection.weight << "from:" << connection.input << "neuron\n";
    return os;
}
