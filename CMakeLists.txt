cmake_minimum_required(VERSION 3.19)
project(cmakegen LANGUAGES CXX)

find_package(Boost 1.32 REQUIRED COMPONENTS program_options nowide)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})