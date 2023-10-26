add_library(Shader Shader.cpp)
add_library(Engine::Shader ALIAS Shader)
target_include_directories(Shader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Shader PUBLIC glm glad)