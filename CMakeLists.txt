project(ekfslam)
cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

find_package(PythonLibs 2.7)

set(s_ekf src/main.cpp src/ekfslam.cpp src/tools.cpp)
add_executable(ekfslam ${s_ekf})
target_include_directories(ekfslam PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(ekfslam ${PYTHON_LIBRARIES})

