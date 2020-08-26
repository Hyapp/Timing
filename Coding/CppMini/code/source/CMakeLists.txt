include_directories(${PROJECT_SOURCE_DIR}/lib/include)
include_directories(${PROJECT_SOURCE_DIR}/code/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

aux_source_directory(./ srcs)

add_executable(timeCpp ${srcs})

target_link_libraries(timeCpp lib)
