add_library(lib_binary_numbers STATIC lib_binary_numbers.cpp)
add_library(lib_cypher_decipher STATIC lib_cypher_decipher.cpp)
add_library(lib_app_cypher STATIC app.cpp)
add_library(lib_app_cajero STATIC app_cajero.cpp)

target_include_directories(lib_binary_numbers PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(lib_cypher_decipher PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(lib_app_cypher PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(lib_app_cajero PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(lib_app_cypher
                        lib_binary_numbers
                        lib_cypher_decipher)

target_link_libraries(lib_app_cajero
                        lib_app_cypher
                        lib_cypher_decipher)