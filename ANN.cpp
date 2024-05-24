#include "ANN.h"

ANN::ANN(int stoppingCriteria) {
    // Initialize the neural network
    trainData = std::vector<Mushroom*>();
    testData = std::vector<Mushroom*>();

    for (int i = 0; i < numInputs; i++) {
        inputLayer.push_back(new Node(0.0, 0.0));
    }

    for (int i = 0; i < numHiddenLayers; i++) {
        std::vector<Node*> hiddenLayer;
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            hiddenLayer.push_back(new Node(0.0, 0.0));
        }
        hiddenLayers.push_back(hiddenLayer);
    }

    for (int i = 0; i < numOutputs; i++) {
        outputLayer.push_back(new Node(0.0, 0.0));
    }

    this->stoppingCriteria = stoppingCriteria;
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
    while (i < stoppingCriteria) {
        feedforward(trainData[i]);
        // backpropagation();
        // updateWeights();
        i++;
    }

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
    // Get the output of the neural network
    float output = outputLayer[0]->activationFunction(outputLayer[0]->getBias());

    std::cout << output << std::endl;

    // Classify the mushroom based on the output
    return output > 0.5 ? true : false;
}

void ANN::save() {
    // Save the neural network
}

void ANN::load() {
    // Load the neural network
}

void ANN::visualize() {
    // Visualize the neural network using Nodes
    std::cout << "Input Layer" << std::endl;
    for (int i = 0; i < numInputs; i++) {
        inputLayer[i]->print();
    }

    std::cout << std::endl;
    std::cout << "Hidden Layer" << std::endl;
    for (int i = 0; i < numHiddenLayers; i++) {
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            hiddenLayers[i][j]->print();
        }
    }

    std::cout << std::endl;
    std::cout << "Output Layer" << std::endl;
    for (int i = 0; i < numOutputs; i++) {
        outputLayer[i]->print();
    }
}

// ANN helper functions
void ANN::feedforward(Mushroom* m) {
    // Feedforward the neural network
    // Calculate n1 for each node in the hidden layer
    // Calculate activation function for each node in the hidden layer
    // Calculate n2 for each node in the output layer
    // Calculate activation function for each node in the output layer

    // // set input layer
    for (int i = 0; i < numInputs; i++) {
        inputLayer[i]->setInput(trainData[getIndexOfMushroom(m)]->getAttribute(i));
        inputLayer[i]->setWeight(1.0);
        inputLayer[i]->setBias(0.0);
    }

    // For each node in the hidden layer
    // calculate n1
    // For each node in the hidden layer
    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        float n1 = 0.0f;
        for (int j = 0; j < numInputs; j++) {
            n1 += inputLayer[j]->getWeight() * inputLayer[j]->activationFunction(trainData[getIndexOfMushroom(m)]->getAttribute(j));
        }
        hiddenLayers[0][i]->setWeight(n1 * getRandomFloat());  // Function to generate random value

        // Option 1: Random Bias Initialization
        hiddenLayers[0][i]->setBias(getRandomFloat());  // Function to generate random value

        // Option 2: Separate Bias Term (if implemented)
        // hiddenLayers[0][i]->setBias(hiddenLayers[0][i]->getBiasWeight() * someValue);  // How the bias weight is used
    }

    // For each node in the hidden layer
    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        hiddenLayers[0][i]->setBias(sigmoid(hiddenLayers[0][i]->getWeight() + hiddenLayers[0][i]->getBias()));
    }

    // For each node in the output layer
    // calculate n2
    for (int i = 0; i < numOutputs; i++) {
        float n2 = 0.0f;
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            n2 += hiddenLayers[0][j]->getWeight() * hiddenLayers[0][j]->getBias();
        }
        outputLayer[i]->setWeight(n2 * getRandomFloat());  // Function to generate random value

        // Option 1: Random Bias Initialization
        outputLayer[i]->setBias(getRandomFloat());  // Function to generate random value

        // Option 2: Separate Bias Term (if implemented)
        outputLayer[i]->setBias(outputLayer[i]->getBias() * getRandomFloat());  // How the bias weight is used
    }

    // For each node in the output layer
    // calculate activation function
    for (int i = 0; i < numOutputs; i++) {
        outputLayer[i]->setBias(sigmoid(outputLayer[i]->getWeight() + outputLayer[i]->getBias()));
    }

}

