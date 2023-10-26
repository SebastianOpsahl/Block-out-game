add_library(Camera INTERFACE)
add_library(Engine::Camera ALIAS Camera)
target_include_directories(Camera INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Camera INTERFACE Engine::Camera)