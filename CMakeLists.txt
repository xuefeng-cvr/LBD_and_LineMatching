#INCLUDE_DIRECTORIES(/usr/include/arpack++/include/)
#INCLUDE_DIRECTORIES(/usr/include/arpack++)

#project name
PROJECT(LILIANTESTS)

cmake_minimum_required(VERSION 2.8)
set(OpenCV_DIR "/home/xfbupt/下载/opencv-2.4.3-rc/")
find_package( OpenCV 3.3 REQUIRED )

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET(BUILD_SHARED_LIBS ON)

## where are user-specific cmake modules
SET(ARPACK_INCLUDE_DIR "/usr/include/arpack++")
SET(ARPACK_LINK_DIR "/usr/lib")
SET(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

#OPTION(USE_BIAS OFF)


#IF(USE_BIAS)
#INCLUDE_DIRECTORIES(${BIAS_INCLUDE_DIR} /usr/local/include/BIAS /usr/include/ImageMagick /usr/local/include/opencv2 ${WXWIDGETS_INCLUDE_DIR})
#LINK_DIRECTORIES( ${BIAS_LINK_DIRECTORIES})
#ENDIF(USE_BIAS)
SET(OpenCV_INCLUDE_DIRS "/usr/local/include/opencv2")
SET(OpenCV_LINK_DIRECTORIES "/usr/local/lib")
INCLUDE_DIRECTORIES(${ARPACK_INCLUDE_DIR} /usr/local/include/opencv)
LINK_DIRECTORIES(${ARPACK_LINK_DIR} /usr/local/lib)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${BIAS_CXX_FLAGS} -O0 -ggdb -std=c++11")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  ${BIAS_C_FLAGS} -O0 -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3") #-fno-omit-frame-pointer")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -O3") #-fno-omit-frame-pointer")

# source files of library "LineMatchingLib" to be created
SET(LineMatchingLib_SRCS
    PairwiseLineMatching.cpp
    LineDescriptor.cpp
    EDLineDetector.cpp
)
# header files to be installed
SET(LineMatchingLib_HEADER
    PairwiseLineMatching.hh
    LineDescriptor.hh
    EDLineDetector.hh
    LineStructure.hh
)


ADD_LIBRARY(LineMatchingLib
            ${LineMatchingLib_SRCS}
            ${LineMatchingLib_HEADER})
#TARGET_LINK_LIBRARIES(LineMatchingLib  arpack /usr/lib/libsuperlu.so  BIASImageBaseD opencv_core opencv_highgui opencv_imgproc BIASDebugD BIASMathAlgoD BIASMathBaseD BIASFilterD arpack++) 
TARGET_LINK_LIBRARIES(LineMatchingLib ${OpenCV_LIBS} arpack /usr/lib/x86_64-linux-gnu/libsuperlu.so arpack++) 


ADD_EXECUTABLE(TestLineMatchingAlgorithm TestLineMatchingAlgorithm.cpp)
TARGET_LINK_LIBRARIES(TestLineMatchingAlgorithm   LineMatchingLib ${OpenCV_LIBS})


