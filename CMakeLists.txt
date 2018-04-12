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

if(MINGW)
	set(PNGwriter_DIR "D:/pngwriter/install/lib/cmake/PNGwriter")

	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PNGwriter_DIR)

	set(ZLIB_INCLUDE_DIR "D:\\zlib\\install\\include")
	set(ZLIB_LIBRARY_RELEASE "D:/zlib/install/lib/libzlib.dll.a")
	set(ZLIB_LIBRARY_DEBUG "D:/zlib/install/lib/libzlib.dll.a")

	set(PNG_LIBRARY_RELEASE "D:/lpng1632/out/lib/libpng.a")
	set(PNG_LIBRARY_DEBUG "D:/lpng1632/out/lib/libpng.a")
	set(PNG_PNG_INCLUDE_DIR "D:\\lpng1632\\out\\include")
else()
	set(PNGwriter_DIR "D:\\pngwriter\\install-vs\\lib\\cmake\\PNGwriter")

	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PNGwriter_DIR)

	set(ZLIB_INCLUDE_DIR "D:\\zlib\\install-vs\\include")
	set(ZLIB_LIBRARY_RELEASE "D:\\zlib\\install-vs\\lib\\zlibd.lib")
	set(ZLIB_LIBRARY_DEBUG "D:\\zlib\\install-vs\\lib\\zlibd.lib")

	set(PNG_LIBRARY_RELEASE "D:\\lpng1632\\out-vs\\libpng\\lib\\libpng16d.lib")
	set(PNG_LIBRARY_DEBUG "D:\\lpng1632\\out-vs\\libpng\\lib\\libpng16d.lib")
	set(PNG_PNG_INCLUDE_DIR "D:\\lpng1632\\out-vs\\libpng\\include")
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#link_directories("C:/Users/USER.ASUS/CLionProjects/InvoluteSpurGear/third-party/lib")
find_package(PNGwriter 0.7.0 REQUIRED)

add_executable(InvoluteSpurGear main.cpp SpurGear.h utils/AngleUtils.h utils/AngleUtils.cpp utils/VectorUtils.h SpurGear.cpp utils/Pair.h)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(InvoluteSpurGear PRIVATE PNGwriter::PNGwriter ${OpenCV_LIBS})
