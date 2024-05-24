#include "ANN.h"

#include <fstream>
#include <iostream>
#include <string>

void csvToObject(std::string inputFile, ANN* ann, bool isTrain = true) {
    std::ifstream file(inputFile);
    std::string line;
    std::string lineArray[9];
    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        for (int i = 0; i < 9; i++) {
            lineArray[i] = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
        }

        int cD = std::stoi(lineArray[0]);
        int cS = std::stoi(lineArray[1]);
        bool gA = lineArray[2] == "1" ? true : false;
        int gC = std::stoi(lineArray[3]);
        float sH = std::stof(lineArray[4]);
        int sW = std::stoi(lineArray[5]);
        int sC = std::stoi(lineArray[6]);
        float s = std::stof(lineArray[7]);
        int mC = std::stoi(lineArray[8]);
        if (isTrain) {
            ann->addMushroomToTrain(new Mushroom(cD, cS, gA, gC, sH, sW, sC, s, mC));
        } else {
            ann->addMushroomToTest(new Mushroom(cD, cS, gA, gC, sH, sW, sC, s, mC));
        }
    }
}

int main() {

    ANN* ann = new ANN(2);

    csvToObject("mushroom_data/mushroom_train.csv", ann, true);
    csvToObject("mushroom_data/mushroom_test.csv", ann, false);

    ann->train();

    ann->visualize();

    return 0;
}