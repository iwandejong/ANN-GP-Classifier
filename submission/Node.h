// Iwan de Jong, u22498037

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>

class Node {
    private:
        float input;
    public:
        Node(float i = 0.0);
        ~Node();
        void print();
        float getWeight();
        float getBias();
        float getInput();
        void setInput(float i);
        float activationFunction(float x);
};

#endif // NODE_H