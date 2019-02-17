cmake_minimum_required(VERSION 3.2)
project(EcLiniare)

set(sources main.cpp)
add_executable(${PROJECT_NAME} ${sources})
set(CMAKE_CONFIGURATION_TYPES Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ot")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${sources} DESTINATION src)
