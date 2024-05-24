#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
    private:
        float weight;
        float bias;
        float input;
    public:
        Node(float w = 0.0, float b = 0.0, float i = 0.0);
        ~Node();
        void print();
        float getWeight();
        float getBias();
        float getInput();
        void setWeight(float w);
        void setBias(float b);
        void setInput(float i);
        float activationFunction(float x);
};

#endif // NODE_H