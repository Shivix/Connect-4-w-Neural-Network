cmake_minimum_required(VERSION 3.15)
project(Genetic_Neural_Network)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/layer.cpp
        src/neuron.cpp)

set(INCLUDES
        GNN/include/agent.hpp
        GNN/include/network.hpp
        GNN/include/layer.hpp
        GNN/include/neuron.hpp)

add_executable(Genetic_Neural_Network ${SOURCES} ${INCLUDES} src/main.cpp test.cpp test.hpp)

#add_library(Genetic_Neural_Network STATIC ${INCLUDES} ${SOURCES})
#set_target_properties(Genetic_Neural_Network PROPERTIES LINKER_LANGUAGE CXX)