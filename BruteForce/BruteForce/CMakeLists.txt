cmake_minimum_required(VERSION 3.2)
project(BruteForce)

set(sources BruteForce.cpp pch.cpp pch.h)
add_executable(BruteForce ${sources})
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Ot")
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES BruteForce.cpp pch.cpp pch.h DESTINATION src)



