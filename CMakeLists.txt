cmake_minimum_required(VERSION 3.9)
project(InvoluteSpurGear)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS -DNO_FREETYPE)

# Where to find CMake modules and OpenCV
if(MINGW)
	set(OpenCV_DIR "D:\\opencv\\install")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
else()
	set(OpenCV_DIR "D:\\opencv-win\\opencv\\build\\x64\\vc15\\lib")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OpenCV_DIR}")
	link_directories("third-party/x64/vs")
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(InvoluteSpurGear main.cpp SpurGear.h utils/AngleUtils.h utils/AngleUtils.cpp utils/VectorUtils.h SpurGear.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(InvoluteSpurGear ${OpenCV_LIBS})
