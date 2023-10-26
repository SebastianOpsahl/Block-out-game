#ifndef GLFWAPPLICATION_H_
#define GLFWAPPLICATION_H_

#include <GLFW/glfw3.h>
#include <string>

class GLFWApplication {
protected:
	std::string name;
	std::string version;
	int width;
	int height;
	GLFWwindow* window;
public:
	GLFWApplication(const std::string& name, const std::string& version);

	~GLFWApplication();

	virtual unsigned int ParseArguments(int argc, char** argv);

	virtual unsigned Init();

	virtual unsigned Run() const = 0;
};

#endif