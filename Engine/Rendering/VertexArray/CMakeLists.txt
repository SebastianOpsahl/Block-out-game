add_library(VertexArray VertexArray.cpp)
add_library(Engine::VertexArray ALIAS VertexArray)
target_include_directories(IndexBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(VertexArray PUBLIC Engine::IndexBuffer Engine::VertexBuffer glad)