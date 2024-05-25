// Iwan de Jong, u22498037

#ifndef GP_NODE_H
#define GP_NODE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "Mushroom.h"

class GP_Node {
    private:
        float input = 0.0;
        GP_Node* left;
        GP_Node* right;
        float fitness = 0.0;

        int operation = -1;
    public:
        GP_Node(float i = 0.0);
        ~GP_Node();
        void print(int level);
        float getInput();
        void setInput(float i);
        float activationFunction(float x);

        GP_Node* getLeft();
        GP_Node* getRight();
        void setLeft(GP_Node* l);
        void setRight(GP_Node* r);
        void setFitness(float f);
        float getFitness();
        void generateTree(int depth, int numFeatures, const std::vector<Mushroom*>& trainData);
        
        bool isLeaf();
        GP_Node* copy(GP_Node* n);
        void crossover(GP_Node* n);
        void mutate();

        int getDepth();

        void setOperation(int op);
        int getOperation();

        GP_Node* getRandomGP_Node();

        float classifyBase(Mushroom* m);
        float classify(Mushroom* m, int numFeatures);
};

#endif // GP_NODE_H