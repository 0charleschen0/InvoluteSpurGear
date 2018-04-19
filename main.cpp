#include <iostream>

#include "SpurGear.h"

#include "third-party/include/opencv2/opencv.hpp"
#include "third-party/include/opencv2/imgproc/imgproc.hpp"
#include "third-party/include/opencv2/highgui/highgui.hpp"

const std::string window_name = "Gear Preview";

int main() {
    int teeth_number;
    double module;
    double press_angle;

//TODO: Use GUI
//    cout<<"Please input the teeth number: ";
//    cin>>teeth_number;
//    cout<<"Please input the module: ";
//    cin>>module;
//    cout<<"Please input the press angle: ";
//    cin>>press_angle;
//
    spur_gear::SpurGear gear = spur_gear::SpurGear();
    std::vector<cv::Point2d> points = gear.getGearCoordinates();
    
    cv::Mat src = gear.drawGearWithDisplayDpi();
    cv::imwrite("test.png", src);

    //std::cout << gear;
    
    /// Create a window
    imshow(window_name, src);

    /// Wait until user exit program by pressing a key
    cv::waitKey(0);

    return 0;
}
