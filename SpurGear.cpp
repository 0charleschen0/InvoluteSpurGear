//
// Created by USER on 2018/3/27.
//
#include <algorithm>
#include "SpurGear.h"

/**
 * /To calculate the coordinates of the involute profile
 */
namespace spur_gear {
    //TODO: Add undercut protection
    SpurGear::SpurGear(const int t_teethNumber = 25, const double t_module = 4.0, const double t_press = 20.0,
             const double t_fillet_radius = 0.05, const double t_shift = 0.0, const double t_backlash = 0.0)
            : m_teeth_number(t_teethNumber),
              m_module(t_module),
              m_fillet_radius(t_fillet_radius),
              m_shift(t_shift),
              m_backlash(t_backlash){
        this->m_press_angle.setDegree(t_press);

        this->m_dimetral_pitch = 25.4 / m_module;
        this->m_pitch_diameter = m_teeth_number * m_module;
        this->m_base_circle_diameter = m_pitch_diameter * m_press_angle.cos();
        this->m_addendum_diameter = m_pitch_diameter + 2 * m_module* (1 + m_shift);
        this->m_dedendum_diameter = m_pitch_diameter - 2.5 * m_module;
    }

    void SpurGear::generateInvoluteProfile() {
        double tooth_space = M_PI * m_pitch_diameter / (2 * m_teeth_number);
        int n = 10;

        for (int i = 0; i < n; i++) {
            double r = m_addendum_diameter / 2 - (m_addendum_diameter - m_base_circle_diameter) * i / (2 * (n - 1));
            double phi = acos(m_base_circle_diameter / (2 * r));

            //Involute equation for a angle x (radians) : f(x) = tan(x) - x
            double theta = (tooth_space / m_pitch_diameter +  2 * m_shift * m_press_angle.getRadianValue() / m_module
                            + (m_press_angle.tan() - m_press_angle.getRadianValue()) - (tan(phi) - phi));

            m_involute.push_back(cv::Point2d(r * sin(theta),
                                         r * cos(theta)));
        }

//        cout << m_involute;
    }

/**
 * To calculate the addendum circle
 */
    void SpurGear::calculateAddendumCircle() {
        int n = 5;

        double phi = acos(m_base_circle_diameter / (m_addendum_diameter));
        double theta = (M_PI / (2 * m_teeth_number) + (m_press_angle.tan() - m_press_angle.getRadianValue()) -
                        (tan(phi) - phi));

        for (int i = 0; i < n; i++) {
            double thetaO = theta * i / (n - 1);
            m_addendum_circle.push_back(cv::Point2d((m_addendum_diameter / 2) * sin(thetaO),
                                                (m_addendum_diameter / 2) * cos(thetaO)));
        }

//        cout<<m_addendum_circle;
    }

/**
 * To calculate the non-involute portion of the curve- between the base circle and
 *  dedendum circle - in this case, a straight line parallel to the y axis and connects
 * to the fillet arc
 */
    void SpurGear::caculateCurveBetweenBaseAndDedendumCircle() {
        int n = 3;
        m_theta0 = asin((m_involute[m_involute.size() - 1].x + m_fillet_radius) / (m_dedendum_diameter / 2));
        for (int i = 0; i < n; i++) {
            //to find the angle between the central line (y-axis) and the line from the center
            //to the last point of the involute curve.
            cv::Point2d point = m_involute[m_involute.size() - 1];
            m_curve_between_base_and_dedendum_circle.push_back(
                    cv::Point2d(point.x,
                            point.y - (point.y - m_fillet_radius - (m_dedendum_diameter / 2) * cos(m_theta0)) * i / n)
            );
        }
    }

/**
 * To calculate the dedendum circle
 */
    void SpurGear::caculateDedendumCircle() {
        int n = 5;
        for (int i = 0; i < n; i++) {
            //(pi/m_teeth_number-theta0) angle subtended for dedendum arc
            double subtendedAngleForDedendumArc = M_PI / m_teeth_number - m_theta0;
            double thetaR = m_theta0 + subtendedAngleForDedendumArc * i / (n - 1);
            m_dedendum_circle.push_back(cv::Point2d(m_dedendum_diameter * sin(thetaR) / 2,
                                                m_dedendum_diameter * cos(thetaR) / 2));
        }
//        cout << m_dedendum_circle;
    }

/**
 * To calculate fillet
 * to draw the quarter of a circle from the last point of the non-involute part to
 * the tangent of the dedendum circle.
 */
    void SpurGear::caculateFillet() {
        int n = 5;
        for (int i = 0; i < n; i++) {
            m_fillet.push_back(cv::Point2d(
                    m_dedendum_circle[0].x - m_fillet_radius * cos(i * M_PI / (2 * (n - 1))),
                    m_dedendum_circle[0].y + m_fillet_radius * (1 - sin(i) * M_PI / 2 * (n - 1))
            ));
        }
    }

/**
 * To reflect the involute curve about y axis to get the whole tooth
 */
    void SpurGear::getWholeTeethReflection() {
        vector<vector<cv::Point2d>> pairVectorList = vector<vector<cv::Point2d>>();

        pairVectorList.push_back(m_addendum_circle);
        pairVectorList.push_back(m_involute);
        pairVectorList.push_back(m_curve_between_base_and_dedendum_circle);
        pairVectorList.push_back(m_fillet);
        pairVectorList.push_back(m_dedendum_circle);

        for (vector<cv::Point2d> v : pairVectorList) {
            m_gear.insert(m_gear.end(), v.begin(), v.end());
        }

        vector<cv::Point2d> reflect = vector<cv::Point2d>();
        for (cv::Point2d p : m_gear) {
            reflect.push_back(cv::Point2d(-1 * p.x, p.y));
        }
        reverse(reflect.begin(), reflect.end());
        m_gear.insert(m_gear.end(), reflect.begin(), reflect.end());

        pairVectorList.clear();
        reflect.clear();
    }

/**
 * To rotate and append the tooth to generate the gear
 */
    void SpurGear::generateWholeGear() {
        int size = (int) m_gear.size();

        for (int i = 0; i < m_teeth_number; i++) {
            double theta = 2 * M_PI * i / m_teeth_number;
            double data[4] = {cos(theta), sin(theta), -1 * sin(theta), cos(theta)};
            vector<cv::Point2d> pairList = computeMatrix(data, m_gear, 0, size);
            m_gear.insert(m_gear.end(), pairList.begin(), pairList.end());
        }
    }

