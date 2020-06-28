#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP

#include <algorithm>
#include "network.hpp"

namespace GNN{
    template<typename T>
    class agent{
    public:
        explicit agent(std::vector<T>* input, int numberOfLayers, int neuronsPerLayer){
            static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Must be integral or floating point type"); // Helps to avoid bad types being used with the template
            for(auto i = 0; i < maxPop; ++i){
                generation.emplace_back(network<T>(input, numberOfLayers, neuronsPerLayer)); // gives agent a full generation of networks to compare fitness
            }
        }
        ~agent()= default;
        std::vector<network<T>> generation;
        
    private:
        const int maxPop = 10;
        void sortFittest(){ // find fittest networks to keep
    
            std::sort(generation.begin(), generation.end(), [](const network<T>& a, const network<T>& b) { // sorts networks in descending order by fitness
                return a.fitness > b.fitness;
            });
        } // order networkVec in descending order of fitness Run for offspring AND parents together to ensure no regression
    
        void cullHalfPop(){
            sortFittest();
            generation.erase(generation.begin() + (maxPop / 2), generation.end()); // removes half of the networks with the lowest fitness.
        }
    
    
    };
}


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_AGENT_HPP
