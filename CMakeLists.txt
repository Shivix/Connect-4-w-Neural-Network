cmake_minimum_required(VERSION 3.15)
project(Genetic_Neural_Network)

set(CMAKE_CXX_STANDARD 17)

add_executable(Genetic_Neural_Network src/main.cpp include/network.hpp src/neuron.cpp include/neuron.hpp include/agent.hpp src/layer.cpp include/layer.hpp test.cpp test.hpp)

#add_library(Genetic_Neural_Network include/network.hpp src/neuron.cpp include/neuron.hpp include/agent.hpp src/layer.cpp include/layer.hpp)
