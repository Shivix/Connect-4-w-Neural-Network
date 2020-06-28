#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
#include <random>
#include <vector>

namespace GNN{
    static std::random_device randomDevice; // used to seed RNG engine. Will attempt to use hardware entropy if possible
    static std::mt19937 engine(randomDevice()); // Mersenne-twister engine used for random number generation
    static std::uniform_real_distribution<float> weightDistribution(-1, 1.0); // calling as static gives less overhead
    
    class neuron{
    public:
        explicit inline neuron(int connections){ // randomly sets all weights and adds the connections to a vector
            connectionVec.resize(connections);
            int inputIter = -1;
            for(auto&& i: connectionVec){
                i.weight = weightDistribution(engine);
                i.input = ++inputIter;
            }
        }
        neuron(const neuron& neuron) = default;
        neuron(neuron&& neuron):
            value(std::move(neuron.value)),
            connectionVec(std::move(neuron.connectionVec)),
            bias(neuron.bias)
        {};
        ~neuron()= default;
        
    public:
        float value = 0.0f;
        struct connection{ // connections going IN to the neuron
            float weight;
            int input;
        };
        
        typedef void (*func)(float a);
        void activation(func activationFunc) const{
            activationFunc(value);
        }
        inline auto getConnectionVec() -> std::vector<connection>& {
            return connectionVec;
        }
        void sigmoid() { // runs when a neuron is fed from all previous neurons
            value = value / (1 + std::abs(value));
        }
        void tanh() const { // runs when a neuron is fed from all previous neurons
            std::tanh(value);
        }
        template <typename charT, typename traits>
        friend std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits>& os, const connection& connection){// makes the content of a neuron easier to output.
            os << "Weight:" << connection.weight << "from:" << connection.input << "neuron\n";
            return os;
        }
        
    private:
        float bias = 0;
        std::vector<connection> connectionVec;
    };
}



#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
