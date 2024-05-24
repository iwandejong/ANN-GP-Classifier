#include "ANN.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

std::vector<std::vector<float>> normalizeData(const std::vector<std::vector<float>>& data) {
    std::vector<std::vector<float>> normalizedData = data;
    int numFeatures = data[0].size();
    int numSamples = data.size();

    for (int i = 0; i < numFeatures; i++) {
        float minVal = data[0][i];
        float maxVal = data[0][i];

        for (int j = 1; j < numSamples; j++) {
            if (data[j][i] < minVal) minVal = data[j][i];
            if (data[j][i] > maxVal) maxVal = data[j][i];
        }

        for (int j = 0; j < numSamples; j++) {
            normalizedData[j][i] = (data[j][i] - minVal) / (maxVal - minVal);
        }
    }

    return normalizedData;
}

void csvToObject(std::string inputFile, ANN* ann, const std::vector<float>& minVals, const std::vector<float>& maxVals, bool isTrain = true) {
    std::ifstream file(inputFile);
    std::string line;
    std::string lineArray[9];
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        // for (int i = 0; i < 9; i++) {
        //     lineArray[i] = line.substr(0, line.find(","));
        //     line = line.substr(line.find(",") + 1);
        // }

        // int cD = std::stoi(lineArray[0]);
        // int cS = std::stoi(lineArray[1]);
        // bool gA = lineArray[2] == "1" ? true : false;
        // int gC = std::stoi(lineArray[3]);
        // float sH = std::stof(lineArray[4]);
        // int sW = std::stoi(lineArray[5]);
        // int sC = std::stoi(lineArray[6]);
        // float s = std::stof(lineArray[7]);
        // int mC = std::stoi(lineArray[8]);

        std::stringstream ss(line);
        std::string token;
        std::vector<float> values;
        while (std::getline(ss, token, ',')) {
            values.push_back(std::stof(token));
        }

        // Normalize values
        for (int i = 0; i < values.size(); i++) {
            values[i] = (values[i] - minVals[i]) / (maxVals[i] - minVals[i]);
            if (isnan(values[i])) {
                values[i] = 0;
            }
        }

        float cD = values[0];
        float cS = values[1];
        float gA = values[2];
        float gC = values[3];
        float sH = values[4];
        float sW = values[5];
        float sC = values[6];
        float s = values[7];
        bool mC = values[8] == 1 ? true : false;

        // std::cout << cD << " " << cS << " " << gA << " " << gC << " " << sH << " " << sW << " " << sC << " " << s << " " << mC << std::endl;

        if (isTrain) {
            ann->addMushroomToTrain(new Mushroom(cD, cS, gA, gC, sH, sW, sC, s, mC));
        } else {
            ann->addMushroomToTest(new Mushroom(cD, cS, gA, gC, sH, sW, sC, s, mC));
        }
    }
}

void computeMinAndMax(std::string inputFile, std::vector<float>& minVals, std::vector<float>& maxVals) {
    std::ifstream file(inputFile);
    std::string line;
    std::getline(file, line); // skip header

    // Initialize min and max vectors with extreme values
    minVals.assign(9, std::numeric_limits<float>::max());
    maxVals.assign(9, std::numeric_limits<float>::lowest());

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<float> values;
        while (std::getline(ss, token, ',')) {
            values.push_back(std::stof(token));
        }

        for (int i = 0; i < values.size(); i++) {
            if (values[i] < minVals[i]) minVals[i] = values[i];
            if (values[i] > maxVals[i]) maxVals[i] = values[i];
        }
    }
}

int main() {

    ANN* ann = new ANN(1, 0.1);

    std::vector<float> minVals;
    std::vector<float> maxVals;

    computeMinAndMax("mushroom_data/mushroom_train.csv", minVals, maxVals);
    csvToObject("mushroom_data/mushroom_train.csv", ann, minVals, maxVals, true);

    computeMinAndMax("mushroom_data/mushroom_test.csv", minVals, maxVals);
    csvToObject("mushroom_data/mushroom_test.csv", ann, minVals, maxVals, false);

    ann->train();

    // ann->visualize();

    return 0;
}