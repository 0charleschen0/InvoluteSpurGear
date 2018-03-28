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

        //tooth thickness at any angle phi
        //involute equation - refer to Shigley's book
        double toothThickness = 2*r*(tp/pitchDiameter + (tan(phi) - phi) - (tan(phi) - phi));
        double theta = toothThickness/2*r;
        involute.push_back(Pair(r*sin(theta), r*cos(theta)));
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
        addendumCircle.push_back(Pair((addendumDiameter/2)*cos(thetaO), (addendumDiameter/2)*sin(thetaO)));
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
        Pair pair = involute[involute.size() - 1];
        pairList.push_back(
                Pair(pair.x(),
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
        pairList.push_back(Pair(dedendumDiameter*sin(thetaR)/2, dedendumDiameter*cos(thetaR)/2));
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
        fillet.push_back(Pair(
                dedendumCircle[0].x() - FILLET_RADIUS*cos(i*M_PI/(2*(n - 1))),
                dedendumCircle[0].y() + FILLET_RADIUS*(1 - sin(i)*M_PI/2*(n - 1))
        ));
    }
}

//void getWholeTeethReflection();
//void generateWholeGear();