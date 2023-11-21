CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(simple.cv)

######## COMPILE #######
SET(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
SET(CMAKE_COMPILE_WARNING_AS_ERROR ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread")
# SET(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -Wall -Werror -frounding-math -fsignaling-nans")

OPTION(BUILD_TEST              "Build GooleTest"            OFF)
OPTION(BUILD_USE_STB           "Use STB"                    OFF)

IF(BUILD_USE_STB MATCHES ON)
    ADD_DEFINITIONS(-DSTB_IMAGE_IMPLEMENTATION)
	ADD_DEFINITIONS(-DSTB_IMAGE_WRITE_IMPLEMENTATION)
ENDIF()

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
####### BUILD SHARED LIB #######
# ADD_LIBRARY(${SIMPLE_CV_LIBS} SHARED ${cv_src})
ADD_DEPENDENCIES(${SIMPLE_CV_LIBS} ${CV_EXTERNAL_DEPS})

############ BUILD SAMPLE #########
ADD_SUBDIRECTORY(samples)

####### INSTALL LIBS #######
SET(CV_INSTALL_DIR ${PROJECT_SOURCE_DIR}/install/simple.cv)
INSTALL(TARGETS  ${SIMPLE_CV_LIBS} ${SIMPLE_CV_LIBS} 
        ARCHIVE  DESTINATION ${CV_INSTALL_DIR}/lib
        LIBRARY  DESTINATION ${CV_INSTALL_DIR}/lib)
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${CV_INSTALL_DIR}/include)

####### UINT TEST   ##########
# ENABLE_TESTING()
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
######### Note! Please Use GCC 5.0+ #######
IF(BUILD_TEST)
    cv_download_dependency(
        "https://github.com/google/googletest.git"
        release-1.12.1
        gtest
        ${PROJECT_SOURCE_DIR}/third_party)

    CMAKE_POLICY(PUSH)
    OPTION(BUILD_GMOCK "Builds the googlemock subproject" OFF)
    OPTION(
        gtest_force_shared_crt
        "Use shared (DLL) run-time lib even when Google Test is built as static lib."
        ON)

    IF(NOT DEFINED GTEST_DIR)
        SET(GTEST_DIR third_party/gtest)
    ENDIF()

    ADD_SUBDIRECTORY(${GTEST_DIR})
    SET(GTEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/gtest/googletest/include)
    LIST(APPEND GTEST_LIBRARIES gtest gtest_main)
    CMAKE_POLICY(POP)
ENDIF(BUILD_TEST)

IF(BUILD_TEST)
    ADD_SUBDIRECTORY(tests)
ENDIF()
