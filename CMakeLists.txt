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

find_package(Qt5 COMPONENTS Core Network CONFIG REQUIRED)
find_package(qhttpengine REQUIRED)

add_subdirectory(data)
add_subdirectory(src)

