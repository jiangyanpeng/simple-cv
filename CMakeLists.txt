CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(simple.cv)

######## COMPILE #######
SET(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
SET(CMAKE_COMPILE_WARNING_AS_ERROR ON)
SET(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread")

####### EXTERNAL DEPS #######
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
LIST(APPEND CMAKE_FIND_ROOT_PATH "${CMAKE_SOURCE_DIR}/third_party/")
SET(FCV_EXTERNAL_DEPS)
INCLUDE(CVUtils)
INCLUDE(external/simple-base)

######## CONFIG OPTION ######
SET(VERSION "1.0.0")
CONFIGURE_FILE(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h")
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

# add_dependencies(${SIMPLE_CV_LIBS} base)
# add_definitions(-DWITH_LIB_PNG)

####### INCLUDE #######
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/include
)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

####### SOURCES (Projects) #######
FILE(GLOB_RECURSE cv_src 
    ${PROJECT_SOURCE_DIR}/src/*.cc)

####### LIBS THIRDPARTY #######
SET(THIRD_PARTY_LIBS
    ${SIMPLE_BASE_LIBRARIES}
    #${EIGEN3_LIBS}
)

####### INTERNAL LIBS #######
SET(SIMPLE_CV_LIBS cv)

####### BUILD STATIC LIB #######
ADD_LIBRARY(${SIMPLE_CV_LIBS} STATIC ${cv_src})
# add_dependencies(${SIMPLE_CV_LIBS} base)
####### BUILD SHARED LIB #######
# ADD_LIBRARY(${SIMPLE_CV_LIBS} SHARED ${cv_src})

####### INSTALL PYTHON #######
# INSTALL(DIRECTORY  
#     ${PROJECT_SOURCE_DIR}/python DESTINATION ${PROJECT_SOURCE_DIR}/build)

####### UINT TEST   ##########
# ENABLE_TESTING()
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
# SET(GTEST_LIB gtest gtest_main)
# include(googletest)

# ADD_SUBDIRECTORY(third_party/googletest)
# INCLUDE_DIRECTORIES(third_party/googletest/include)

############ BUILD SAMPLE #########
ADD_SUBDIRECTORY(samples)
