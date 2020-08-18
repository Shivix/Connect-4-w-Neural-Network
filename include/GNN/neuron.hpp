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
        explicit neuron(const int& connections){ // randomly sets all weights and adds the connections to a vector
            connectionVec.resize(connections);
            int inputIter = -1;
            for(auto&& i: connectionVec){
                i.weight = weightDistribution(engine);
                i.input = ++inputIter;
            }
        }
        neuron(const neuron& other) = default; // rule of zero could easily (and should) be followed here, but I decided to implement the move constructor and assignment myself
        neuron(neuron&& other) noexcept{
            *this = std::move(other);
        };
        ~neuron()= default;
        neuron& operator = (const neuron& other) = default;
        neuron& operator = (neuron&& other) noexcept{
            this->value = std::move(other.value);
            this->connectionVec = std::move(other.connectionVec);
            other.connectionVec.clear();
            this->bias = std::move(other.bias);
            return *this;}
    public:
        float value = 0.0f;
        struct connection{ // connections going IN to the neuron
            float weight;
            int input;
        };
        
        void activation(std::function<void(float)> activationFunc){ // can allow the library user to provide their own nonlinear function
            activationFunc(value);
        }
        [[nodiscard]] auto getConnectionVec() const{ // provides better encapsulation since connectionVec should never be edited outside of the class
            return connectionVec;
        }
        void sigmoid() { // runs when a neuron is fed from all previous neurons
            value = value / (1 + std::abs(value));
        }
        void tanh() const { // runs when a neuron is fed from all previous neurons
            std::tanh(value);
        }
        template <typename charT, typename traits>
        friend std::basic_ostream<charT,traits>& operator << (std::basic_ostream<charT,traits>& os, const connection& connection){// makes the content of a neuron easier to output.
            os << "Weight:" << connection.weight << "from:" << connection.input << "neuron\n";
            return os;
        }
        friend bool operator > (const neuron& neuron1, const neuron& neuron2){
            return neuron1.value > neuron2.value;
        }
        friend bool operator < (const neuron& neuron1, const neuron& neuron2){
            return neuron1.value < neuron2.value;
        }
    private:
        float bias = 0;
        std::vector<connection> connectionVec = {};
    };
}



#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
