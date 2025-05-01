add_library(lib_router STATIC router.cpp)
target_include_directories(lib_router PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_library(lib_network STATIC network.cpp)
target_include_directories(lib_network PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(lib_network PRIVATE lib_router)  