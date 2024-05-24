#include "ANN.h"

ANN::ANN(int stoppingCriteria, float learningRate) {
    // Initialize the neural network
    trainData = std::vector<Mushroom*>();
    testData = std::vector<Mushroom*>();

    for (int i = 0; i < numInputs; i++) {
        inputLayer.push_back(new Node(0.0, 0.0));
    }

    for (int i = 0; i < numHiddenLayers; i++) {
        std::vector<Node*> hiddenLayer;
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            hiddenLayer.push_back(new Node(getRandomFloat(), 0.0));
        }
        hiddenLayers.push_back(hiddenLayer);
    }

    for (int i = 0; i < numOutputs; i++) {
        outputLayer.push_back(new Node(getRandomFloat(), 0.0));
    }

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

    // initialize weights and biases
    float biasRandom = getRandomFloat();
    for (int i = 0; i < numInputs; i++) {;
        inputLayer[i]->setBias(biasRandom);
    }

    while (i < stoppingCriteria) {
        trainHelper(trainData[i % trainData.size()]);
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
    float output = 0;
    for (int i = 0; i < numInputs; i++) {
        inputLayer[i]->setInput(m->getAttribute(i));
    }

    for (int k = 0; k < numHiddenLayers; k++) {
        for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
            float n1 = hiddenLayers[k][i]->getBias();
            for (int j = 0; j < numInputs; j++) {
                n1 += hiddenLayers[k][i]->getWeight() * inputLayer[j]->getInput();
            }
            hiddenLayers[k][i]->setInput(sigmoid(n1));
        }
    }

    for (int i = 0; i < numOutputs; i++) {
        float n2 = outputLayer[i]->getBias();
        for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
            n2 += outputLayer[i]->getWeight() * sigmoid(hiddenLayers[0][j]->getInput());
        }
        output = sigmoid(n2);
    }

    std::cout << output << std::endl;

    // Classify the mushroom based on the output
    return output > 0.5 ? true : false;
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
void ANN::trainHelper(Mushroom* m) {
    // Feedforward the neural network
    // Calculate n1 for each node in the hidden layer
    // Calculate activation function for each node in the hidden layer
    // Calculate n2 for each node in the output layer
    // Calculate activation function for each node in the output layer

    // Set the input layer
    for (int i = 0; i < numInputs; i++) {
        inputLayer[i]->setInput(m->getAttribute(i));
    }

    // calculate the activation function for each node in the hidden layer
    for (int n = 0; n < hiddenLayers.size(); n++) {
        for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
            // n1j = v0j + sum(vij * xi)
            float n1 = hiddenLayers[n][i]->getBias();
            for (int k = 0; k < hiddenLayers.size(); k++) {
                for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
                    n1 += hiddenLayers[k][i]->getWeight() * inputLayer[i]->getInput();
                }
            }
            hiddenLayers[n][i]->setInput(n1);
        }
    }

    // calculate the activation function for each node in the output layer
    for (int i = 0; i < numOutputs; i++) {
        // n2m = w0m + sum(wjm * f(n1j))
        float n2 = outputLayer[i]->getBias();
        for (int k = 0; k < hiddenLayers.size(); k++) {
            for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
                n2 += hiddenLayers[k][j]->getWeight() * sigmoid(hiddenLayers[k][j]->getInput());
            }
        }
        outputLayer[i]->setInput(n2);
    }

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
    float sumDeltaInput = 0;
    float errorInformationTerm = 0;
    float weightErrorTerm = 0;
    float biasErrorTerm = 0;

    // std::vector <float> errors = std::vector <float>();
    // std::vector <float> weightCorrectionTerms = std::vector <float>();
    // std::vector <float> biasCorrectionTerms = std::vector <float>();
    // std::vector <float> sumDeltaInputs = std::vector <float>();
    // std::vector <float> errorInformationTerms = std::vector <float>();
    // std::vector <float> weightErrorTerms = std::vector <float>();
    // std::vector <float> biasErrorTerms = std::vector <float>();

    for (int i = 0; i < numOutputs; i++) {
        // deltak = (tk - f(n2k)) * f'(n2k)
        error = (m->getMushroomClass() - sigmoid(outputLayer[i]->getInput())) * sigmoidDerivative(outputLayer[i]->getInput());

        // deltawik = alpha * deltak * f(n1i)
        for (int n = 0; n < hiddenLayers.size(); n++) {
            for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
                weightCorrectionTerm = learningRate * error * sigmoid(hiddenLayers[n][j]->getInput());
            }
        }

        // deltaw0k = alpha * deltak
        biasCorrectionTerm = learningRate * error;

        // errors.push_back(error);
        // weightCorrectionTerms.push_back(weightCorrectionTerm);
        // biasCorrectionTerms.push_back(biasCorrectionTerm);
        outputLayer[i]->setWeight(outputLayer[i]->getWeight() + weightCorrectionTerm);
        outputLayer[i]->setBias(outputLayer[i]->getBias() + biasCorrectionTerm);
    }

    // Sum of the delta inputs from the output layer for each node in the hidden layer:
    // deltai = sum(deltak * wki)
    for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
        sumDeltaInput = 0;
        for (int j = 0; j < numOutputs; j++) {
            sumDeltaInput += error * outputLayer[j]->getWeight();
        }
    }

    // std::cout << "Hidden layer size: " << hiddenLayers.size() << std::endl;
    for (int i = 0; i < hiddenLayers.size(); i++) {
        for (int j = 0; j < hiddenLayers[0].size(); j++) {
            
            // deltai = deltani * f'(ni)
            errorInformationTerm = sumDeltaInput * sigmoidDerivative(hiddenLayers[i][j]->getInput());

            // delta vli = alpha * deltali * xi
            for (int k = 0; k < numInputs; k++) {
                weightErrorTerm += learningRate * errorInformationTerm * inputLayer[k]->getInput();
            }
            
            biasErrorTerm = learningRate * errorInformationTerm;

            // sumDeltaInputs.push_back(sumDeltaInput);
            // errorInformationTerms.push_back(errorInformationTerm);
            // weightErrorTerms.push_back(weightErrorTerm);
            // biasErrorTerms.push_back(biasErrorTerm);

            // wik(new) = wik(old) + deltawik
            hiddenLayers[i][j]->setWeight(hiddenLayers[i][j]->getWeight() + weightErrorTerm);
            hiddenLayers[i][j]->setBias(hiddenLayers[i][j]->getBias() + biasErrorTerm);
        }
    }

    // Update the weights and biases of the output layer
    // wik(new) = wik(old) + deltawik
    // for (int i = 0; i < numOutputs; i++) {
    //     // outputLayer[i]->setWeight(outputLayer[i]->getWeight() + weightCorrectionTerms[i]);
    //     // outputLayer[i]->setBias(outputLayer[i]->getBias() + biasCorrectionTerms[i]);
    // }

    // // Update the weights and biases of the hidden layer
    // // vij(new) = vij(old) + deltavij
    // for (int i = 0; i < hiddenLayers.size(); i++) {
    //     for (int j = 0; j < hiddenLayers[0].size(); j++) {
    //     }
    // }
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