void ANN::backpropagation() {
    // Backpropagate the neural network
    // Calculate the error for each node in the output layer
    // Calculate the weight correction term for each node in the output layer
    // Calculate the bias correction term for each node in the output layer
    // Calculate the sum of delta inputs for each node in the hidden layer
    // Calculate the error information term for each node in the hidden layer
    // Calculate the weight error term for each node in the hidden layer
    // Calculate the bias error term for each node in the hidden layer

    float error = 0;
    float weightCorrectionTerm = 0;
    float biasCorrectionTerm = 0;
    float sumDeltaInputs = 0;
    float errorInformationTerm = 0;
    float weightErrorTerm = 0;
    float biasErrorTerm = 0;

    // For each node in the output layer
    for (int i = 0; i < numOutputs; i++) {
        error = trainData[0]->getMushroomClass() - outputLayer[i]->getBias();
        weightCorrectionTerm = error * outputLayer[i]->getBias() * (1 - outputLayer[i]->getBias());
        biasCorrectionTerm = error * outputLayer[i]->getBias() * (1 - outputLayer[i]->getBias());
    }

    // For each node in the hidden layer
    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        sumDeltaInputs = 0;
        for (int j = 0; j < numOutputs; j++) {
            sumDeltaInputs += outputLayer[j]->getWeight() * outputLayer[j]->getBias();
        }
        errorInformationTerm = hiddenLayers[0][i]->getBias() * (1 - hiddenLayers[0][i]->getBias()) * sumDeltaInputs;
        weightErrorTerm = errorInformationTerm * hiddenLayers[0][i]->getBias();
        biasErrorTerm = errorInformationTerm;
    }

    // Update the weights of the neural network using the weight error term
    // Update the biases of the neural network using the bias error term

    // For each node in the output layer
    for (int i = 0; i < numOutputs; i++) {
        float newWeight = outputLayer[i]->getWeight() + 0.1 * weightErrorTerm;
        outputLayer[i]->setWeight(newWeight);
        float newBias = outputLayer[i]->getBias() + 0.1 * biasErrorTerm;
        outputLayer[i]->setBias(newBias);
    }

    // For each node in the hidden layer
    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        float newWeight = hiddenLayers[0][i]->getWeight() + 0.1 * weightErrorTerm;
        hiddenLayers[0][i]->setWeight(newWeight);
        float newBias = hiddenLayers[0][i]->getBias() + 0.1 * biasErrorTerm;
        hiddenLayers[0][i]->setBias(newBias);
    }

}

void ANN::updateWeights() {
    // Update the weights of the neural network after backpropagation

    // For each node in the output layer
    for (int i = 0; i < numOutputs; i++) {
        // Update the weight of the node
        outputLayer[i]->setWeight(outputLayer[i]->getWeight() + 0.1);
        // Update the bias of the node
        outputLayer[i]->setBias(outputLayer[i]->getBias() + 0.1);
    }

    // For each node in the hidden layer
    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        // Update the weight of the node
        hiddenLayers[0][i]->setWeight(hiddenLayers[0][i]->getWeight() + 0.1);
        // Update the bias of the node
        hiddenLayers[0][i]->setBias(hiddenLayers[0][i]->getBias() + 0.1);
    }
}

float ANN::sigmoid(float x) {
    // Sigmoid activation function
    return 1 / (1 + exp(-x));
}

float ANN::getRandomFloat() {
    // Generate a random float between 0 and 1
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
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