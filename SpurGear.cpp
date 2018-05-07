#include <algorithm>
#include "SpurGear.h"

/**
 * /To calculate the coordinates of the involute profile
 */
namespace SpurGear {
    SpurGear::SpurGear(const int t_teethNumber, const double t_module, const double t_press,
             const double t_fillet_radius, const double t_shift, const double t_backlash)
            : m_teeth_number(t_teethNumber),
              m_module(t_module),
              m_press_angle(Radian(t_press)),
              m_fillet_radius(t_fillet_radius),
              m_shift(t_shift),
              m_backlash(t_backlash){
        this->m_dimetral_pitch = 25.4 / m_module;
        this->m_pitch_diameter = m_teeth_number * m_module;
        this->m_base_circle_diameter = m_pitch_diameter * cos(m_press_angle);
        this->m_addendum_diameter = m_pitch_diameter + 2 * m_module * (1 + m_shift);
        this->m_dedendum_diameter = m_pitch_diameter - 2.5 * m_module;
    }

    bool SpurGear::isUnderCut() {
        int undercut= static_cast<int>((2.0 * (1.0 - m_shift)/(std::pow(sin(m_press_angle), 2))) + 1.0);
        return (m_teeth_number < undercut);
    }

    void SpurGear::generateInvoluteProfile() {
        int n = 10;

        for (int i = 0; i < n; i++) {
            double r = m_addendum_diameter / 2 - (m_addendum_diameter - m_base_circle_diameter) * i / (2 * (n - 1));
            double phi = acos(m_base_circle_diameter / (2 * r));

            //Involute equation for a angle x (radians) : f(x) = tan(x) - x
            double theta = (M_PI / (2 * m_teeth_number)
                            +  2 * m_shift * tan(m_press_angle) / m_module
                            + (tan(m_press_angle) - m_press_angle.getRadian()) - (tan(phi) - phi));

            m_involute.emplace_back(r * sin(theta) - m_backlash, r * cos(theta));
        }

//        cout << m_involute;
    }

