cmake_minimum_required(VERSION 3.16)

project(practica1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(practica2 main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

include(GNUInstallDirs)

add_subdirectory(include)

install(TARGETS practica2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
