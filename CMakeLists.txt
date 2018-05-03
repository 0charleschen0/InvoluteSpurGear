cmake_minimum_required(VERSION 3.9)
project(InvoluteSpurGear)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS)

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

set(SOURCES main.cpp SpurGear.cpp widget.cpp)

set(MOC_HEADERS SpurGear.h utils/Radian.h widget.h)

set(UIS Main.ui)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)
add_definitions( ${QT_DEFINITIONS})
include_directories( ${CMAKE_BINARY_DIR})

qt5_wrap_ui(UI_HEADERS ${UIS})
qt5_wrap_cpp( MOC_SRCS ${MOC_HEADERS} )

add_executable(InvoluteSpurGear ${SOURCES} ${MOC_SRCS} ${UI_HEADERS})

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(InvoluteSpurGear ${OpenCV_LIBS} Qt5::Core Qt5::Widgets Qt5::Gui)
