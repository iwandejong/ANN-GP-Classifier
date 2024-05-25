#include "Node.h"

Node::Node(float i) : input(i) {}

Node::~Node() {}

void Node::print() {
    std::cout << "Input: " << std::fixed << std::setprecision(2) << input << std::endl;
}

float Node::getInput() {
    return input;
}

void Node::setInput(float i) {
    input = i;
}

float Node::activationFunction(float x) {
    return 1 / (1 + exp(-x));
}