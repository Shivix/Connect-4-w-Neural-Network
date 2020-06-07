#ifndef CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
#define CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
#include <random>
#include <vector>

static std::random_device randomDevice; // use boost random?
static std::mt19937 engine(randomDevice());


class neuron{
public:
    neuron(int);
    neuron(neuron const&);
    ~neuron();


public:
    
    float value = 0; // TODO: value is getting reset seemingly at the end of feedForward()
    struct connection{
        float weight;
        int input;
    };
    std::vector<connection> getConnectionVec();

    
    void sigmoid();
    
private:

    float bias = 0;


    void activation();
    std::vector<connection> connectionVec;
    
};


#endif //CONNECT4_WITH_REINFORCEMENT_LEARNING_NEURON_HPP
