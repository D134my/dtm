cmake_minimum_required(VERSION 3.20)
set(project_name "dtm")
project(${project_name} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#enable testing mode 
option(testing_mode "enable testing" OFF)
if(${testing_mode})
    message("test mode enabled")
    enable_testing()
    add_subdirectory(test)
endif()

message("finding sources ...")
add_subdirectory(src)

add_definitions("-Wall")
add_executable(${project_name}app main.cpp)
target_include_directories(${project_name}app PUBLIC src)
target_link_directories(${project_name}app PUBLIC src)
message("linking d_t_m lib to main")
target_link_libraries(${project_name}app PRIVATE d_t_m)

