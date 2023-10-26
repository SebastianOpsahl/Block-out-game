#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <tclap/CmdLine.h>
#include <iostream>

#include "GLFWApplication.h"

GLFWApplication::GLFWApplication(const std::string& name, const std::string& version) {
	this->name = name;
	this->version = version;
}

GLFWApplication::~GLFWApplication() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

unsigned int GLFWApplication::ParseArguments(int argc, char** argv) {
	try {
		TCLAP::CmdLine cmd(name, ' ', version);

		TCLAP::ValueArg<int> widthArg("w", "width", "Width of window", false, 800, "int");
		cmd.add(widthArg);

		TCLAP::ValueArg<int> heightArg("g", "height", "Height of window", false, 800, "int");
		cmd.add(heightArg);

		cmd.parse(argc, argv);
		width = widthArg.getValue();

		height = heightArg.getValue();
	}
	catch (TCLAP::ArgException& e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

unsigned GLFWApplication::Init() {
	if (glfwInit()) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			return EXIT_FAILURE;
		}

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}