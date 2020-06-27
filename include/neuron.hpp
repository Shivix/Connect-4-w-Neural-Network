#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
#include <random>
#include <vector>

namespace GNN{
    static std::random_device randomDevice;
    static std::mt19937 engine(randomDevice());

    class neuron{
    public:
        explicit neuron(int);
        neuron(const neuron&);
        ~neuron();
    
    
    public:
        float value = 0.0f;
        struct connection{ // connections going IN to the neuron
            float weight;
            int input;
        };
        std::vector<connection> getConnectionVec();
        template <typename charT, typename traits>
        friend std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits>& os, const GNN::neuron::connection& connection){// makes the content of a neuron easier to output.
            os << "Weight:" << connection.weight << "from:" << connection.input << "neuron\n";
            return os;
        }
        void sigmoid();
        
    private:
        float bias = 0;
    
        void activation();
        std::vector<connection> connectionVec;
    };
}



#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
