#include <random>
#include <iostream>
#include "network.hpp"


#define NETSIZE 30
#define MUTATESPERLAYER 3


network::network(){
    
    hiddenLayer.reserve(NETSIZE);
    hiddenLayer2.reserve(NETSIZE);
    outputLayer.reserve(NETSIZE);
    for(auto i = 0; i < NETSIZE; ++i){
        hiddenLayer.emplace_back(neuron(INPUTSIZE));
    }
    for(auto i = 0; i < NETSIZE; ++i){
        hiddenLayer2.emplace_back(neuron(NETSIZE));
    }
    for(auto i = 0; i < NETSIZE; ++i){
        outputLayer.emplace_back(neuron(NETSIZE));
    }
}

network::~network(){

    /*for(auto & i : hiddenLayer){ // ensure heap allocated memory is deleted once the object is out of scope
        delete i;
    }
    for(auto & i : hiddenLayer2){
        delete i;
    }
    for(auto & i : outputLayer){
        delete i;
    }*/
    
    
}


void network::crossover(network mate){ // combine half of the neurons of one network with another

    std::uniform_int_distribution<int> netsizeDistribution(0, NETSIZE);
    int neuronToCrossover;
    for(auto i = 0; i < NETSIZE / 2; ++i){ // this will often copy over a neuron that has already been copied meaning the network that calls the function will have the dominant genome (temp)
        neuronToCrossover = netsizeDistribution(engine);
        this->hiddenLayer[neuronToCrossover] = mate.hiddenLayer[neuronToCrossover];
        neuronToCrossover = netsizeDistribution(engine);
        this->hiddenLayer2[neuronToCrossover] = mate.hiddenLayer2[neuronToCrossover];
        neuronToCrossover = netsizeDistribution(engine);
        this->outputLayer[neuronToCrossover] = mate.outputLayer[neuronToCrossover];
    }
}

void network::drawNetwork(){ // gives visual feedback for test purposes.
    for(auto i: hiddenLayer){
        for(auto j = 0; j < i.connectionVec.size(); ++j){
            std::cout << "Weight:" << i.connectionVec[j].weight << "from:" << j << "neuron\n";
        }
        std::cout << "Value:" << i.value << "\n";
    }
    for(auto i: hiddenLayer2){
        for(auto j = 0; j < i.connectionVec.size(); ++j){
            std::cout << "Weight:" << i.connectionVec[j].weight << "from:" << j << "neuron\n";
        }
        std::cout << "Value:" << i.value << "\n";
    }
    for(auto i: outputLayer){
        for(auto j = 0; j < i.connectionVec.size(); ++j){
            std::cout << "Weight:" << i.connectionVec[j].weight << "from:" << j << "neuron\n";
        }
        std::cout << "Value:" << i.value << "\n";
    }
}

void network::fitnessTest(){ // does it need this when board has evaluation?

    
    
    
    
    
}

float network::feedforward(std::vector<std::vector<board::counter>> boardVec){ // parameter is the input layer. TODO: make input layer declared and stored in constructor?
    
    // WeightOfInputCon * ActivationOfInputNeuron (for each input) = ActivationOfNewNeuron (+ bias with sigmoid func)
    
    std::vector<float> inputLayer;
    inputLayer.reserve(boardVec.size() * boardVec[0].size());
    for(auto i: boardVec){
        for(auto j = 0; j <= i.size(); ++j){
            inputLayer.push_back(static_cast<float>(i[j]));
        }
    }
    
    for(auto i: hiddenLayer){ // iterate through neurons
        for(auto j = 0; j <= i.connectionVec.size(); ++j){ // iterate through connections

            i.value += i.connectionVec[j].weight * inputLayer[j];

        }
        i.sigmoid();
    }
    for(auto i: hiddenLayer2){
        for(auto j = 0; j <= hiddenLayer.size(); ++j){

            i.value += i.connectionVec[j].weight * hiddenLayer[j].value;

        }
        i.sigmoid();
    }
    for(auto i: outputLayer){
        for(auto j = 0; j <= hiddenLayer2.size(); ++j){

            i.value += i.connectionVec[j].weight * hiddenLayer2[j].value;

        }
        i.sigmoid();
    }
    
    // return highest value in final layer?
    return highestOutput();
    
}

float network::highestOutput(){
    float highestValue = outputLayer[0].value;
    for(auto i = 1; i < outputLayer.size(); ++i){
        if(outputLayer[i].value > highestValue){
            highestValue = outputLayer[i].value;
        }
    }
    return std::round(highestValue);
}

void network::mutate(){
    
    std::uniform_int_distribution<int> netsizeDistribution(0, NETSIZE);
    std::uniform_int_distribution<int> connectionDistribution1(0, hiddenLayer[0].connectionVec.size() * NETSIZE); // track amount of connections in one layer?
    std::uniform_int_distribution<int> connectionDistribution2(0, hiddenLayer2[0].connectionVec.size() * NETSIZE);
    std::uniform_int_distribution<int> connectionDistribution3(0, outputLayer[0].connectionVec.size() * NETSIZE); // only need one?
    std::uniform_real_distribution<float> weightDistribution(0, 1);


    for(auto i = 0; i < MUTATESPERLAYER; ++i){
        hiddenLayer[netsizeDistribution(engine)].connectionVec[connectionDistribution1(engine)].weight = weightDistribution(engine);
    }
    for(auto i = 0; i < MUTATESPERLAYER; ++i){
        hiddenLayer2[netsizeDistribution(engine)].connectionVec[connectionDistribution2(engine)].weight = weightDistribution(engine);
    }
    for(auto i = 0; i < MUTATESPERLAYER; ++i){
        outputLayer[netsizeDistribution(engine)].connectionVec[connectionDistribution3(engine)].weight = weightDistribution(engine);
    }

}