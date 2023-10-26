#include <iostream>
#include <ChessApplication.h>

int main(int argc, char* argv[]) {
	ChessApplication application("Chess", "1.0");

	if (application.ParseArguments(argc, argv) == EXIT_FAILURE) {
		std::cout << "Failed to parse arguments." << std::endl;
		return EXIT_FAILURE;
	}

	if (application.Init() == EXIT_FAILURE) {
		std::cout << "Failed to initialize GLFW." << std::endl;
		return EXIT_FAILURE;
	}

	return application.Run();
}