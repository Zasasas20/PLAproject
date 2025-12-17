cmake_minimum_required(VERSION 3.10.0)
project(SorterDriver VERSION 0.1.0 LANGUAGES C CXX)

find_package(pybind11 REQUIRED)  # or `add_subdirectory(pybind11)`
find_package(PkgConfig REQUIRED)
find_package(Python COMPONENTS Development)
find_package( OpenCV REQUIRED )
pkg_check_modules(LIBCAMERA REQUIRED libcamera)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/lib/ROIExtractionPLA/include
        ${PROJECT_SOURCE_DIR}/lib/ROIExtractionPLA/src
        ${PROJECT_SOURCE_DIR}/lib/Feature-extraction-C-/
        ${OpenCV_INCLUDE_DIRS} 
        ${LIBCAMERA_INCLUDE_DIRS}
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/lib/ROIExtractionPLA/include/*.cpp"
        "${PROJECT_SOURCE_DIR}/lib/ROIExtractionPLA/src/*.hpp"
        "${PROJECT_SOURCE_DIR}/lib/Feature-extraction-C-/*.hpp"
)

add_executable(SorterDriver ${all_SRCS} main.cpp)
target_link_libraries(SorterDriver PRIVATE Python::Python -llccv ${OpenCV_LIBS})