#ifndef GP_H
#define GP_H

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <fstream>
#include "GP_Node.h"
#include "Mushroom.h"

class GP {
    private:
        int maxDepth = 4;
        int numFeatures = 8;
        int numClasses = 2;
        int populationSize = 100;
        int numGenerations = 50;
        float mutationRate = 0.08;
        float crossoverRate = 0.7;
        float maxFitness = 0.0;
        GP_Node* bestIndividual = nullptr;

        std::vector<Mushroom*> trainData;
        std::vector<Mushroom*> testData;

        std::vector<GP_Node*> population;
       
    public:
        GP();
        ~GP();

        void addMushroomToTrain(Mushroom* m);
        void addMushroomToTest(Mushroom* m);
        void generatePopulation();

        // float evaluateFitness(GP_Node* individual, Mushroom* m);
        // float evaluateFitnessHelper(GP_Node* n);

        void tournamentSelection();
        void crossover(GP_Node* parent1, GP_Node* parent2);
        void mutation(GP_Node* individual);
        void generateTree(int depth, GP_Node* h);

        GP_Node* getRandomIndividual(GP_Node* h);

        void train();
        void test();
        float classify(Mushroom* m, GP_Node* h);

        void print(GP_Node* head);

        float sigmoid(float x);

        void stats(const std::vector<bool>& predicted, const std::vector<bool>& actual);
        void outputsToCSV();

        float calculateAccuracy(const std::vector<Mushroom*>& data, GP_Node* individual);
};

#endif // GP_H