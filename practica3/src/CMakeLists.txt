add_library(lib_binary_numbers STATIC lib_binary_numbers.cpp)
add_library(lib_cypher_decipher STATIC lib_cypher_decipher.cpp)

target_include_directories(lib_binary_numbers PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(lib_cypher_decipher PUBLIC ${PROJECT_SOURCE_DIR}/include)