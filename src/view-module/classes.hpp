#pragma once

namespace view {
	//	================================================================
	//								Renderer
	//  ================================================================
	
	rendererComponent::rendererComponent(shader* prog, shape* sh, unsigned int tex)
		: program(prog), mesh(sh), texture(tex) {}
		
	rendererComponent::rendererComponent() 
		: rendererComponent(NULL, NULL, 0) {} 
	

	std::string rendererComponent::toString() { return "Render Component0"; }
	
	void rendererComponent::update() {
		
	}

	//	================================================================
	//								Shape
	//  ================================================================
	
	shape::shape(GLuint vb, GLuint ub, int bs) : vertexBuffer(vb), uvBuffer(ub), bufferSize(bs) { }
	
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
	
	void shader::bindTexture(unsigned int Texture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(textureId, 0);
	}
	
	void shader::bindMVP(float MVP[16]) {
		glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0]);
	}
	
	void shader::bindPos(float Pos[16]) {
		glUniformMatrix4fv(posId, 1, GL_FALSE, &Pos[0]);
	}
	
	void shader::useProgram() {glUseProgram(program); }
}
