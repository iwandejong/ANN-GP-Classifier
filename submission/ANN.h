// Iwan de Jong, u22498037

#ifndef ANN_H
#define ANN_H

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <fstream>

#include "Mushroom.h"
#include "Node.h"

class ANN {
    private:
        std::vector<Mushroom*> trainData;
        std::vector<Mushroom*> testData;

        const int numInputs = 8;
        const int numOutputs = 1;
        const int numHiddenLayers = 1;
        const int numNeuronsPerHiddenLayer = 16;
        
        float learningRate = 0.1;

        std::vector<Node*> inputLayer;
        std::vector<std::vector<Node*>> hiddenLayers;
        std::vector<Node*> outputLayer;

        float inputBias = 1.0;
        std::vector <float> hiddenBias;
        float outputBias = 1.0;

        std::vector<std::vector<float>> weights;
        std::vector<std::vector<float>> outputWeights;

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

        // void backpropagation();
        // void updateWeights();

        void trainHelper(Mushroom* m, std::ofstream& file);
        float feedforward(Mushroom* m, bool training = true);

        float sigmoid(float x);
        float sigmoidDerivative(float x);
        float getRandomFloat();

        int getIndexOfMushroom(Mushroom* m);

        float calculateLoss();
        // float getRandomAlt(int numInputs);
        void stats(const std::vector<bool>& predicted, const std::vector<bool>& actual);

        void outputsToCSV();
};

#endif // ANN_H