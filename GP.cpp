#include "GP.h"

GP::GP() {
    trainData = std::vector<Mushroom*>();
    testData = std::vector<Mushroom*>();
    population = std::vector<GP_Node*>();
}

GP::~GP() {}

void GP::addMushroomToTrain(Mushroom* m) {
    trainData.push_back(m);
}

void GP::addMushroomToTest(Mushroom* m) {
    testData.push_back(m);
}

void GP::generatePopulation() {
    for (int i = 0; i < populationSize; i++) {
        population.push_back(new GP_Node());
        generateTree(maxDepth, population[i]);
        // Evaluate fitness for each individual after generating the tree
        // random fitness
        // between -0.5 and 0.5
        float fitness = (std::rand() % 100) / 100.0 - 0.5;
        population[i]->setFitness(fitness);
        // Print each individual's tree and fitness
        // std::cout << "Fitness: " << std::fixed << fitness << std::endl;
        // print(population[i]);
    }

    // Find the best individual and update maxFitness and bestIndividual accordingly
    for (int i = 0; i < populationSize; i++) {
        if (population[i]->getFitness() > maxFitness) {
            maxFitness = population[i]->getFitness();
            bestIndividual = population[i];
        }
    }
}


void GP::tournamentSelection() {
    for (int i = 0; i < populationSize; i++) {
        GP_Node* parent1 = getRandomIndividual(population[i]);
        GP_Node* parent2 = getRandomIndividual(population[i]);
        GP_Node* pop = population[i];
        crossover(parent1, parent2);

        if (pop->getFitness() > maxFitness) {
            maxFitness = pop->getFitness();
            bestIndividual = pop;
        }
    }
}

GP_Node* GP::getRandomIndividual(GP_Node* h) {
    return h->getRandomGP_Node();
}

void GP::crossover(GP_Node* parent1, GP_Node* parent2) {
    // change two parents with each other
    // using crossover rate
    if (std::rand() % 100 < crossoverRate * 100) {
        GP_Node* temp = parent1->copy(parent1);
        parent1->crossover(parent2);
        parent2->crossover(temp);
    }
    // then mutate the children
    mutation(parent1);
    mutation(parent2);
}

void GP::mutation(GP_Node* individual) {
    if (std::rand() % 100 < mutationRate * 100) {
        individual->mutate();
    }
}

void GP::generateTree(int depth, GP_Node* h) {
    h->generateTree(depth, numFeatures, trainData);
}

void GP::train() {
    // Evolution loop
    // GP_error
    std::ofstream file("GP_error.csv");
    file << "Generation,TrainingAcc" << std::endl;

    for (int generation = 0; generation < numGenerations; generation++) {
        // // Evaluate fitness for each individual
        // for (int i = 0; i < populationSize; i++) {
        //     float fit = evaluateFitness(population[i], trainData[i]);
        //     population[i]->setFitness(fit);
        // }

        // Select individuals for reproduction
        for (int i = 0; i < populationSize; i++) {
            tournamentSelection();
        }

        float trainingAccuracy = calculateAccuracy(trainData, bestIndividual);
        std::cout << "Generation " << generation << " - Training Accuracy: " << trainingAccuracy << std::endl;

        // write this to GP_error.csv
        std::ofstream file("GP_error.csv", std::ios_base::app);
        file << generation << "," << trainingAccuracy << std::endl;
    }

    float testingAccuracy = calculateAccuracy(testData, bestIndividual);
    std::cout << "Testing Accuracy: " << testingAccuracy << std::endl;
}

void GP::test() {
    float correct = 0.0;

    std::cout << "Output\t\tActual\tExpected" << std::endl;

    std::vector<bool> allPredicted = std::vector<bool>();
    std::vector<bool> allActual = std::vector<bool>();
    std::vector<float> outputs = std::vector<float>();

    for (int i = 0; i < testData.size(); i++) {
        // float outputValue = feedforward(testData[i], false);
        // bool predicted = classify(testData[i]);
        // bool expected = testData[i]->getMushroomClass();

        float outputValue = classify(testData[i], bestIndividual);
        float predicted = outputValue < 0.8;
        float expected = testData[i]->getMushroomClass();

        allPredicted.push_back(predicted);
        allActual.push_back(expected);
        outputs.push_back(outputValue);

        if (predicted == expected) {
            std::cout << "\033[32m" << std::fixed << outputValue << "\t" << predicted << "\t\t" << expected << "\033[0m" << std::endl;
            correct++;
        }
        else {
            std::cout << "\033[31m" << std::fixed << outputValue << "\t" << predicted << "\t\t" << expected << "\033[0m" << std::endl;
        }
    }
    
    std::cout << std::endl << "\033[34m" << "Statistics" << "\033[0m" << std::endl;
    stats(allPredicted, allActual);

    std::cout << std::endl << "\033[36m" << "Output Statistics:" << "\033[0m" << std::endl;
    float mean = 0.0f;
    for (int i = 0; i < outputs.size(); i++) {
        mean += outputs[i];
    }
    mean /= outputs.size();
    std::cout << "Mean: " << mean << std::endl;

    float variance = 0.0f;
    for (int i = 0; i < outputs.size(); i++) {
        variance += pow(outputs[i] - mean, 2);
    }
    variance /= outputs.size();
    std::cout << "Variance: " << variance << std::endl;

    float stdDev = sqrt(variance);
    std::cout << "Standard Deviation: " << stdDev << std::endl;

    float maxVal = outputs[0];
    float minVal = outputs[0];
    for (int i = 0; i < outputs.size(); i++) {
        if (outputs[i] < minVal) minVal = outputs[i];
        if (outputs[i] > maxVal) maxVal = outputs[i];
    }
    float range = maxVal - minVal;
    std::cout << "Range: " << range << std::endl << std::endl;

    outputsToCSV();
}

