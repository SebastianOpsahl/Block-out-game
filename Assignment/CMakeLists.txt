add_executable(Chess main.cpp)
add_library(ChessApplication ChessApplication.cpp)

target_include_directories(ChessApplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Chess PUBLIC ChessApplication)
target_link_libraries(ChessApplication PUBLIC 
	Engine::GLFWApplication
	Engine::GeometricTools
	Engine::VertexBuffer
	Engine::IndexBuffer
	Engine::BufferLayout
	Engine::VertexArray
	Engine::Shader
	Engine::RenderCommands
	Engine::TextureManager
	Engine::PerspectiveCamera
	Engine::OrthographicCamera
	glad
	glfw
	glm
)

add_custom_command(
	TARGET Chess POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/cube_texture.png
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/cube_texture.png
)

add_custom_command(
	TARGET Chess POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/floor_texture.png
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/floor_texture.png
)

target_compile_definitions(ChessApplication PRIVATE
	TEXTURES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/"
)

target_compile_definitions(Chess PRIVATE STB_IMAGE_IMPLEMENTATION)
target_compile_definitions(Chess PRIVATE STB_IMAGE_STATIC)