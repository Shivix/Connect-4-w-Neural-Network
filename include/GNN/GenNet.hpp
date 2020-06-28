#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP

#include <algorithm>
#include "network.hpp"

namespace GNN{
    template<typename T>
    class GenNet{
    public:
        explicit inline GenNet(std::vector<T>* input, int numberOfLayers, int neuronsPerLayer, int maxPop):
        input(input),
        numberOfLayers(numberOfLayers),
        neuronsPerLayer(neuronsPerLayer),
        maxPop(maxPop)
        {
            static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Must be integral or floating point type"); // Helps to avoid bad types being used with the template
            for(auto i = 0; i < maxPop; ++i){
                generation.emplace_back(network<T>(input, numberOfLayers, neuronsPerLayer)); // gives GenNet a full generation of networks to compare fitness
            }
        }
        ~GenNet()= default;
        std::vector<network<T>> generation;
        virtual void setFitness() = 0; // will dictate how the fitness of each network is decided.
        
        void cullAndReplacePop(int numToCull){
            sortFittest();
            for(auto i = generation.size() - numToCull; i < generation.size(); ++i){// removes half of the networks with the lowest fitness.
                generation.pop_back();
                generation.emplace_back(network<T>(input, numberOfLayers, neuronsPerLayer));
            }
        }
    protected:
        int maxPop = 10;
        void sortFittest(){ // find fittest networks to keep
            if(generation[0].fitness == -1){
                std::cout << "Fitness not set" << std::endl;
                //throw "Fitness not set";
            }
            std::sort(generation.begin(), generation.end(), [](const network<T>& a, const network<T>& b) { // sorts networks in descending order by fitness
                return a.fitness > b.fitness;
            });
        } // order networkVec in descending order of fitness Run for offspring AND parents together to ensure no regression
        void crossoverFittest(){
            sortFittest();
            for(auto i = 1; i < generation.size(); ++i){
                generation[0].crossover(generation[i]);
            }
        }
    private:
        std::vector<T>* input;
        int numberOfLayers;
        int neuronsPerLayer;
    };
}


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
