//
// Created by USER on 2018/3/27.
//
#include <algorithm>
#include "SpurGear.h"
#include "utils/Matrix.h"

/**
 * /To calculate the coordinates of the involute profile
 */
void SpurGear::generateInvoluteProfile() {
    double tp = M_PI*pitchDiameter/(2*teethNumber);
    int n = 10;

    for (int i=0; i<n; i++) {
        double r = addendumDiameter/2 - (addendumDiameter - baseCircleDiameter)*i/(n - 1);
        double phi = acos(baseCircleDiameter/(2*r));

        //tooth thickness at any angle phi
        //involute equation - refer to Shigley's book
        double toothThickness = 2*r*(tp/pitchDiameter + (pressAngle.tan() - pressAngle.getRadianValue()) - (tan(phi) - phi));
        double theta = toothThickness/(2*r);
        involute.push_back(Pair<double, double>(r*sin(theta), r*cos(theta)));
        thetaList.push_back(theta);
    }
}

/**
 * To calculate the addendum circle
 */
void SpurGear::calculateAddendumCircle() {
    int n = 5;
    double theta = thetaList[0];
    for (int i=0; i<n; i++) {
        double thetaO = theta*i/(n - 1);
        addendumCircle.push_back(Pair<double, double>((addendumDiameter/2)*cos(thetaO), (addendumDiameter/2)*sin(thetaO)));
    }
}

/**
 * To calculate the non-involute portion of the curve- between the base circle and
 *  dedendum circle - in this case, a straight line parallel to the y axis and connects
 * to the fillet arc
 */
void SpurGear::caculateCurveBetweenBaseAndDedendumCircle() {
    int n = 3;
    theta0 = asin((involute[involute.size() - 1].x() + FILLET_RADIUS)/(dedendumDiameter/2));
    for (int i=0; i<n; i++) {
        //to find the angle between the central line (y-axis) and the line from the center
        //to the last point of the involute curve.
        Pair<double, double> pair = involute[involute.size() - 1];
        curveBetweenBaseAndDedendumCircle.push_back(
                Pair<double, double>(pair.x(),
                     pair.y() - (pair.y() - FILLET_RADIUS - (dedendumDiameter/2)*cos(theta0))*i/(n - 1)
                )
        );
    }
}

/**
 * To calculate the dedendum circle
 */
void SpurGear::caculateDedendumCircle() {
    int n = 5;
    for (int i=0; i<n; i++) {
        //(pi/teethNumber-theta0) angle subtended for dedendum arc
        double subtendedAngleForDedendumArc = M_PI/teethNumber - theta0;
        double thetaR = theta0 + subtendedAngleForDedendumArc*i/(n - 1);
        dedendumCircle.push_back(Pair<double, double>(dedendumDiameter*sin(thetaR)/2, dedendumDiameter*cos(thetaR)/2));
    }
}

/**
 * To calculate fillet
 * to draw the quarter of a circle from the last point of the non-involute part to
 * the tangent of the dedendum circle.
 */
void SpurGear::caculateFillet() {
    int n = 5;
    for (int i=0; i<n; i++) {
        fillet.push_back(Pair<double, double>(
                dedendumCircle[0].x() - FILLET_RADIUS*cos(i*M_PI/(2*(n - 1))),
                dedendumCircle[0].y() + FILLET_RADIUS*(1 - sin(i)*M_PI/2*(n - 1))
        ));
    }
}

/**
 * To reflect the involute curve about y axis to get the whole tooth
 */
void SpurGear::getWholeTeethReflection() {
    vector<vector<Pair<double, double>>> pairVectorList = vector<vector<Pair<double, double>>>();
    pairVectorList.push_back(involute);
    pairVectorList.push_back(addendumCircle);
    pairVectorList.push_back(curveBetweenBaseAndDedendumCircle);
    pairVectorList.push_back(dedendumCircle);
    pairVectorList.push_back(fillet);

    for (vector<Pair<double, double>> v : pairVectorList) {
        gear.insert(gear.end(), v.begin(), v.end());
    }

    vector<Pair<double, double>> reflect = vector<Pair<double, double>>();
    for (Pair<double, double> p : gear) {
        reflect.push_back(Pair<double, double>(-1*p.x(), p.y()));
    }
    reverse(reflect.begin(), reflect.end());
    gear.insert(gear.end(), reflect.begin(), reflect.end());

    pairVectorList.clear();
    reflect.clear();
}

/**
 * To rotate and append the tooth to generate the gear
 */
void SpurGear::generateWholeGear() {
    int size = gear.size();

    for (int i=0; i<teethNumber; i++) {
        double theta = 2*M_PI*i/teethNumber;
        double data[4] = {cos(theta), sin(theta), -1*sin(theta), cos(theta)};
        vector<Pair<double, double>> pairList = computeMatrix(data, gear, 0, size);
        gear.insert(gear.end(), pairList.begin(), pairList.end());
    }
}

vector<Pair<double, double>> SpurGear::computeMatrix(double *matrix, vector<Pair<double, double>> pairList, int begin, int end) {
    vector<Pair<double, double>> result = vector<Pair<double, double>>();
    for (int i=begin; i<end; i++) {
        result[i] = Pair<double, double>(matrix[0]*pairList[i].x() + matrix[1]*pairList[i].y(),
                         matrix[2]*pairList[i].x() + matrix[3]*pairList[i].y());
    }
    return result;
}

vector<Pair<double, double>> SpurGear::getGearCordinates() {
    generateInvoluteProfile();
    calculateAddendumCircle();
    caculateCurveBetweenBaseAndDedendumCircle();
    caculateDedendumCircle();
    caculateFillet();
    getWholeTeethReflection();
    generateWholeGear();

    return gear;
}