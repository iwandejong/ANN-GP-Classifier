#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <iostream>

class Mushroom {
    private:
        int capDiameter;
        int capShape;
        bool gillAttachment;
        int gillColor;
        float stemHeight;
        int stemWidth;
        int stemColor;
        float season;
        int mushroomClass;
    public:
        Mushroom(int cD = 0, int cS = 0, bool gA = false, int gC = 0.0, float sH = 0.0, int sW = 0, int sC = 0, float s = 0.0, int mC = 0);
        ~Mushroom();
        void print();

        int getCapDiameter();
        int getCapShape();
        bool getGillAttachment();
        int getGillColor();
        float getStemHeight();
        int getStemWidth();
        int getStemColor();
        float getSeason();
        int getMushroomClass();

        float getAttribute(int i);
};

#endif // MUSHROOM_H