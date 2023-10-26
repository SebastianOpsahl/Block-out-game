#ifndef CHESSAPLLICATION_H_
#define CHESSAPPLICATION_H_

#include <GLFWApplication.h>

class ChessApplication : public GLFWApplication {
	public:
		ChessApplication(const std::string& name, const std::string& version);

		unsigned Run() const;
};

#endif