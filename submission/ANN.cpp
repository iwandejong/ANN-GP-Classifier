#include "ANN.h"

ANN::ANN(int stoppingCriteria, float learningRate) {
    trainData = std::vector<Mushroom*>();
    testData = std::vector<Mushroom*>();

    for (int i = 0; i < numInputs; i++) {
        inputLayer.push_back(new Node());
    }

    for (int i = 0; i < numHiddenLayers; i++) {
        std::vector<Node*> hiddenLayer;
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            hiddenLayer.push_back(new Node());
        }
        hiddenLayers.push_back(hiddenLayer);
    }

    for (int i = 0; i < numOutputs; i++) {
        outputLayer.push_back(new Node());
    }

    for (int i = 0; i < numInputs; i++) {
        std::vector<float> weight;
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            weight.push_back(getRandomFloat());
        }
        weights.push_back(weight);
    }

    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        std::vector<float> outputWeight;
        for (int j = 0; j < numOutputs; j++) {
            outputWeight.push_back(getRandomFloat());
        }
        outputWeights.push_back(outputWeight);
    }

    // visualize();

    inputBias = getRandomFloat();
    hiddenBias = std::vector<float>(numNeuronsPerHiddenLayer);
    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        hiddenBias[i] = getRandomFloat();
    }
    outputBias = getRandomFloat();

    this->stoppingCriteria = stoppingCriteria;
    this->learningRate = learningRate;
}

ANN::~ANN() {}

void ANN::addMushroomToTrain(Mushroom* m) {
    trainData.push_back(m);
}

void ANN::addMushroomToTest(Mushroom* m) {
    testData.push_back(m);
}

void ANN::print() {
    std::cout << "Training data size:" << std::endl;
    std::cout << trainData.size() << std::endl;
    std::cout << "Test data size:" << std::endl;
    std::cout << testData.size() << std::endl;
}

void ANN::train() {
    int i = 0;

    // visualize();

    std::ofstream file("error.csv");
    file << "Error" << std::endl;

    inputBias = getRandomFloat();

    while (i < stoppingCriteria) {
        // selects a random mushroom from the training data
        int randomIndex = rand() % trainData.size();
        trainHelper(trainData[randomIndex], file);
        // trainHelper(trainData[i]);
        
        if (i % 100 == 0) { // Print loss every 100 iterations
            float loss = calculateLoss();
            std::cout << "Iteration " << i << ", Error: " << loss << std::endl;
            if (i % 1000 == 0 && i > 0) {
                learningRate *= 0.9;
            }
        }
        i++;
    }

    std::cout << "After Training:" << std::endl;
    // visualize();

    // Test the neural network
    test();
}

void ANN::test() {
    // Test the neural network

    std::cout << "Output\t\tActual\tExpected" << std::endl;

    std::vector<bool> allPredicted = std::vector<bool>();
    std::vector<bool> allActual = std::vector<bool>();
    std::vector<float> outputs = std::vector<float>();

    int correct = 0;
    int total = 0;
    for (int i = 0; i < testData.size(); i++) {
        float outputValue = feedforward(testData[i], false);
        bool predicted = classify(testData[i]);
        bool expected = testData[i]->getMushroomClass();


        if (predicted == expected) {
            std::cout << "\033[32m" << std::fixed << outputValue << "\t" << predicted << "\t\t" << expected << "\033[0m" << std::endl;
            correct++;
        } else {
            std::cout << "\033[31m" << std::fixed << outputValue << "\t" << predicted << "\t\t" << expected << "\033[0m" << std::endl;
        }
        allActual.push_back(expected);
        allPredicted.push_back(predicted);
        outputs.push_back(outputValue);
        total++;
    }

    // std::cout << "Accuracy: " << (float)correct / total * 100 << "%" << std::endl;
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

bool ANN::classify(Mushroom* m) {
    // Classify the mushroom based on the output
    float outputValue = feedforward(m, false);
    // std::cout << "Pre-output: " << (float)outputValue << "%" << std::endl;
    bool returnValue = (outputValue < 0.5) ? true : false;
    return returnValue;
}

void ANN::visualize() {
    // Visualize the neural network using Nodes
    // std::cout << "Input Layer" << std::endl;
    // for (int i = 0; i < numInputs; i++) {
    //     inputLayer[i]->print();
    // }

    // std::cout << std::endl;
    // std::cout << "Hidden Layer" << std::endl;
    // for (int i = 0; i < numHiddenLayers; i++) {
    //     for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
    //         hiddenLayers[i][j]->print();
    //     }
    // }

    // std::cout << std::endl;
    // std::cout << "Output Layer" << std::endl;
    // for (int i = 0; i < numOutputs; i++) {
    //     outputLayer[i]->print();
    // }

    // visualize the neural network
    for (int i = 0; i < numInputs; i++) {
        std::cout << "Input Neuron " << i << '\t';
        std::cout << "Hidden Neuron 0" << std::endl;
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            std::cout << "\t\t" << weights[i][j] << std::endl;
        }
    }
    std::cout << "\t\t\tOutput Neuron: \t[" << sigmoid(outputLayer[0]->getInput()) << "]" << std::endl;
}

