#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP

#include <iostream>
#include "layer.hpp"

namespace GNN{
    template<typename T>
    class network{
    public:
        explicit network(std::vector<T>* inputLayer, const int& numberOfLayers, const int& neuronsPerLayer):
        neuronsPerLayer(neuronsPerLayer),
        inputLayer(inputLayer)
        {
            layerVec.reserve(numberOfLayers);
            layerVec.emplace_back(layer(inputLayer->size())); // adds input layer
            for(auto i = 1; i < numberOfLayers - 2; ++i){
                layerVec.emplace_back(layer(neuronsPerLayer)); // adds x amount of hidden layers
            }
            layerVec.emplace_back(layer(neuronsPerLayer)); // adds the output layer
        }
        
        int fitness = -1;
    
        void crossover(const network& mate){ // combine half of the neurons of one network with another
            std::uniform_int_distribution<int> netsizeDistribution(0, neuronsPerLayer - 1);
            int neuronToCrossover;
            for(std::size_t i = 1; i < layerVec.size(); ++i){ // this will often copy over a neuron that has already been copied meaning the network that calls the function will have the dominant genome (temp)
                neuronToCrossover = netsizeDistribution(engine);
                this->layerVec[i].getNeuronVec()[neuronToCrossover] = mate.layerVec[i].getNeuronVec()[neuronToCrossover];
            }
        }
        void drawNetwork(){ // gives visual feedback for test purposes.
            for(auto&& i: layerVec){
                std::cout << "=============================================LAYER DIVIDER============================================\n";
                for(auto&& j: i.getNeuronVec()){
                    for(auto&& k: j.getConnectionVec()){
                        std::cout << k;
                    }
                    std::cout << "Value:" << j.value << "\n";
                }
            }
        }
        void feedForward(){
            layerVec[0].feed(*inputLayer);
            for(std::size_t i = 1; i < layerVec.size(); ++i){
                layerVec[i].feed(layerVec[i - 1]);
            }
        }
        void orderOutput(){ // orders the output layer in descending order of value to easily refer to greatest one.
            auto outputLayer = layerVec.back().getNeuronVec();
            std::sort(outputLayer.rbegin(), outputLayer.rend());
        }
        void mutate(const int& mutatesPerLayer){
            std::uniform_int_distribution<int> neuronDistribution(0, (neuronsPerLayer - 1));
            std::uniform_int_distribution<int> connectionDistribution(0, neuronsPerLayer - 1); // track amount of connections in one layer?
            for(std::size_t i = 1; i < layerVec.size(); ++i){ // starts at 1 to avoid mutating the input layer
                for(auto j = 0; j < mutatesPerLayer; ++j){
                    layerVec[i].getNeuronVec()[neuronDistribution(engine)].getConnectionVec()[connectionDistribution(engine)].weight = weightDistribution(engine);
                }
            }
        }
        std::vector<layer> layerVec = {}; // contains hidden layers and output layer.
        
    private:
        int neuronsPerLayer = -1;
        std::vector<T>* inputLayer = nullptr; // stored as pointer to the source of the input layer to ensure input layer is kept up to date
    };
}


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NETWORK_HPP