#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GLFWApplication.h>
#include <GeometricTools.h>
#include <iostream>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <BufferLayout.h>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
#include <RenderCommands.h>
#include <TextureManager.h>
#include <PerspectiveCamera.h>
#include <OrthographicCamera.h>

#include "ChessApplication.h"

ChessApplication::ChessApplication(const std::string& name, const std::string& version) : GLFWApplication(name, version) {

}

unsigned ChessApplication::Run() const {
////////////////////////////////////////////////////////////////////////////////////////

	// Colors for the chessboard

	float colors[4 * 8 * 8 * 3];
	int n = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 3 * 4; ++k)
				colors[n++] = 0.0f;
			for (int k = 0; k < 3 * 4; ++k)
				colors[n++] = 1.0f;
		}
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 3 * 4; ++k)
				colors[n++] = 1.0f;
			for (int k = 0; k < 3 * 4; ++k)
				colors[n++] = 0.0f;
		}
	}

	float greenField[4*3];
	for (int i = 0; i < 4; ++i) {
		greenField[i * 3] = 0.0f;
		greenField[i * 3 + 1] = 1.0f;
		greenField[i * 3 + 2] = 0.0f;
	}

	// Geometry and topology for the chessboard and cube

	std::array<float, 4*4*8*8> floorGeo = GeometricTools::UnitGridGeometry2DWTCoords<8, 8>();
	std::array<unsigned int, 8 * 8 * 6> gridTop = GeometricTools::UnitGridTopologyTriangles<8, 8>();

	std::array<float, 3 * 24 * 2> cubeGeo = GeometricTools::UnitCube3D24WNormals;
	std::array<unsigned int, 6 * 3 * 2> cubeTop = GeometricTools::UnitCube3DTopologyTriangles24;

/////////////////////////////////////////////////////////////////////////////////////////////

	// Locations of the chess pieces

	std::array<glm::ivec2, 16> blue;
	std::array<glm::ivec2, 16> red;

	for (int i = 0; i < 8; ++i) {
		blue[i] = glm::ivec2(0, i);
		red[i] = glm::ivec2(7, i);
	}
	for (int i = 0; i < 8; ++i) {
		blue[8+i] = glm::ivec2(1, i);
		red[8+i] = glm::ivec2(6, i);
	}

//////////////////////////////////////////////////////////////////////////////////////////

	// Setting up transformation matrices for the chessbaord and cube

	PerspectiveCamera pc({45.0f, (float)width, (float)height, 1.0f, -10.0f},
		glm::vec3(0, 5, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	auto chessboardModelMatrix = glm::mat4(1.0f);
	auto chessboardRotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	auto chessboardTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	auto chessboardScale = glm::scale(glm::mat4(1.0f), glm::vec3(8.0f, 8.0f, 8.0f));
	chessboardModelMatrix = chessboardTranslation * chessboardRotation * chessboardScale;

	auto cubeModelMatrix = glm::mat4(1.0f);
	auto cubeRotation = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	auto cubeTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, -3.0f/4.0f, -3.5f));
	auto cubeScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	cubeModelMatrix = cubeRotation * cubeTranslation * cubeScale;

//////////////////////////////////////////////////////////////////////////////////////////

	// Making vertex arrays, vertex buffers and index arrays for the chessboard and cube

	auto board = std::make_shared<VertexArray>();
	board->Bind();

	auto boardBuffer = std::make_shared<VertexBuffer>(floorGeo.data(), floorGeo.size() * sizeof(float));
	BufferLayout boardLayout({
		{ShaderDataType::Float2, "position"},
		{ShaderDataType::Float2, "tcoords"}
	});
	boardBuffer->SetLayout(boardLayout);

	auto boardColor = std::make_shared<VertexBuffer>(colors, 4 * 8 * 8 * 3 * sizeof(float));
	BufferLayout colorLayout({ {ShaderDataType::Float3, "color"} });
	boardColor->SetLayout(colorLayout);

	board->AddVertexBuffer(boardBuffer);
	board->AddVertexBuffer(boardColor);

	auto boardIb = std::make_shared<IndexBuffer>(gridTop.data(), gridTop.size());
	board->SetIndexBuffer(boardIb);

	auto cube = std::make_shared<VertexArray>();
	cube->Bind();

	auto cubePos = std::make_shared<VertexBuffer>(cubeGeo.data(), cubeGeo.size() * sizeof(float));
	BufferLayout cubePosLayout({
		{ShaderDataType::Float3, "position"},
		{ShaderDataType::Float3, "normal"}
	});
	cubePos->SetLayout(cubePosLayout);

	cube->AddVertexBuffer(cubePos);

	auto cubeIb = std::make_shared<IndexBuffer>(cubeTop.data(), cubeTop.size());
	cube->SetIndexBuffer(cubeIb);

	// Loading the two textures

	TextureManager* tm = TextureManager::GetInstance();
	if (!tm->LoadTexture2DRGBA("floorTexture", std::string(TEXTURES_DIR) + std::string("floor_texture.png"), 0, false)) {
		std::cout << "Failed to load floor" << std::endl;
		return EXIT_FAILURE;
	}

	if (!tm->LoadCubeMapRGBA("cubeTexture", std::string(TEXTURES_DIR) + std::string("cube_texture.png"), 1, false)) {
		std::cout << "Failed to load cube" << std::endl;
		return EXIT_FAILURE;
	}

