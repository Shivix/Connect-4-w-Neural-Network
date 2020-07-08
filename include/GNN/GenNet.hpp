#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP

#include <algorithm>
#include "network.hpp"

namespace GNN{
    template<typename T>
    class GenNet{
    public:
        explicit GenNet(std::vector<T>* input, int numberOfLayers, int neuronsPerLayer, int maxPop):
        maxPop(maxPop),
        input(input),
        numberOfLayers(numberOfLayers),
        neuronsPerLayer(neuronsPerLayer)
        {
            static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Must be integral or floating point type"); // Helps to avoid bad types being used with the template
            for(auto i = 0; i < maxPop; ++i){
                generation.emplace_back(network<T>(input, numberOfLayers, neuronsPerLayer)); // gives GenNet a full generation of networks to compare fitness
            }
        }
        
        std::vector<network<T>> generation;

        void cullAndReplacePop(int numToCull){ // deletes x amount of networks and replaces with new ones with random weights (helps to maintain a varied population)
            sortFittest();
            for(auto i = generation.size() - numToCull; i < generation.size(); ++i){
                generation.erase(generation.begin() + i);
                generation.emplace_back(network<T>(input, numberOfLayers, neuronsPerLayer));
            }
        }

        void crossoverWithFittest(){ // replaces half of the neurons of each network with the fittest network's
            sortFittest();
            for(std::size_t i = 1; i < generation.size(); ++i){
                generation[0].crossover(generation[i]);
            }
        }
        
        void mutateAll(int mutatesPerLayer){ // replaces x amount of weights with new random weights
            for(auto&& i: generation){
                i.mutate(mutatesPerLayer);
            }
        }

    protected:
        int maxPop;
        void sortFittest(){ // find fittest networks to keep
            if(generation[0].fitness == -1){
                std::cout << "Fitness not set" << std::endl;
                //throw "Fitness not set";
            }
            std::sort(generation.begin(), generation.end(), [](const network<T>& a, const network<T>& b) { // sorts networks in descending order by fitness
                return a.fitness > b.fitness;
            });
        } // order networkVec in descending order of fitness Run for offspring AND parents together to ensure no regression
    private:
        std::vector<T>* input = nullptr;
        int numberOfLayers;
        int neuronsPerLayer;
    };
}


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
