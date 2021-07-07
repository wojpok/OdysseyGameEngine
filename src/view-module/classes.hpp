#pragma once

namespace view {
	//	================================================================
	//								Camera
	//  ================================================================
	
	std::string camera::toString() { return "Camera"; }
	
	float  camera::position[3] = {-5, 0, 0};
	
	float camera::getX() { return position[0]; }
	float camera::getY() { return position[1]; }
	float camera::getZ() { return position[2]; }
	
	void camera::setX(float x) { position[0] = x; }
	void camera::setY(float y) { position[1] = y; }
	void camera::setZ(float z) { position[2] = z; }
	
	void camera::setPos(float x, float y, float z) {
		 position[0] = x;
		 position[1] = y;
		 position[2] = z;
	}
	
	
	//	================================================================
	//								Renderer
	//  ================================================================
	
	rendererComponent::rendererComponent(shader* prog, shape* sh, unsigned int tex)
		: program(prog), mesh(sh), texture(tex), transform((float*)new glm::mat4(1)) {}
		
	rendererComponent::rendererComponent() 
		: rendererComponent(NULL, NULL, 0) {} 
	

	std::string rendererComponent::toString() { return "Render Component"; }
	
	void rendererComponent::update() {
		program->useProgram();
		program->bindMVP();
		program->bindPos(transform);
		program->bindTexture(texture);
		
		mesh->draw();
	}
	
	float rendererComponent::getX() { return transform[12]; }
	float rendererComponent::getY() { return transform[13]; }
	float rendererComponent::getZ() { return transform[14]; }
	
	void rendererComponent::setX(float x) { transform[12] = x; }
	void rendererComponent::setY(float y) { transform[13] = y; }
	void rendererComponent::setZ(float z) { transform[14] = z; }
	
	void rendererComponent::setPos(float x, float y, float z) {
		 transform[12] = x;
		 transform[13] = y;
		 transform[14] = z;
	}

	//	================================================================
	//								Shape
	//  ================================================================
	
	shape::shape(GLuint vb, GLuint ub, int bs) : vertexBuffer(vb), uvBuffer(ub), bufferSize(bs) { }
	
	shape::shape(const float *uvArr, int uvSize, const float *verArr, int verSize, int stripLength) : bufferSize(stripLength)  {
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);		
		
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, verSize*sizeof(float), verArr, GL_DYNAMIC_DRAW);

		
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uvSize*sizeof(float), uvArr, GL_DYNAMIC_DRAW);
	}
	
	void shape::draw() {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, bufferSize );
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	
	void shape::drawInstantiated( int count) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, bufferSize );
		
		glVertexAttribDivisor(0, 0);
		glVertexAttribDivisor(1, 0); 
		
		glDrawArraysInstanced(GL_TRIANGLES, 0, bufferSize, count);
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	
	shape::~shape() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &uvBuffer);
	}
	
	//	================================================================
	//								Shader
	//  ================================================================
	
	shader::shader() {}
	
	shader::shader(const char * vertex_file_path, const char * fragment_file_path) {
		program = LoadShaders(vertex_file_path, fragment_file_path);
		bindShader(program);
	}
		
	void shader::bindShader(unsigned int prog) {
		program = prog;
		textureId = glGetUniformLocation(program, "myTextureSampler");
		MVPID = 	glGetUniformLocation(program, "MVP");
		posId = 	glGetUniformLocation(program, "offset");
	}
	
	void shader::bindTexture(unsigned int Texture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(textureId, 0);
	}
	
	void shader::bindMVP() {
		glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
	}
	
	void shader::bindPos(float Pos[16]) {
		glUniformMatrix4fv(posId, 1, GL_FALSE, &Pos[0]);
	}
	
	void shader::useProgram() {glUseProgram(program); }
}
