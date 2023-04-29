add_library(sorting qsort.cpp mergesort.cpp)
add_subdirectory(utils)

target_include_directories(sorting INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sorting PUBLIC utils)