//
// Created by USER on 2018/3/27.
//
#include "SpurGear.h"

/**
 * /To calculate the coordinates of the involute profile
 */
void SpurGear::generateInvoluteProfile() {
    double tp = M_PI*pitchDiameter/(2*teethNumber);
    int n = 10;

    for (int i=0; i<n; i++) {
        double r = addendumDiameter/2 - (addendumDiameter - baseCircleDiameter)*i/(n - 1);
        double phi = acos(baseCircleDiameter/(2*r));

        //tooth tickness at any angle phi
        //involute equation - refer to Shigley's book
        double toothThickness = 2*r*(tp/pitchDiameter + (tan(phi) - phi) - (tan(phi) - phi));
        double theta = toothThickness/2*r;
        pairList.push_back(Pair(r*sin(theta), r*cos(theta)));
    }
}

//void calculateAddendumCircle();
//void caculateCurveBetweenBaseAndDedendumCircle();
//void caculateDedendumCircle();
//void caculateFillet();
//void getWholeTeethReflection();
//void generateWholeGear();