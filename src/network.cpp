#include <random>
#include <iostream>
#include "../include/network.hpp"

#define NUMOFLAYERS 3
#define MUTATESPERLAYER 3

network::network(const std::vector<int>& input){
    layer inputLayer;
    inputLayer.neuronVec.clear(); // clear constructed neurons to emplace new ones
    inputLayer.neuronVec.reserve(input.size());
    for(auto i = 0; i < input.size(); ++i){ 
        inputLayer.neuronVec.emplace_back(neuron(0)); // neuron(0) as input has no incoming connections
        inputLayer.neuronVec[i].value = input[i];//FIXME: REQUIRES FUTURE BOARD MOVES TO BE CHANGED IN NETWORK TOO.
    }
    layerVec.reserve(NUMOFLAYERS);
    layerVec.emplace_back(inputLayer);
    for(auto i = 0; i < NUMOFLAYERS - 1; ++i){
        layerVec.emplace_back(layer());
    }
}

network::~network(){

    /*for(auto&& i : layerVec){ // ensure heap allocated memory is deleted once the object is out of scope
        delete i;
    }
    */
}


void network::crossover(const network& mate){ // combine half of the neurons of one network with another

    std::uniform_int_distribution<int> netsizeDistribution(0, layer::NEURONSPERLAYER - 1);
    int neuronToCrossover;
    for(auto i = 0; i < this->layerVec.size(); ++i){ // this will often copy over a neuron that has already been copied meaning the network that calls the function will have the dominant genome (temp)
        neuronToCrossover = netsizeDistribution(engine);
        this->layerVec[i].neuronVec[neuronToCrossover] = mate.layerVec[i].neuronVec[neuronToCrossover];
    }
}

void network::drawNetwork(){ // gives visual feedback for test purposes.
    for(auto&& i: layerVec){
        std::cout << "=============================================LAYER DIVIDER============================================\n";
        for(auto&& j: i.neuronVec){
            for(auto&& k: j.getConnectionVec()){
                std::cout << "Weight:" << k.weight << "from:" << k.input << "neuron\n";
            }
            std::cout << "Value:" << j.value << "\n";
        }
    }
}

void network::feedForward(){
    for(auto i = 1; i < layerVec.size(); ++i){
        layerVec[i].feed(layerVec[i - 1]);
    }
    //return static_cast<int>(highestOutput());
}

float network::highestOutput(){
    float highestValue = layerVec.back().neuronVec[0].value;
    for(auto&& i: layerVec.back().neuronVec){
        if(i.value > highestValue){
            highestValue = i.value;
        }
    }
    return std::round(highestValue); // round output to 1 to use with applyMove()
}

void network::mutate(){
    
    std::uniform_int_distribution<int> neuronDistribution(0, (layer::NEURONSPERLAYER - 1));
    std::uniform_int_distribution<int> connectionDistribution(0, layer::NEURONSPERLAYER - 1); // track amount of connections in one layer?
    std::uniform_real_distribution<float> weightDistribution(0, 1);
    for(auto i = 1; i < layerVec.size(); ++i){ // starts at 1 to avoid mutating the input layer
        for(auto j = 0; j < MUTATESPERLAYER; ++j){
            layerVec[i].neuronVec[neuronDistribution(engine)].getConnectionVec()[connectionDistribution(engine)].weight = weightDistribution(engine);
        }
    }
}
