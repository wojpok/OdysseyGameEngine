#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../odysseyGameEngine.h"
#include "../components.hpp"
#include "view.h"
#include "viewHidden.h"
#include "loader.hpp"
#include "classes.hpp"
#include "frame.hpp"

GLFWwindow* window;

namespace view {
	GLFWwindow* window;
	shape* block;
	
	int windowHeight = 1600;
	int windowWidth = 900;
	
	// initation
	void init() {
		if( !glfwInit() ) {
			fprintf( stderr, "Failed to initialize GLFW\n" );
			getchar();
			exit(1);
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Open a window and create its OpenGL context
		window = glfwCreateWindow( windowHeight,  windowWidth, "Odyssey 2: Electric Boogalo", NULL, NULL);
		if( window == NULL ){
			fprintf( stderr, "Failed to open GLFW window.\n" );
			getchar();
			glfwTerminate();
			exit(1);
		}
		glfwMakeContextCurrent(window);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			getchar();
			glfwTerminate();
			exit(1);
		}
		
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		//glfwSetMouseButtonCallback(window, mouse_callback);
		
		glfwPollEvents();
		glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		
		//anti-aliasing
		glEnable(GL_MULTISAMPLE);  

		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS); 
		glEnable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	
	// opengl specific utilities
	void clearFrame() {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}
	void pushFrame() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	bool isContextOpen() {
		return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 ;
	}
	
	void clearContext() {
		glfwTerminate();
	}
}
