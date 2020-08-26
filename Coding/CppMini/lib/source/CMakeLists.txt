include_directories(${PROJECT_SOURCE_DIR}/lib/include)

aux_source_directory(. lib_srcs)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../lib)

add_library(lib STATIC ${lib_srcs})
