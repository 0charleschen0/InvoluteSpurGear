#ifndef INVOLUTESPURGEAR_SPURGEAR_H
#define INVOLUTESPURGEAR_SPURGEAR_H

#include "utils/Radian.h"
#include "third-party/include/opencv2/opencv.hpp"
#include "third-party/include/opencv2/core/core.hpp"

namespace SpurGear {
    class SpurGear {

    public:
        const static int TYPE_DISPLAY = 0;
        const static int TYPE_PRINTER = 1;

        explicit SpurGear(int t_teethNumber = 25, double t_module = 4.0, double t_press = 20.0,
                 double t_fillet_radius = 0.05, double t_shift = 0.0, double t_backlash = 0.0);

        void writeToPngFiles(std::string fileName, const int type = TYPE_DISPLAY);

        int getTeethNumber() const {
               return m_teeth_number;
        }

        double getPressAngle() const {
            return m_press_angle.getDegree();
        }

        double getModule() const {
               return m_module;
        }

        std::vector<cv::Point2d> getGear();

        bool isUnderCut();

    private:
        const double DISPLAY_DPI = 72.0;
        const double PRINTER_DPI = 300.0;
        const double INCH_PER_MM = 25.4;

        const int m_teeth_number;
        const double m_module;
        Radian m_press_angle;
        const double m_fillet_radius;
        const double m_shift;
        const double m_backlash;

        double m_dimetral_pitch;
        double m_pitch_diameter;
        double m_base_circle_diameter;
        double m_addendum_diameter;
        double m_dedendum_diameter;

        double m_theta0;

        std::vector<cv::Point2d> m_involute = std::vector<cv::Point2d>();
        std::vector<cv::Point2d> m_addendum_circle = std::vector<cv::Point2d>();
        std::vector<cv::Point2d> m_curve_between_base_and_dedendum_circle = std::vector<cv::Point2d>();
        std::vector<cv::Point2d> m_dedendum_circle = std::vector<cv::Point2d>();
        std::vector<cv::Point2d> m_fillet = std::vector<cv::Point2d>();
        std::vector<cv::Point2d> m_gear = std::vector<cv::Point2d>();

        std::vector<cv::Point2d> computeMatrix(double *matrix, std::vector<cv::Point2d> points, int begin, int end);

        void generateInvoluteProfile();

        void calculateAddendumCircle();

        void caculateCurveBetweenBaseAndDedendumCircle();

        void caculateDedendumCircle();

        void caculateFillet();

        void getWholeTeethReflection();

        void generateWholeGear();

        void generateGearCoordinates();

        double findOptimizedOffset();

        cv::Mat drawGearWithType(int type = TYPE_DISPLAY);
    };

//    std::ostream& operator<<(std::ostream& out, const SpurGear::SpurGear& gear);
//    std::ostream& operator<<(std::ostream& out, const std::vector<cv::Point2d>& list);
//    std::ostream& operator<<(std::ostream& out, const std::vector<cv::Point>& list);
};
#endif //INVOLUTESPURGEAR_SPURGEAR_H
