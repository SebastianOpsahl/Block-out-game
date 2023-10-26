add_library(TextureManager TextureManager.cpp)
add_library(Engine::TextureManager ALIAS TextureManager)
target_include_directories(TextureManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TextureManager PUBLIC glad stb)