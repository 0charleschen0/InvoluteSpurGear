#include <iostream>

#include "SpurGear.h"

#include "third-party/include/opencv2/opencv.hpp"
#include "third-party/include/opencv2/imgproc/imgproc.hpp"
#include "third-party/include/opencv2/highgui/highgui.hpp"

#include "third-party/include/pngwriter.h"

const string window_name = "Gear Preview";

const double DISPLAY_DPI = 72.0;
const double INCH_PER_MM = 25.4;

namespace spur_gear {
    cv::Mat drawContour(vector<cv::Point2d> contour) {

        cv::Mat src = cv::Mat::zeros(cv::Size(500, 500), CV_8UC3);

        vector<cv::Point> points = vector<cv::Point>();
        for (cv::Point2d point2d : contour) {
            points.push_back( cv::Point(static_cast<int>(point2d.x * DISPLAY_DPI / INCH_PER_MM + 250),
                                        static_cast<int>(point2d.y * DISPLAY_DPI / INCH_PER_MM + 250)));
        }

        string filename = "test.txt";
        fstream fp;
        fp.open(filename, ios::out);
        if(fp) {
            fp<<points;
        }

        const cv::Point *pts = (const cv::Point *) cv::Mat(points).data;
        int npts = cv::Mat(points).rows;

        // draw the polygon
        polylines(src, &pts, &npts, 1, false, cv::Scalar(255, 0, 0), 1, CV_AA, 0);

//    cv::Point lastPoint = points[0];
//    for (auto point : points) {
//        cv::line(src, lastPoint, point, cv::Scalar(255, 0, 0), 1, cv::LINE_AA, 0);
//    }

        return src;
    }

};

int main() {
    int teeth_number;
    double module;
    double press_angle;

//    cout<<"Please input the teeth number: ";
//    cin>>teeth_number;
//    cout<<"Please input the module: ";
//    cin>>module;
//    cout<<"Please input the press angle: ";
//    cin>>press_angle;
//
    spur_gear::SpurGear gear = spur_gear::SpurGear();
    vector<cv::Point2d> points = gear.getGearCoordinates();
//
//    pngwriter png(500, 500, 0, "test.png");
//
//    for (cv::Point2d point2d : points) {
//        png.plot(point2d.x*DISPLAY_DPI/INCH_PER_MM + 250,
//                 point2d.y*DISPLAY_DPI/INCH_PER_MM + 250,
//                 0.0,
//                 0.0,
//                 1.0);
//    }
//
//    png.close();


    cv::Mat src = spur_gear::drawContour(points);
    cv::imwrite("test.png", src);

    //std::cout << gear;

    //cv::Mat src = cv::imread("test.png");

    /// Create a window
    imshow(window_name, src);

    /// Wait until user exit program by pressing a key
    cv::waitKey(0);

    return 0;
}
