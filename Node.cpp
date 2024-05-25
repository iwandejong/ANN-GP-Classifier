#include "Node.h"

Node::Node(float i) : input(i) {}

Node::~Node() {}

void Node::print() {
    // Implementation of the print function as float
    std::cout << "Input: " << std::fixed << std::setprecision(2) << input << std::endl;
}

float Node::getInput() {
    // Implementation of the getInput function
    return input;
}

void Node::setInput(float i) {
    // Implementation of the setInput function
    input = i;
}

float Node::activationFunction(float x) {
    // Implementation of the activationFunction function
    // Sigmoid activation function
    return 1 / (1 + exp(-x));
}