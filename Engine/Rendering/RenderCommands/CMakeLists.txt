add_library(RenderCommands INTERFACE)
add_library(Engine::RenderCommands ALIAS RenderCommands)
target_include_directories(RenderCommands INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(RenderCommands INTERFACE glad glm Engine::VertexArray)