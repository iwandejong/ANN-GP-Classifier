// Iwan de Jong, u22498037

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <iostream>

class Mushroom {
    private:
        float capDiameter;
        float capShape;
        float gillAttachment;
        float gillColor;
        float stemHeight;
        float stemWidth;
        float stemColor;
        float season;
        bool mushroomClass;
    public:
        Mushroom(float cD = 0.0, float cS = 0.0, float gA = 0.0, float gC = 0.0, float sH = 0.0, float sW = 0.0, float sC = 0.0, float s = 0.0, bool mC = false);
        ~Mushroom();
        void print();

        float getCapDiameter();
        float getCapShape();
        float getGillAttachment();
        float getGillColor();
        float getStemHeight();
        float getStemWidth();
        float getStemColor();
        float getSeason();
        bool getMushroomClass();

        float getAttribute(int i);
};

#endif // MUSHROOM_H