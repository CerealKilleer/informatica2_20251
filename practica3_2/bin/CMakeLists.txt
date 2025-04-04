add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
                        lib_app_cajero)

include_directories(${PROJECT_SOURCE_DIR}/include)