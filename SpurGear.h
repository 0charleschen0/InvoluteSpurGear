//
// Created by USER on 2018/3/26.
//

#ifndef INVOLUTESPURGEAR_SPURGEAR_H
#define INVOLUTESPURGEAR_SPURGEAR_H

#include "utils/AngleUtils.h"
#include "third-party/include/opencv2/opencv.hpp"
#include "third-party/include/opencv2/core/core.hpp"

namespace spur_gear {
    class SpurGear {

    public:
        SpurGear(const int t_teethNumber = 25, const double t_module = 4.0, const double t_press = 20.0,
                 const double t_fillet_radius = 0.05, const double t_shift = 0.0, const double t_backlash = 0.0);

        vector<cv::Point2d> getGearCoordinates();

        int getTeethNumber() const {
               return m_teeth_number;
        }

        double getPressAngle() const {
               return m_press_angle.getDegreeValue();
        }

        double getModule() const {
               return m_module;
        }

        vector<cv::Point2d> getGear() const {
            return m_gear;
        }

    private:

        const int m_teeth_number;
        const double m_module;
        AngleUtils m_press_angle = AngleUtils();
        const double m_fillet_radius;
        const double m_shift;
        const double m_backlash;

        double m_dimetral_pitch;
        double m_pitch_diameter;
        double m_base_circle_diameter;
        double m_addendum_diameter;
        double m_dedendum_diameter;

        double m_theta0;

        vector<cv::Point2d> m_involute = vector<cv::Point2d>();
        vector<cv::Point2d> m_addendum_circle = vector<cv::Point2d>();
        vector<cv::Point2d> m_curve_between_base_and_dedendum_circle = vector<cv::Point2d>();
        vector<cv::Point2d> m_dedendum_circle = vector<cv::Point2d>();
        vector<cv::Point2d> m_fillet = vector<cv::Point2d>();
        vector<cv::Point2d> m_gear = vector<cv::Point2d>();

        vector<cv::Point2d> computeMatrix(double *matrix, vector<cv::Point2d> points, int begin, int end);

        void generateInvoluteProfile();

        void calculateAddendumCircle();

        void caculateCurveBetweenBaseAndDedendumCircle();

        void caculateDedendumCircle();

        void caculateFillet();

        void getWholeTeethReflection();

        void generateWholeGear();
    };

    std::ostream& operator<<(std::ostream& out, const spur_gear::SpurGear& gear);
    std::ostream& operator<<(std::ostream& out, const std::vector<cv::Point2d>& list);
};
#endif //INVOLUTESPURGEAR_SPURGEAR_H
