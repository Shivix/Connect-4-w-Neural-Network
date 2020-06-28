cmake_minimum_required(VERSION 3.15)
project(Genetic_Neural_Network)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES
        include/GNN/agent.hpp
        include/GNN/network.hpp
        include/GNN/layer.hpp
        include/GNN/neuron.hpp)

add_executable(Genetic_Neural_Network ${SOURCES} ${INCLUDES} src/main.cpp test.cpp test.hpp)

#add_library(Genetic_Neural_Network INTERFACE ${INCLUDES} ${SOURCES})
#set_target_properties(Genetic_Neural_Network PROPERTIES LINKER_LANGUAGE CXX)