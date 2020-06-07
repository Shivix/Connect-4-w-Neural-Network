#include <cmath>
#include "neuron.hpp"


neuron::neuron(int connections){

    static std::uniform_real_distribution<float> randomDistribution(0, 1.0); // TODO: implement negative weights
    connectionVec.resize(connections);
    for(auto &&i: connectionVec){
        i.weight = randomDistribution(engine);
    }
}

neuron::neuron(const neuron &neuron) = default;

neuron::~neuron()= default;

std::vector<neuron::connection> neuron::getConnectionVec(){
    return connectionVec;
}

void neuron::sigmoid() { // runs when a neuron is fed from all previous neurons

    std::tanh(value);

}

void neuron::activation(){
    
    
    
}



