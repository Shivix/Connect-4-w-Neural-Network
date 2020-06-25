#include "../include/layer.hpp"

layer::layer(int neurons){
    for(auto i = 0; i < neurons; ++i){
        neuronVec.emplace_back(neuron(neurons));
    }
}

layer::~layer(){

}

void layer::feed(const layer& prevLayer){ // parameter is the input layer.
    // WeightOfInputCon * ActivationOfInputNeuron (for each input) = ActivationOfNewNeuron (+ bias with sigmoid func)
    for(auto&& i: this->neuronVec){ // iterate through neurons
        for(auto&& j: i.getConnectionVec()){ // iterate through connections
            i.value += (j.weight * prevLayer.neuronVec[j.input].value);
        }
        i.sigmoid();
    }
}
