#include "GP_Node.h"

GP_Node::GP_Node(float i) {
    input = i;
    left = nullptr;
    right = nullptr;
    fitness = (float) std::rand() / RAND_MAX;
}

GP_Node::~GP_Node() {}

void GP_Node::print(int level) {
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }

    if (isLeaf()) {
        std::cout << "Fitness: " << std::fixed << std::setprecision(2) << fitness << std::endl;
    } else {
        std::cout << "Operator: " << operation;
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
    return input;
}

void GP_Node::setInput(float i) {
    input = i;
}

float GP_Node::activationFunction(float x) {
    return 1 / (1 + exp(-x));
}

// GP-related functions
GP_Node* GP_Node::getLeft() {
    return left;
}

GP_Node* GP_Node::getRight() {
    return right;
}

void GP_Node::setLeft(GP_Node* l) {
    left = l;
}

void GP_Node::setRight(GP_Node* r) {
    right = r;
}

void GP_Node::setFitness(float f) {
    fitness = f;
}

float GP_Node::getFitness() {
    return fitness;
}

void GP_Node::generateTree(int depth, int numFeatures, const std::vector<Mushroom*>& trainData) {
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
    return left == nullptr && right == nullptr;
}

GP_Node* GP_Node::copy(GP_Node* n) {
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
    if (isLeaf()) {
        return 1;
    } else {
        return 1 + std::max(left->getDepth(), right->getDepth());
    }
}

GP_Node* GP_Node::getRandomGP_Node() {
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
    operation = op;
}

int GP_Node::getOperation() {
    return operation;
}

float GP_Node::classifyBase(Mushroom* m) {
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