///////////////////////////////////////////////////////////////////////////////////////

	// Shader programs for the chessboard and cube

	const std::string vertexShaderSrc = R"(
#version 430 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 tcoords;
layout(location = 2) in vec3 color;

out vec2 vs_tcoords;
out vec4 vs_color;

uniform mat4 u_camera;
uniform mat4 u_model;

void main()
{
gl_Position = u_camera * u_model * vec4(position, 0.0, 1.0);
vs_tcoords = tcoords;
vs_color = vec4(color, 1.0);
}
)";

	const std::string fragmentShaderSrc = R"(
#version 430 core

in vec2 vs_tcoords;
in vec4 vs_color;
out vec4 finalColor;

layout(binding=0) uniform sampler2D u_floorSampler;
uniform bool u_setTexture;
uniform float u_ambientStrength = 1.0f;

void main()
{
if(u_setTexture) finalColor = mix(vs_color, texture(u_floorSampler, vs_tcoords), 0.7) * u_ambientStrength;
else finalColor = vs_color;
}
)";

	auto shader = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);
	shader->Bind();

	const std::string cubeVertSrc = R"(
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_camera;
uniform mat4 u_model;

out vec3 vs_position;
out vec4 vs_normal;

void main() {
gl_Position = u_camera * u_model * vec4(position, 1.0f);
vs_position = position;
vs_normal = normalize(u_model * vec4(normal, 1.0f));
}
)";

	const std::string cubeFragSrc = R"(
#version 430 core

layout(binding = 1) uniform samplerCube u_texture;

uniform vec3 u_color;
uniform bool u_setTexture;
uniform float u_ambientStrength = 1.0f;
uniform vec3 u_lightSourcePosition;
uniform float u_diffuseStrength;
uniform vec3 u_cameraPosition;
uniform float u_specularStrength = 0.5f;

in vec3 vs_position;
in vec4 vs_normal;
out vec4 color;

void main() {
if(u_setTexture) color = mix(vec4(u_color, 1.0f), texture(u_texture, vs_position), 0.7);
else color = vec4(u_color, 1.0f);

vec3 lightDirection = normalize(vec3(u_lightSourcePosition - vs_position));
float diffuseStrength = max(dot(lightDirection, vs_normal.xyz), 0.0f) * u_diffuseStrength;
vec3 reflectedLight = normalize(reflect(-lightDirection, vs_normal.xyz));
vec3 observerDirection = normalize(u_cameraPosition - vs_position);
float specFactor = pow(max(dot(observerDirection, reflectedLight), 0.0f), 12);
float specular = specFactor * u_specularStrength;

color *= (u_ambientStrength + diffuseStrength + specular);
}
)";

	auto cubeShader = std::make_shared<Shader>(cubeVertSrc, cubeFragSrc);
	cubeShader->Bind();

