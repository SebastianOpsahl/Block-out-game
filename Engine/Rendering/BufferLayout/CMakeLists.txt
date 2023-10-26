add_library(BufferLayout INTERFACE)
add_library(Engine::BufferLayout ALIAS BufferLayout)
target_include_directories(BufferLayout INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(BufferLayout INTERFACE Engine::ShadersDataTypes)