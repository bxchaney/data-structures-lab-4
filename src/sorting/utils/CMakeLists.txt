add_library(utils queue.cpp stack.cpp)

target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
