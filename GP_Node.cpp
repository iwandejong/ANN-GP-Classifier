#include "GP_Node.h"

GP_Node::GP_Node(float i) {
    // Implementation of the constructor
    input = i;
    left = nullptr;
    right = nullptr;
    fitness = (float) std::rand() / RAND_MAX;
}

GP_Node::~GP_Node() {}

void GP_Node::print(int level) {
    // Indentation based on level
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }

    // Print node information
    if (isLeaf()) {
        std::cout << "Fitness: " << std::fixed << std::setprecision(2) << fitness << std::endl;
    } else {
        std::cout << "Operator: " << operation;
        // Print operator symbol based on your implementation (e.g., "+", "-")
        std::cout << std::endl;
        if (left != nullptr) {
            left->print(level + 1);
        }
        if (right != nullptr) {
            right->print(level + 1);
        }
    }
}


float GP_Node::getInput() {
    // Implementation of the getInput function
    return input;
}

void GP_Node::setInput(float i) {
    // Implementation of the setInput function
    input = i;
}

float GP_Node::activationFunction(float x) {
    // Implementation of the activationFunction function
    // Sigmoid activation function
    return 1 / (1 + exp(-x));
}

// GP-related functions
GP_Node* GP_Node::getLeft() {
    // Implementation of the getLeft function
    return left;
}

GP_Node* GP_Node::getRight() {
    // Implementation of the getRight function
    return right;
}

void GP_Node::setLeft(GP_Node* l) {
    // Implementation of the setLeft function
    left = l;
}

void GP_Node::setRight(GP_Node* r) {
    // Implementation of the setRight function
    right = r;
}

void GP_Node::setFitness(float f) {
    // Implementation of the setFitness function
    fitness = f;
}

float GP_Node::getFitness() {
    // iterate through the tree to get the fitness value
    return fitness;
}

void GP_Node::generateTree(int depth, int numFeatures, const std::vector<Mushroom*>& trainData) {
    // Implementation of the generateTree function
    if (depth == 1 || numFeatures == 1) {
        int featureIndex = std::rand() % numFeatures;
        int trainingIndex = std::rand() % trainData.size();
        fitness = trainData[trainingIndex]->getAttribute(featureIndex);
        // std::cout << "Feature: " << featureIndex << " Value: " << fitness << std::endl;
    } else {
        left = new GP_Node();
        left->generateTree(depth - 1, numFeatures - 1, trainData);
        right = new GP_Node();
        right->generateTree(depth - 1, numFeatures - 1, trainData);
        operation = std::rand() % 7;
    }
}

bool GP_Node::isLeaf() {
    // Implementation of the isLeaf function
    return left == nullptr && right == nullptr;
}

GP_Node* GP_Node::copy(GP_Node* n) {
    // Implementation of the copy function
    fitness = n->getFitness();
    if (!n->isLeaf()) {
        left = new GP_Node();
        left->copy(n->getLeft());
        right = new GP_Node();
        right->copy(n->getRight());
    }
    return this;
}

void GP_Node::crossover(GP_Node* n) {
    GP_Node* tempLeft = left;
    GP_Node* tempRight = right;

    left = n->left;
    n->left = tempLeft;
    right = n->right;
    n->right = tempRight;
}


void GP_Node::mutate() {
    // Implementation of the mutate function
    if (std::rand() % 2 == 0) {
        fitness = (float) std::rand() / RAND_MAX;
    } else {
        if (left != nullptr) {
            left->mutate();
        }
        if (right != nullptr) {
            right->mutate();
        }
    }
}

int GP_Node::getDepth() {
    // Implementation of the getDepth function
    if (isLeaf()) {
        return 1;
    } else {
        return 1 + std::max(left->getDepth(), right->getDepth());
    }
}

GP_Node* GP_Node::getRandomGP_Node() {
    // Implementation of the getRandomGP_Node function
    if (isLeaf()) {
        return this;
    } else {
        if (std::rand() % 2 == 0) {
            return left->getRandomGP_Node();
        } else {
            return right->getRandomGP_Node();
        }
    }
}

void GP_Node::setOperation(int op) {
    // Implementation of the setOperation function
    operation = op;
}

int GP_Node::getOperation() {
    // Implementation of the getOperation function
    return operation;
}

float GP_Node::classifyBase(Mushroom* m) {
    // Implementation of the classifyBase function
    return classify(m, 0);
}

float GP_Node::classify(Mushroom* m, int atAttribute) {
    if (isLeaf()) {
        return m->getAttribute(atAttribute--) * fitness;
    }
    
    float leftValue = 0.0f;
    float rightValue = 0.0f;

    if (left != nullptr) {
        leftValue = left->classify(m, atAttribute);
    }

    if (right != nullptr) {
        rightValue = right->classify(m, atAttribute);
    }

    switch (operation) {
        case 0:
            return leftValue + rightValue;
        case 1:
            return leftValue - rightValue;
        case 2:
            return leftValue * rightValue;
        case 3:
            return rightValue != 0.0f ? leftValue / rightValue : 0.0f;
        case 4:
            return pow(leftValue, rightValue);
        case 5:
            return sin(leftValue);
        case 6:
            return cos(rightValue);
        default:
            return 0.0;
    }
}
