//
// Created by USER on 2018/3/26.
//

#ifndef INVOLUTESPURGEAR_SPURGEAR_H
#define INVOLUTESPURGEAR_SPURGEAR_H

#include "utils/AngleUtils.h"
#include "utils/Pair.h"

using namespace std;
class SpurGear {
private:
    int teethNumber;
    double module;
    AngleUtils pressAngle = AngleUtils();
    const double filletRadius = 0.05;

    double pd;
    double pitchDiameter;
    double baseCircleDiameter;
    double addendumDiameter;
    double dedendumDiameter;

    vector<Pair<double, double>> pairList = vector<Pair<double, double>>();

public:
   SpurGear(int teethNumber, double module, double press) {
       this->teethNumber = teethNumber;
       this->module = module;
       this->pressAngle.setDegree(press);

       this->pd = 25.4/module;
       this->pitchDiameter = teethNumber/pd;
       this->baseCircleDiameter = pitchDiameter*pressAngle.cos();
       this->addendumDiameter = pitchDiameter + 2/pd;
       this->dedendumDiameter = pitchDiameter - 2*1.25/pd;
   }

    void generateInvoluteProfile();
    void calculateAddendumCircle();
    void caculateCurveBetweenBaseAndDedendumCircle();
    void caculateDedendumCircle();
    void caculateFillet();
    void getWholeTeethReflection();
    void generateWholeGear();
};
#endif //INVOLUTESPURGEAR_SPURGEAR_H
