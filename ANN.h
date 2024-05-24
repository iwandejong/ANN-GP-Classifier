#ifndef ANN_H
#define ANN_H

#include <iostream>
#include <vector>

#include "Mushroom.h"
#include "Node.h"

class ANN {
    private:
        std::vector<Mushroom*> trainData;
        std::vector<Mushroom*> testData;

        const int numInputs = 8;
        const int numOutputs = 1;
        const int numHiddenLayers = 1;
        const int numNeuronsPerHiddenLayer = 8;
        
        float learningRate = 0.1;

        std::vector<Node*> inputLayer;
        std::vector<std::vector<Node*>> hiddenLayers;
        std::vector<Node*> outputLayer;

        int stoppingCriteria = 1000;
    public:
        ANN(int stoppingCriteria = 1000, float learningRate = 0.1);
        ~ANN();
        void addMushroomToTrain(Mushroom* m);
        void addMushroomToTest(Mushroom* m);
        void print();
        void train();
        void test();
        bool classify(Mushroom* m);

        void visualize();

        // void feedforward(Mushroom* m);
        // void backpropagation();
        // void updateWeights();

        void trainHelper(Mushroom* m);

        float sigmoid(float x);
        float sigmoidDerivative(float x);
        float getRandomFloat();

        int getIndexOfMushroom(Mushroom* m);

        float relu(float x);
};

#endif // ANN_H