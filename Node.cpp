#include "Node.h"

Node::Node(float w, float b, float i) : weight(w), bias(b), input(i) {}

Node::~Node() {}

void Node::print() {
    // Implementation of the print function
    std::cout << "Weight: " << weight << std::endl;
    std::cout << "Bias: " << bias << std::endl;
}

float Node::getWeight() {
    // Implementation of the getWeight function
    return weight;
}

float Node::getBias() {
    // Implementation of the getBias function
    return bias;
}

float Node::getInput() {
    // Implementation of the getInput function
    return input;
}

void Node::setWeight(float w) {
    // Implementation of the setWeight function
    weight = w;
}

void Node::setBias(float b) {
    // Implementation of the setBias function
    bias = b;
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