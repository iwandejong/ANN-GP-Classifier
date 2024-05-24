#include "ANN.h"

ANN::ANN(int stoppingCriteria, float learningRate) {
    // Initialize the neural network
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
            weight.push_back(getRandomAlt(numInputs));
        }
        weights.push_back(weight);
    }

    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        std::vector<float> outputWeight;
        for (int j = 0; j < numOutputs; j++) {
            outputWeight.push_back(getRandomAlt(numNeuronsPerHiddenLayer));
        }
        outputWeights.push_back(outputWeight);
    }

    // visualize();

    inputBias = getRandomAlt(numInputs);
    hiddenBias = getRandomAlt(numNeuronsPerHiddenLayer);
    outputBias = getRandomAlt(numNeuronsPerHiddenLayer);

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
    // Train the neural network
    int i = 0;

    // visualize();

    // initialize weights and biases
    inputBias = getRandomFloat();

    while (i < stoppingCriteria) {
        // select a random mushroom from the training data
        int randomIndex = rand() % trainData.size();
        trainHelper(trainData[randomIndex]);
        
        if (i % 100 == 0) { // Print loss every 100 iterations
            float loss = calculateLoss();
            std::cout << "Iteration " << i << ", Loss: " << loss << std::endl;
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

    // Classify each mushroom in the test data
    std::vector<bool> results;
    for (int i = 0; i < testData.size(); i++) {
        results.push_back(classify(testData[i]));
    }

    int correct = 0;
    int total = 0;
    for (int i = 0; i < testData.size(); i++) {
        if (results[i] == testData[i]->getMushroomClass()) {
            correct++;
        }
        total++;
    }

    // Print the accuracy of the neural network
    std::cout << "Accuracy: " << (float)correct / total * 100 << "%" << std::endl;
}

bool ANN::classify(Mushroom* m) {
    // Classify the mushroom based on the output
    return feedforward(m) > 0.5 ? true : false;
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

float ANN::feedforward(Mushroom* m) {
    // Feedforward the neural network
    // Calculate n1 for each node in the hidden layer
    // Calculate activation function for each node in the hidden layer
    // Calculate n2 for each node in the output layer
    // Calculate activation function for each node in the output layer

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
            if (dropoutValue < dropoutRate) {
                hiddenLayers[n][i]->setInput(0.0f);
            } else {
                // n1j = v0j + sum(vij * xi)
                float n1 = hiddenBias;
                for (int k = 0; k < numInputs; k++) {
                    n1 += weights[k][i] * sigmoid(inputLayer[k]->getInput());
                }
                hiddenLayers[n][i]->setInput(n1);
            }
        }
    }

    // calculate the activation function for each node in the output layer
    float n2 = outputBias;
    for (int i = 0; i < numOutputs; i++) {
        // n2m = w0m + sum(wjm * f(n1j))
        for (int k = 0; k < hiddenLayers.size(); k++) {
            for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
                n2 += outputWeights[j][i] * sigmoid(hiddenLayers[k][j]->getInput());
            }
        }
        outputLayer[i]->setInput(n2);
    }

    // std::cout << "Output: " << sigmoid(n2) << std::endl;

    return sigmoid(n2);
}

// ANN helper functions
void ANN::trainHelper(Mushroom* m) {
    feedforward(m);

    float targetValue = (m->getMushroomClass()) ? 1.0f : 0.0f;
    float outputError = (targetValue - sigmoid(outputLayer[0]->getInput())) * sigmoidDerivative(outputLayer[0]->getInput());

    std::vector<float> hiddenLayerErrors(numNeuronsPerHiddenLayer);

    for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
        hiddenLayerErrors[j] = outputError * outputWeights[j][0] * sigmoidDerivative(hiddenLayers[0][j]->getInput());
    }

    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        outputWeights[i][0] += learningRate * outputError * sigmoid(hiddenLayers[0][i]->getInput());
    }
    outputBias += learningRate * outputError;

    for (int i = 0; i < numInputs; i++) {
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            weights[i][j] += learningRate * hiddenLayerErrors[j] * sigmoid(inputLayer[i]->getInput()) - learningRate * 0.00001 * weights[i][j];
        }
    }
    hiddenBias += learningRate * std::accumulate(hiddenLayerErrors.begin(), hiddenLayerErrors.end(), 0.0f);
}

float ANN::sigmoid(float x) {
    // Sigmoid activation function
    return 1 / (1 + exp(-x));
}

float ANN::sigmoidDerivative(float x) {
    // Derivative of the sigmoid activation function
    return sigmoid(x) * (1 - sigmoid(x));
}

float ANN::getRandomFloat() {
    // Generate a random float between -0.5 and 0.5
    // return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5;
}

int ANN::getIndexOfMushroom(Mushroom* m) {
    // Get the index of a mushroom in the training data
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
    return totalLoss / trainData.size();
}

float ANN::getRandomAlt(int numInputs) {
    float range = sqrt(6.0 / numInputs);
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (2 * range)) - range;
}