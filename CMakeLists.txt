
cmake_minimum_required(VERSION 3.16)

project(OpenGLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hardware src/main.cpp)
install(TARGETS hardware RUNTIME 
    DESTINATION bin
)
