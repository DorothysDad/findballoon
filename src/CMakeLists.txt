find_package(OpenCV  REQUIRED)

aux_source_directory(. DIR_SRCS)
add_executable(hello ${DIR_SRCS})

target_link_libraries(hello  ${OpenCV_LIBS}  pthread)

