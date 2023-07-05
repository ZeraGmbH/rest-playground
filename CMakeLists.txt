cmake_minimum_required(VERSION 3.1)
set(PROJECT_NAME zera-vein-rest)

project(${PROJECT_NAME}
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(FeatureSummary)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

find_package(Qt5 COMPONENTS Core CONFIG REQUIRED)

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/external)

ExternalProject_Add(QHTTPENGINE
    GIT_REPOSITORY https://github.com/etherealjoy/qhttpengine.git
    CMAKE_ARGS  -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
                -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_subdirectory(data)
add_subdirectory(src)

