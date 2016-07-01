cmake_minimum_required (VERSION 2.6)
project(ObjectTracker)

set(CMAKE_CXX_FLAGS "-std=c++11")

#Find OpenCV
find_package(OpenCV REQUIRED)

set(SRCS src/main.cpp)
      
add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}) 