    vector<cv::Point2d> SpurGear::computeMatrix(double *matrix, vector<cv::Point2d> points, int begin, int end) {
        vector<cv::Point2d> result = vector<cv::Point2d>();
        for (int i = begin; i < end; i++) {
            result.push_back(cv::Point2d(
                    matrix[0] * points[i].x + matrix[1] * points[i].y,
                    matrix[2] * points[i].x + matrix[3] * points[i].y));
        }
        return result;
    }

    vector<cv::Point2d> SpurGear::getGearCoordinates() {
        generateInvoluteProfile();
        calculateAddendumCircle();
        caculateCurveBetweenBaseAndDedendumCircle();
        caculateDedendumCircle();
        caculateFillet();
        getWholeTeethReflection();
        generateWholeGear();

        return m_gear;
    }

    std::ostream& operator<<(std::ostream& out, const spur_gear::SpurGear& gear) {
        return out << "teeth number: " << gear.getTeethNumber()
                   << ", module: " << gear.getModule()
                   << ", press angle: "<< gear.getPressAngle()<< '\n'
                   << "coordinates: " << '\n' << gear.getGear();
    }

    std::ostream& operator<<(std::ostream& out, const std::vector<cv::Point2d>& list) {
        out << "[\n";
        for (auto point : list) {
            out << point.x <<", "<< point.y << '\n';
        }
        out << "]\n";
        return out;
    }
};