    /**
     * To calculate the addendum circle
     */
    void SpurGear::calculateAddendumCircle() {
        int n = 5;

        double phi = acos(m_base_circle_diameter / (m_addendum_diameter));
        double theta = (M_PI / (2 * m_teeth_number) + 2 * m_shift * tan(m_press_angle) / m_module
                        + (tan(m_press_angle) - m_press_angle.getRadian()) - (tan(phi) - phi));

        for (int i = 0; i < n; i++) {
            double thetaO = theta * i / (n - 1);
            m_addendum_circle.emplace_back((m_addendum_diameter / 2) * sin(thetaO),
                                           (m_addendum_diameter / 2) * cos(thetaO));
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
        cv::Point2d point = m_involute[m_involute.size() - 1];
        for (int i = 0; i < n; i++) {
            //to find the angle between the central line (y-axis) and the line from the center
            //to the last point of the involute curve.
            m_curve_between_base_and_dedendum_circle.emplace_back(
                    point.x,
                    point.y - (point.y - m_fillet_radius - (m_dedendum_diameter / 2) * cos(m_theta0)) * i / n);
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
            m_dedendum_circle.emplace_back(m_dedendum_diameter * sin(thetaR) / 2,
                                           m_dedendum_diameter * cos(thetaR) / 2);
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
            m_fillet.emplace_back(
                    m_dedendum_circle[0].x - m_fillet_radius * cos(i * M_PI / (2 * (n - 1))),
                    m_dedendum_circle[0].y + m_fillet_radius * (1 - sin(i * M_PI / 2 * (n - 1))));
        }
    }

/**
 * To reflect the involute curve about y axis to get the whole tooth
 */
    void SpurGear::getWholeTeethReflection() {
        std::vector<std::vector<cv::Point2d>> pairVectorList = std::vector<std::vector<cv::Point2d>>();

//        pairVectorList.push_back(m_addendum_circle);
        pairVectorList.push_back(m_involute);
//        pairVectorList.push_back(m_curve_between_base_and_dedendum_circle);
//        pairVectorList.push_back(m_fillet);
//        pairVectorList.push_back(m_dedendum_circle);

        for (std::vector<cv::Point2d> v : pairVectorList) {
            m_gear.insert(m_gear.end(), v.begin(), v.end());
        }

        std::vector<cv::Point2d> reflect = std::vector<cv::Point2d>();
        for (cv::Point2d p : m_gear) {
            reflect.emplace_back(-1 * p.x, p.y);
        }
        reverse(m_gear.begin(), m_gear.end());
        m_gear.insert(m_gear.end(), reflect.begin(), reflect.end());
        reverse(m_gear.begin(), m_gear.end());

        pairVectorList.clear();
        reflect.clear();
    }

/**
 * To rotate and append the tooth to generate the gear
 */
    void SpurGear::generateWholeGear() {
        auto size = (int) m_gear.size();

        for (int i = 1; i < m_teeth_number; i++) {
            double theta = 2 * M_PI * i / m_teeth_number;
            double data[4] = {cos(theta), sin(theta), -1 * sin(theta), cos(theta)};
            std::vector<cv::Point2d> pairList = computeMatrix(data, m_gear, 0, size);
            m_gear.insert(m_gear.end(), pairList.begin(), pairList.end());
        }
    }

    std::vector<cv::Point2d> SpurGear::computeMatrix(double *matrix, std::vector<cv::Point2d> points, int begin, int end) {
        std::vector<cv::Point2d> result = std::vector<cv::Point2d>();
        for (int i = begin; i < end; i++) {
            result.emplace_back(
                    matrix[0] * points[i].x + matrix[1] * points[i].y,
                    matrix[2] * points[i].x + matrix[3] * points[i].y);
        }
        return result;
    }

    void SpurGear::generateGearCoordinates() {
        generateInvoluteProfile();
        calculateAddendumCircle();
        caculateCurveBetweenBaseAndDedendumCircle();
        caculateDedendumCircle();
        caculateFillet();
        getWholeTeethReflection();
        //generateWholeGear();
    }

    std::vector<cv::Point2d> SpurGear::getGear() {
        if (m_gear.empty()) {
            generateGearCoordinates();
        }
        return m_gear;
    }

    void SpurGear::writeToPngFiles(std::string fileName, int type) {
        cv::Mat src = drawGearWithType(type);
        cv::imwrite(fileName, src);
    }

    cv::Mat SpurGear::drawGearWithType(int type) {
        if (m_gear.empty()) {
            generateGearCoordinates();
        }

        double dpi;

        switch (type) {
            case TYPE_DISPLAY: {
                dpi = DISPLAY_DPI;
            break;
            }
            case TYPE_PRINTER: {
                dpi = PRINTER_DPI;
            break;
            }
            default: {
                dpi = DISPLAY_DPI;
            break;
            }
        }

        double offset = findOptimizedOffset();
        auto border = static_cast<int>(offset*2);
        cv::Mat src = cv::Mat::zeros(cv::Size(border, border), CV_8UC3);
        std::vector<cv::Point> points = std::vector<cv::Point>();
        for (const cv::Point2d &point2d : m_gear) {
            points.emplace_back(static_cast<int>(point2d.x * dpi / INCH_PER_MM + offset),
                                static_cast<int>(point2d.y * dpi / INCH_PER_MM + offset));
        }
        const cv::Point *pts = (const cv::Point *) cv::Mat(points).data;
        int npts = cv::Mat(points).rows;

        // draw the polygon
        polylines(src, &pts, &npts, 1, false, cv::Scalar(255, 0, 0), 1, CV_AA, 0);

        return src;
    }

    double SpurGear::findOptimizedOffset() {
        double max_x = 0.0;
        double max_y = 0.0;

        for (const auto &point : m_gear) {
            max_x = (point.x > max_x) ? point.x : max_x;
            max_y = (point.y > max_y) ? point.y : max_y;
        }

        return round(std::max(max_x, max_y) * DISPLAY_DPI / INCH_PER_MM) + 25;
    }

//    std::ostream& operator<<(std::ostream& out, const SpurGear::SpurGear& gear) {
//        return out << "teeth number: " << gear.getTeethNumber()
//                   << ", module: " << gear.getModule()
//                   << ", press angle: "<< gear.getPressAngle()<< '\n'
//                   << "coordinates: " << '\n' << gear.getGear();
//    }

//    std::ostream& operator<<(std::ostream& out, const std::vector<cv::Point2d>& list) {
//        out << "[\n";
//        for (auto point : list) {
//            out << point.x <<", "<< point.y << '\n';
//        }
//        out << "]\n";
//        return out;
//    }

//    std::ostream& operator<<(std::ostream& out, const std::vector<cv::Point>& list) {
//        out << "[\n";
//        for (auto point : list) {
//            out << point.x <<", "<< point.y << '\n';
//        }
//        out << "]\n";
//        return out;
//    }
}; //SpurGear

