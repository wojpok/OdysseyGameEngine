#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace view {
		
	extern GLFWwindow* window;
	
	//wrapper functions for onpegl. It helps keep main.cpp as tidy as possible
	void init();
	void clearFrame();
	void pushFrame();
	bool isContextOpen();
	void clearContext();
	void computeMatricesFromInputs();
	
	extern glm::mat4 MVP;
	
}
