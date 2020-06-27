# Genetic Neural Network

A neural network implementation that mimics natural selection to train it's networks.

## Neuron
Each neuron is made up of a value and multiple connections to other neurons. In the current implementation
each connection is an **incoming** connection to the neuron.

Each connection has a weight that is initially randomized between -1 and 1 but may change through mutation.

## Mutation
The mutation function simply replaces a set amount of weights with a new random weight.

The amount of mutations is dependant on the value of MUTATES_PER_LAYER. More will help provide variation in the
population, however too much will hinder the training.

## Crossover
Crossover is a way to have 2 parent networks produce a child network that contains half of each parents 
neurons.

## Feed Forward
This is effectively how a network *makes a decision*. The weight of a connection is multiplied
by the value of the neuron it connects to and the result is added to the value of the current neuron. This
is repeated for each incoming neuron. The value is then passed through a sigmoid function to ensure
non-linearity.

# How to use on your own data set

Please refer to the [Wiki](https://github.com/Shivix/Genetic-Neural-Network/wiki)