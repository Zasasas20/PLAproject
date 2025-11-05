cmake_minimum_required(VERSION 3.10.0)
project(SorterDriver VERSION 0.1.0 LANGUAGES C CXX)

find_package(pybind11 REQUIRED)  # or `add_subdirectory(pybind11)`

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/lib/ROIExtractionPLA/include
        ${PROJECT_SOURCE_DIR}/lib/ROIExtractionPLA/src
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/lib/ROIExtractionPLA/include/*.cpp"
        "${PROJECT_SOURCE_DIR}/lib/ROIExtractionPLA/src/*.hpp"
)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(SorterDriver ${all_SRCS} main.cpp)

find_package(Python COMPONENTS Development)
target_link_libraries(SorterDriver PRIVATE Python::Python ${OpenCV_LIBS})