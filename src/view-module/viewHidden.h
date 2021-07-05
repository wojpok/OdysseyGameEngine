#pragma once

#include <GLFW/glfw3.h>

namespace view {
		
	extern GLFWwindow* window;
	
	//wrapper functions for onpegl. It helps keep main.cpp as tidy as possible
	void init();
	void clearFrame();
	void pushFrame();
	bool isContextOpen();
	void clearContext();
	
}
