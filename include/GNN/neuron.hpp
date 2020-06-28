#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
#include <random>
#include <vector>

namespace GNN{
    static std::random_device randomDevice;
    static std::mt19937 engine(randomDevice());

    class neuron{
    public:
        explicit neuron(int connections){
            static std::uniform_real_distribution<float> randomDistribution(-1, 1.0);
            connectionVec.resize(connections);
            int inputIter = -1;
            for(auto&& i: connectionVec){
                i.weight = randomDistribution(GNN::engine);
                i.input = ++inputIter;
            }
        }
        neuron(const neuron &neuron) = default;
        ~neuron()= default;
    
    
    public:
        float value = 0.0f;
        struct connection{ // connections going IN to the neuron
            float weight;
            int input;
        };
        std::vector<connection> getConnectionVec(){
            return connectionVec;
        }
        template <typename charT, typename traits>
        friend std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits>& os, const GNN::neuron::connection& connection){// makes the content of a neuron easier to output.
            os << "Weight:" << connection.weight << "from:" << connection.input << "neuron\n";
            return os;
        }
        void sigmoid() { // runs when a neuron is fed from all previous neurons
            value = value / (1 + (std::abs(value)));
        }
        void tanh() const { // runs when a neuron is fed from all previous neurons
            std::tanh(value);
        }

        typedef void (*func)(float a);
        void activation(func activationFunc) const{
            activationFunc(value);
        }
        
    private:
        float bias = 0;
        
        std::vector<connection> connectionVec;
    };
}



#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
