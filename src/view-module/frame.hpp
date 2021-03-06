/*
 * 
 * 			Manages user input and calculates deltaTime
 */

namespace view {
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	glm::mat4 getViewMatrix(){
		return ViewMatrix;
	}
	
	glm::mat4 getProjectionMatrix(){
		return ProjectionMatrix;
	}
	
	glm::mat4 MVP;

	// Initial position : on +Z
	glm::vec3 position = glm::vec3( -5, 0, 0 ); 
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14/2;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 50.0f;

	float speed = 1.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	float deltaTime;

	int blockInd = 0;
	
	
	int frameCnt = 1;
	float timeElapsed = 0;
	float frameL = 1;
	
	void (*refreshFunc)();
	
	void refreshFuncSet(void (*ptr)()) {
		refreshFunc = ptr;
	}
	
	void computeMatricesFromInputs(){
		
		position = *(glm::vec3*)camera::position;

		// Get mouse position
		double xpos = 512 , ypos = 384;
		
		// ============ camera rotation disabled, uncomment if needed ================
		
		/*glfwGetCursorPos(window, &xpos, &ypos);		
		
			// Reset mouse position for next frame
			glfwSetCursorPos(window, windowHeight/2, windowWidth/2); 		
			
			// Compute new orientation
			//horizontalAngle += mouseSpeed * float(windowHeight/2 - xpos );
			//verticalAngle   += mouseSpeed * float(windowWidth/2 - ypos );
		// Direction : Spherical coordinates to Cartesian coordinates conversion
		*/
		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle), 
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);
		
		// Right vector
		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f/2.0f), 
			0,
			cos(horizontalAngle - 3.14f/2.0f)
		);
		
		// Up vector
		glm::vec3 up = glm::cross( right, direction );

		float FoV = initialFoV;//  - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		ProjectionMatrix = glm::perspective(glm::radians(FoV), 16.0f / 9.0f, 0.1f, 100.0f);
		//ProjectionMatrix = glm::ortho( -1024.f, 1024.f, -768.f, 768.f);
		// Camera matrix
		ViewMatrix       = glm::lookAt(
									position,           // Camera is here
									position+direction, // and looks here : at the same position, plus "direction"
									up                  // Head is up (set to 0,-1,0 to look upside-down)
							   );
		
		MVP = ProjectionMatrix * ViewMatrix;
		
		// For the next frame, the "last time" will be "now"
		//lastTime = currentTime;
	}
}