// bool GP::classify(Mushroom* m, GP_Node* h) {
//     float fitness = evaluateFitness(h);
//     // std::cout << fitness << std::endl;
//     return evaluateFitness(h) > 0.5;
// }

float GP::classify(Mushroom* m, GP_Node* h) {
    float fitness = h->classifyBase(m);
    return sigmoid(fitness);
}

void GP::print(GP_Node* head) {
    head->print(head->getDepth());
}

// float GP::evaluateFitness(GP_Node* individual, Mushroom* data) {
//     // std::cout << individual->getLeft() << std::endl;
//     // std::cout << individual->getRight() << std::endl;
//     // individual->evaluateFitness(trainData);

//     // traverse the tree and evaluate the fitness starting at individual
//     return individual->classify(data);
// }

// float GP::evaluateFitnessHelper(GP_Node* n) {
//     // Implementation of the evaluateFitnessHelper function
//     if (n == nullptr) {
//         return 0.0f;
//     }
//     if (n->isLeaf()) {
//         return n->getFitness();
//     }

//     float leftValue = 0.0f;
//     float rightValue = 0.0f;

//     if (n->getLeft() != nullptr) {
//         leftValue = evaluateFitnessHelper(n->getLeft());
//     }

//     if (n->getRight() != nullptr) {
//         rightValue = evaluateFitnessHelper(n->getRight());
//     }

//     switch (n->getOperation()) {
//         case 0:
//             return leftValue + rightValue;
//         case 1:
//             return leftValue - rightValue;
//         case 2:
//             return leftValue * rightValue;
//         case 3:
//             return rightValue != 0.0f ? leftValue / rightValue : 0.0f;
//         case 4:
//             return pow(leftValue, rightValue);
//         case 5:
//             return sin(leftValue);
//         case 6:
//             return cos(rightValue);
//         default:
//             return 0.0;
//     }
// }

float GP::sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

void GP::stats(const std::vector<bool>& predicted, const std::vector<bool>& actual) {
    int truePositive = 0;
    int falsePositive = 0;
    int trueNegative = 0;
    int falseNegative = 0;

    for (size_t i = 0; i < predicted.size(); ++i) {
        if (predicted[i] == true && actual[i] == true) {
            truePositive++;
        } else if (predicted[i] == true && actual[i] == false) {
            falsePositive++;
        } else if (predicted[i] == false && actual[i] == true) {
            falseNegative++;
        } else if (predicted[i] == false && actual[i] == false) {
            trueNegative++;
        }
    }

    // Precision = True Positives / (True Positives + False Positives)
    float precision = static_cast<float>(truePositive) / (truePositive + falsePositive);

    // Recall = True Positives / (True Positives + False Negatives)
    float recall = static_cast<float>(truePositive) / (truePositive + falseNegative);

    // Accuracy = (True Positives + True Negatives) / Total
    float accuracy = static_cast<float>(truePositive + trueNegative) / predicted.size();

    // F1 Score = 2 * (Precision * Recall) / (Precision + Recall)
    float f1Score = 2.0f * (precision * recall) / (precision + recall);

    std::cout << "Precision: " << precision << std::endl;
    std::cout << "Recall: " << recall << std::endl;
    std::cout << "Accuracy: " << accuracy << std::endl;
    std::cout << "F1 Score: " << f1Score << std::endl;
}

void GP::outputsToCSV() {
    std::ofstream file("GP_outputs.csv");
    file << "Output,Actual,Expected" << std::endl;

    for (int i = 0; i < testData.size(); i++) {
        float outputValue = classify(testData[i], bestIndividual);
        bool predicted = outputValue < 0.8;
        bool expected = testData[i]->getMushroomClass();
        file << outputValue << "," << predicted << "," << expected << std::endl;
    }
    file.close();

    std::cout << "Outputs written to GP_outputs.csv" << std::endl;
}

float GP::calculateAccuracy(const std::vector<Mushroom*>& data, GP_Node* individual) {
    float correct = 0.0;
    for (int i = 0; i < data.size(); i++) {
        float outputValue = classify(data[i], individual);
        bool predicted = outputValue < 0.8;
        bool expected = data[i]->getMushroomClass();
        if (predicted == expected) {
            correct++;
        }
    }
    return correct / data.size();
}
