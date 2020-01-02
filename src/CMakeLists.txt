find_package(OpenCV  REQUIRED)
project(findballoon)
#aux_source_directory(. DIR_SRCS)
#add_executable(hello ${DIR_SRCS})

#target_link_libraries(hello  ${OpenCV_LIBS}  pthread)

add_executable(${PROJECT_NAME}_test findballon.cpp  line2Dup.cpp main.cpp)
target_link_libraries(${PROJECT_NAME}_test ${OpenCV_LIBS})