////////////////////////////////////////////////////////////////////////////////////////////

	shader->UploadUniformMatrixFloat4x4("u_camera", pc.GetViewProjectionMatrix());
	shader->UploadUniformMatrixFloat4x4("u_model", chessboardModelMatrix);
	shader->UploadUniformInt("u_setTexture", false);
	cubeShader->UploadUniformMatrixFloat4x4("u_camera", pc.GetViewProjectionMatrix());
	cubeShader->UploadUniformMatrixFloat4x4("u_model", chessboardModelMatrix);
	cubeShader->UploadUniformInt("u_setTexture", false);
	cubeShader->UploadUniformFloat3("u_lightSourcePosition", pc.GetPosition());
	cubeShader->UploadUniformFloat("u_diffuseStrength", 0.5f);
	cubeShader->UploadUniformFloat3("u_cameraPosition", pc.GetPosition());
	cubeShader->UploadUniformFloat("u_specularStrength", 0.5f);

	// Settings for the 3D rendering
	RenderCommands::SetSolidMode();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Making a struct to pass as user pointer

	int selector = 0;
	int selected = -1;
	double deltaTime = 0.0f;
	bool setTexture = false;
	struct Pointers {
		int* pos;
		int* select;
		double* delta;
		glm::mat<4, 4, glm::f32, glm::packed_highp>* rotMatrix;
		PerspectiveCamera* camera;
		std::array<glm::ivec2, 16>* b;
		std::array<glm::ivec2, 16>* r;
		bool* tex;
	};
	Pointers userPointer = {&selector, &selected, &deltaTime, &cubeRotation, &pc, &blue, &red, &setTexture};

	glfwSetWindowUserPointer(window, &userPointer);
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Pointers* p = (Pointers*)glfwGetWindowUserPointer(window);
		int* pos = p->pos;
		int* select = p->select;
		double time = *(p->delta);
		auto* matrix = p->rotMatrix;
		PerspectiveCamera* cam = p->camera;
		auto* b = p->b;
		auto* r = p->r;
		bool* tex = p->tex;
		const float rotSpeed = 1000.0f;
		const float zoomSpeed = 100.0f;
		if (action == GLFW_PRESS) {
			switch (key) {
			case GLFW_KEY_UP:
				if (*pos % 8 != 0) --(*pos); break;
			case GLFW_KEY_DOWN:
				if (*pos % 8 != 7) ++(*pos); break;
			case GLFW_KEY_LEFT:
				if (*pos >= 8) *pos -= 8; break;
			case GLFW_KEY_RIGHT:
				if (*pos <= 55) *pos += 8; break;
			case GLFW_KEY_ENTER: {
				if (*select == -1) {
					for (int i = 0; i < 16; ++i) {
						if ((*b)[i][0] * 8 + (*b)[i][1] == *pos) { *select = *pos; break; }
						if ((*r)[i][0] * 8 + (*r)[i][1] == *pos) { *select = *pos; break; }
					}
				}
				else {
					for (int i = 0; i < 16; ++i) {
						if ((*b)[i][0] * 8 + (*b)[i][1] == *pos || (*r)[i][0] * 8 + (*r)[i][1] == *pos) {
							*select = -1; break;
						}
					}
					for (int i = 0; i < 16; ++i) {
						if ((*b)[i][0] * 8 + (*b)[i][1] == *select) {
							(*b)[i][0] = *pos / 8;
							(*b)[i][1] = *pos % 8;
							*select = -1; break;
						}
						if ((*r)[i][0] * 8 + (*r)[i][1] == *select) {
							(*r)[i][0] = *pos / 8;
							(*r)[i][1] = *pos % 8;
							*select = -1; break;
						}
					}
				}
				break;
			}
			case GLFW_KEY_T:
				*tex = !(*tex); break;
			case GLFW_KEY_Q:
				glfwSetWindowShouldClose(window, GL_TRUE);; break;
			}
		}

		if (action == GLFW_REPEAT ) {
			switch (key) {
			case GLFW_KEY_L: {
				float angle = rotSpeed * time;
				glm::vec3 pos = cam->GetPosition();
				pos = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0)) * glm::vec4(pos, 1.0f));
				cam->SetPosition(pos);
				break;
			}
			case GLFW_KEY_H: {
				float angle = -rotSpeed * time;
				glm::vec3 pos = cam->GetPosition();
				pos = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0)) * glm::vec4(pos, 1.0f));
				cam->SetPosition(pos);
				break;
			}
			case GLFW_KEY_P: {
				float zoom = -zoomSpeed * time;
				glm::vec3 pos = cam->GetPosition();
				if (pos[1] <= 2.0f) break;
				for (int i = 0; i <= 2; ++i)
					pos[i] += pos[i] * zoom;
				cam->SetPosition(pos);
				break;
			}
			case GLFW_KEY_O: {
				float zoom = zoomSpeed * time;
				glm::vec3 pos = cam->GetPosition();
				if (pos[1] >= 20.0f) break;
				for (int i = 0; i <= 2; ++i)
					pos[i] += pos[i] * zoom;
				cam->SetPosition(pos);
				break;
			}
			};
		}
	});

	// Game loop

	double currentFrame, lastFrame = glfwGetTime();
	float ambience = 0.0f;
	bool a = true;
	while (!glfwWindowShouldClose(window)) {

		// Updating deltaTime

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		/**
		if (a) ambience += deltaTime * 0.1f;
		else ambience -= deltaTime * 0.1f;

		if (ambience >= 1.0f) a = false;
		else if (ambience <= 0.0f) a = true;
		*/ ambience = 1.0f;
		//Setting background color

		RenderCommands::SetClearColor(glm::vec3(0.5f, 0.5f, 0.5f) * ambience);
		RenderCommands::Clear();

		shader->Bind();
		board->Bind();

		shader->UploadUniformMatrixFloat4x4("u_camera", pc.GetViewProjectionMatrix());
		shader->UploadUniformInt("u_setTexture", setTexture);
		shader->UploadUniformFloat("u_ambientStrength", ambience);

		// Drawing the chessboard
		/**
		int k = 0;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 8; j += 2) {
				if (selector == k + j) boardColor->BufferSubData(0, sizeof(green), green);
				else boardColor->BufferSubData(0, sizeof(white), white);
				RenderCommands::DrawIndex(board, GL_TRIANGLES, 6, 6 * (k + j));
				if (selector == k + j + 1) boardColor->BufferSubData(0, sizeof(green), green);
				else boardColor->BufferSubData(0, sizeof(black), black);
				RenderCommands::DrawIndex(board, GL_TRIANGLES, 6, 6 * (k + j + 1));
			}
			k += 8;
			for (int j = 0; j < 8; j += 2) {
				if (selector == k + j) boardColor->BufferSubData(0, sizeof(green), green);
				else boardColor->BufferSubData(0, sizeof(black), black);
				RenderCommands::DrawIndex(board, GL_TRIANGLES, 6, 6 * (k + j));
				if (selector == k + j + 1) boardColor->BufferSubData(0, sizeof(green), green);
				else boardColor->BufferSubData(0, sizeof(white), white);
				RenderCommands::DrawIndex(board, GL_TRIANGLES, 6, 6 * (k + j + 1));
			}
			k += 8;
		}
		*/

		boardColor->BufferSubData(3*4*selector * sizeof(GLfloat), 3*4 * sizeof(GLfloat), greenField);
		RenderCommands::DrawIndex(board, GL_TRIANGLES);
		boardColor->BufferSubData(3 * 4 * selector * sizeof(GLfloat), 3 * 4 * sizeof(GLfloat), (void*)(colors+3*4*selector  ));

		cubeShader->Bind();
		cube->Bind();

		cubeShader->UploadUniformMatrixFloat4x4("u_camera", pc.GetViewProjectionMatrix());
		cubeShader->UploadUniformInt("u_setTexture", setTexture);
		cubeShader->UploadUniformFloat("u_ambientStrength", ambience);

		// Drawing the chess pieces at the correct locations

		for (int i = 0; i < 16; ++i) {
			if(blue[i][0] * 8 + blue[i][1] == selected)
				cubeShader->UploadUniformFloat3("u_color", glm::vec3(1.0f, 1.0f, 0.0f));
			else if(blue[i][0] * 8 + blue[i][1] == selector)
				cubeShader->UploadUniformFloat3("u_color", glm::vec3(0.0f, 1.0f, 0.0f));
			else
				cubeShader->UploadUniformFloat3("u_color", glm::vec3(0.0f, 0.0f, 1.0f));

			auto translation = glm::translate(cubeTranslation, glm::vec3((float)blue[i][0], 0.0f, (float)blue[i][1]));
			cubeModelMatrix = cubeRotation * translation * cubeScale;
			cubeShader->UploadUniformMatrixFloat4x4("u_model", cubeModelMatrix);
			RenderCommands::DrawIndex(cube, GL_TRIANGLES);

			if (red[i][0] * 8 + red[i][1] == selected)
				cubeShader->UploadUniformFloat3("u_color", glm::vec3(1.0f, 1.0f, 0.0f));
			else if(red[i][0] * 8 + red[i][1] == selector)
				cubeShader->UploadUniformFloat3("u_color", glm::vec3(0.0f, 1.0f, 0.0f));
			else
				cubeShader->UploadUniformFloat3("u_color", glm::vec3(1.0f, 0.0f, 0.0f));

			translation = glm::translate(cubeTranslation, glm::vec3((float)red[i][0], 0.0f, (float)red[i][1]));
			cubeModelMatrix = cubeRotation * translation * cubeScale;
			cubeShader->UploadUniformMatrixFloat4x4("u_model", cubeModelMatrix);
			cubeShader->UploadUniformFloat3("u_cameraPosition", pc.GetPosition());
			RenderCommands::DrawIndex(cube, GL_TRIANGLES);
		}

		glfwSwapBuffers(window);
	}

	return EXIT_SUCCESS;
}