float ANN::feedforward(Mushroom* m, bool training) {
    // Feedforward the neural network
    // Calculate n1 for each node in the hidden layer
    // Calculate activation function for each node in the hidden layer
    // Calculate n2 for each node in the output layer
    // Calculate activation function for each node in the output layer
    // std::cout << training << std::endl;

    // Set the input layer
    for (int i = 0; i < numInputs; i++) {
        inputLayer[i]->setInput(m->getAttribute(i));
        // std::cout << m->getAttribute(i) << std::endl;
    }

    float dropoutRate = 0.5;

    // calculate the activation function for each node in the hidden layer
    for (int n = 0; n < hiddenLayers.size(); n++) {
        for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
            // dropout
            float dropoutValue = (float)rand() / RAND_MAX;
            if (dropoutValue < dropoutRate && training) {
                hiddenLayers[n][i]->setInput(0.0f);
            } else {
                // n1j = v0j + sum(vij * xi)
                float n1 = hiddenBias[i];
                for (int k = 0; k < numInputs; k++) {
                    n1 += weights[k][i] * inputLayer[k]->getInput();
                }
                hiddenLayers[n][i]->setInput(n1);
            }
        }
    }

    // calculate the activation function for each node in the output layer
    float n2 = 0.0f;
    for (int i = 0; i < numOutputs; i++) {
        n2 = outputBias;
        // n2m = w0m + sum(wjm * f(n1j))
        for (int k = 0; k < hiddenLayers.size(); k++) {
            for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
                n2 += outputWeights[j][i] * sigmoid(hiddenLayers.back()[j]->getInput());
            }
        }
        outputLayer[i]->setInput(n2);
    }

    // std::cout << "Output: " << sigmoid(n2) << std::endl;

    return sigmoid(n2);
}

// ANN helper functions
void ANN::trainHelper(Mushroom* m, std::ofstream& file) {
    feedforward(m);
    // std::cout << "Class: " << m->getMushroomClass() << std::endl;
    float targetValue = (m->getMushroomClass()) ? 1.0f : 0.0f;
     // deltak = (tk - f(n2k)) * f'(n2k)
    float outputError = (targetValue - sigmoid(outputLayer[0]->getInput())) * sigmoidDerivative(outputLayer[0]->getInput());

    // write error to file
    file << outputError << std::endl;

    std::vector<float> hiddenLayerErrors(numNeuronsPerHiddenLayer);

    for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
        // deltai = deltani * f'(ni)
        hiddenLayerErrors[j] = outputError * outputWeights[j][0] * sigmoidDerivative(hiddenLayers[0][j]->getInput());
    }

    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
         // deltawik = alpha * deltak * f(n1i)
        outputWeights[i][0] += learningRate * outputError * sigmoid(hiddenLayers[0][i]->getInput());
    }
    // deltaw0k = alpha * deltak
    outputBias += learningRate * outputError;

    for (int i = 0; i < numInputs; i++) {
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
             // delta vli = alpha * deltali * xi
             // wik(new) = wik(old) + deltawik
            weights[i][j] += learningRate * hiddenLayerErrors[j] * sigmoid(inputLayer[i]->getInput()) - learningRate * 0.00001 * weights[i][j];
        }
    }
    for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
        // vij(new) = vij(old) + deltavij
        hiddenBias[j] += learningRate * hiddenLayerErrors[j];
    }
}

float ANN::sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x));
}

float ANN::sigmoidDerivative(float x) {
    return sigmoid(x) * (1.0f - sigmoid(x));
}

float ANN::getRandomFloat() {
    // return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5;
}

int ANN::getIndexOfMushroom(Mushroom* m) {
    for (int i = 0; i < trainData.size(); i++) {
        if (trainData[i] == m) {
            return i;
        }
    }
    return -1;
}

float ANN::calculateLoss() {
    float totalLoss = 0.0f;
    for (Mushroom* m : trainData) {
        float outputValue = feedforward(m);
        float targetValue = (m->getMushroomClass()) ? 1.0f : 0.0f;
        totalLoss += -targetValue * log(outputValue) - (1 - targetValue) * log(1 - outputValue);
    }
    return (float)totalLoss / trainData.size();
}

// float ANN::getRandomAlt(int numInputs) {
//     float range = sqrt(6.0 / numInputs);
//     return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (2 * range)) - range;
// }

void ANN::stats(const std::vector<bool>& predicted, const std::vector<bool>& actual) {
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
    float precision = (float)(truePositive) / (truePositive + falsePositive);

    // Recall = True Positives / (True Positives + False Negatives)
    float recall = (float)(truePositive) / (truePositive + falseNegative);

    // Accuracy = (True Positives + True Negatives) / Total
    float accuracy = (float)(truePositive + trueNegative) / predicted.size();

    // F1 Score = 2 * (Precision * Recall) / (Precision + Recall)
    float f1Score = 2.0f * (precision * recall) / (precision + recall);

    std::cout << "Precision: " << precision << std::endl;
    std::cout << "Recall: " << recall << std::endl;
    std::cout << "Accuracy: " << accuracy << std::endl;
    std::cout << "F1 Score: " << f1Score << std::endl;
}

void ANN::outputsToCSV() {
    std::ofstream file("outputs.csv");
    file << "Output,Actual,Expected" << std::endl;

    for (int i = 0; i < testData.size(); i++) {
        float outputValue = feedforward(testData[i], false);
        bool predicted = classify(testData[i]);
        bool expected = testData[i]->getMushroomClass();
        file << outputValue << "," << predicted << "," << expected << std::endl;
    }
    file.close();

    std::cout << "Outputs written to outputs.csv" << std::endl;
}