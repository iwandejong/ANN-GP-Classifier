#include "Mushroom.h"

Mushroom::Mushroom(int cD, int cS, bool gA, int gC, float sH, int sW, int sC, float s, int mC) {
    capDiameter = cD;
    capShape = cS;
    gillAttachment = gA;
    gillColor = gC;
    stemHeight = sH;
    stemWidth = sW;
    stemColor = sC;
    season = s;
    mushroomClass = mC;
}

Mushroom::~Mushroom() {}

void Mushroom::print() {
    std::cout << "Cap Diameter: " << capDiameter << std::endl;
    // std::cout << "Cap Shape: " << capShape << std::endl;
    // std::cout << "Gill Attachment: " << gillAttachment << std::endl;
    // std::cout << "Gill Color: " << gillColor << std::endl;
    // std::cout << "Stem Height: " << stemHeight << std::endl;
    // std::cout << "Stem Width: " << stemWidth << std::endl;
    // std::cout << "Stem Color: " << stemColor << std::endl;
    // std::cout << "Season: " << season << std::endl;
    // std::cout << "Mushroom Class: " << mushroomClass << std::endl;
}

int Mushroom::getCapDiameter() {
    return capDiameter;
}

int Mushroom::getCapShape() {
    return capShape;
}

bool Mushroom::getGillAttachment() {
    return gillAttachment;
}

int Mushroom::getGillColor() {
    return gillColor;
}

float Mushroom::getStemHeight() {
    return stemHeight;
}

int Mushroom::getStemWidth() {
    return stemWidth;
}

int Mushroom::getStemColor() {
    return stemColor;
}

float Mushroom::getSeason() {
    return season;
}

int Mushroom::getMushroomClass() {
    return mushroomClass;
}

float Mushroom::getAttribute(int i) {
    switch (i) {
        case 0:
            return capDiameter;
        case 1:
            return capShape;
        case 2:
            return gillAttachment;
        case 3:
            return gillColor;
        case 4:
            return stemHeight;
        case 5:
            return stemWidth;
        case 6:
            return stemColor;
        case 7:
            return season;
        case 8:
            return mushroomClass;
        default:
            return 0;
    }
}