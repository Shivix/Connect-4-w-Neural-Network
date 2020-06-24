#include "../include/layer.hpp"

layer::layer(){
    for(auto i = 0; i < NEURONSPERLAYER; ++i){
        neuronVec.emplace_back(neuron(NEURONSPERLAYER));
    }
}

layer::~layer(){

}

void layer::feed(const layer& prevLayer){ // parameter is the input layer. TODO: make input layer declared and stored in constructor?
    // WeightOfInputCon * ActivationOfInputNeuron (for each input) = ActivationOfNewNeuron (+ bias with sigmoid func)
    for(auto&& i: this->neuronVec){ // iterate through neurons
        for(auto&& j: i.getConnectionVec()){ // iterate through connections
            i.value += (j.weight * prevLayer.neuronVec[j.input].value);
        }
        i.sigmoid();
    }
}
