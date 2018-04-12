#include <iostream>

#include "SpurGear.h"

#include "third-party/include/opencv2/opencv.hpp"
#include "third-party/include/opencv2/imgproc/imgproc.hpp"
#include "third-party/include/opencv2/highgui/highgui.hpp"

#include "third-party/include/pngwriter.h"

const string window_name = "Gear Preview";

const double DISPLAY_DPI = 72.0;
const double INCH_PER_MM = 25.4;

cv::Mat drawContour(vector<cv::Point2d> contour) {

    vector<cv::Point> points = vector<cv::Point>();
    for (cv::Point2d point2d : contour) {
        cv::Point point = cv::Point(round(1000 - (point2d.x*DISPLAY_DPI/INCH_PER_MM + 500)),
                                    round(point2d.y*DISPLAY_DPI/INCH_PER_MM + 500));
        points.push_back(point);
    }

    const cv::Point *pts = (const cv::Point *) cv::Mat(points).data;
    int npts = cv::Mat(points).rows;

    cv::Mat src = cv::Mat::zeros(cv::Size(1000, 1000), CV_8UC3);

    // draw the polygon
    polylines(src, &pts, &npts, 1, false, cv::Scalar(255, 0, 0), 1, CV_AA, 0);
    return src;
}

int main() {
    int teeth_number;
    double module;
    double press_angle;

    cout<<"Please input the teeth number: ";
    cin>>teeth_number;
    cout<<"Please input the module: ";
    cin>>module;
    cout<<"Please input the press angle: ";
    cin>>press_angle;

    spur_gear::SpurGear gear = spur_gear::SpurGear(teeth_number, module, press_angle);
    vector<cv::Point2d> points = gear.getGearCoordinates();

    pngwriter png(500, 500, 0, "test.png");

    for (cv::Point2d point2d : points) {
        png.plot(point2d.x*DISPLAY_DPI/INCH_PER_MM + 250,
                 point2d.y*DISPLAY_DPI/INCH_PER_MM + 250,
                 0.0,
                 0.0,
                 1.0);
    }

    png.close();


    //cv::Mat src = drawContour(points);
    //std::cout << gear;

    cv::Mat src = cv::imread("test.png");

    /// Create a window
    imshow(window_name, src);

    /// Wait until user exit program by pressing a key
    cv::waitKey(0);

    return 0;
}
