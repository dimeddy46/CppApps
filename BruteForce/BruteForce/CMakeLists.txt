cmake_minimum_required(VERSION 3.13)
project(BruteForce)

set(sources BruteForce.cpp pch.cpp pch.h)
add_executable(${PROJECT_NAME} ${sources})
set(CMAKE_CONFIGURATION_TYPES Release)
<<<<<<< HEAD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Os")

=======
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ot")
>>>>>>> edb7b7c9a85cbb6af97690dd84d30423614b6f93
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${sources} DESTINATION src)


