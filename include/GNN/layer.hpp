#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP

#include "neuron.hpp"

namespace GNN{
    class layer{
    public:
        explicit inline layer(int neurons){
            for(auto i = 0; i < neurons; ++i){
                neuronVec.emplace_back(neuron(neurons));
            }
        }
        ~layer()= default;
    public:
        void feed(const layer& prevLayer){
            for(auto&& i: this->neuronVec){
                for(auto&& j: i.getConnectionVec()){
                    i.value += (j.weight * prevLayer.neuronVec[j.input].value);
                }
                i.sigmoid();
            }
        }

        template<typename T>
        void feed(const std::vector<T>& inputLayer){ // template used to make less restrictive. Restriction currently still exists at higher level
            for(auto&& i: this->neuronVec){
                for(auto&& j: i.getConnectionVec()){
                    i.value += (j.weight * inputLayer[j.input]);
                }
                i.sigmoid();
            }
        }
        std::vector<neuron> neuronVec = {};
    };
}



#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_LAYER_HPP