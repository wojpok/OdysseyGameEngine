
#include "src/view-module/viewHidden.h"
#include "src/odysseyGameEngine.h"
#include "math2D.hpp"

float playerSpeed = 2;
view::shader *sh2;

class timer : public oge::component {
public:
	void update() override {
		oge::parent->transform[3] += chr::deltaTime;
		
		if (glfwGetKey(view::window, GLFW_KEY_W ) == GLFW_PRESS){
			oge::parent->transform[1] += chr::deltaTime;
		}
		
		if (glfwGetKey(view::window, GLFW_KEY_S ) == GLFW_PRESS){
			oge::parent->transform[1] -= chr::deltaTime;
		}
	}
};

int main() {
	view::init();
	
	view::shader *sh = new view::shader("src/view-module/basicVertex.glsl","src/view-module/basicFragment.glsl");
	//sh2 = new view::shader("src/view-module/basicVertex.glsl","src/view-module/mandFragment.glsl");
	
	static const GLfloat square[] = {
		 0, -0.125, 0.125,
		 0, 0.125, -0.125,
		 0, -0.125, -0.125,
		 0, -0.125, 0.125,
		 0, 0.125, 0.125,
		 0, 0.125, -0.125,
	};
	
	float borderUV = 0.01f;
	
	static const GLfloat g_uv_buffer_data[] = {
		 1 - borderUV, 0 + borderUV,
		 0 + borderUV, 1 - borderUV,
		 0 + borderUV, 0 + borderUV,
		 1 - borderUV, 0 + borderUV,
		 1 - borderUV, 1 - borderUV,
		 0 + borderUV, 1 - borderUV
	};
	
	unsigned int whiteT = view::loadBMP_custom("white.bmp");
	unsigned int blackT = view::loadBMP_custom("black.bmp");
	
	view::shape* squareS = new view::shape(g_uv_buffer_data, 12, square, 18, 6);
			
	oge::gameObject* bg = oge::createNewGameObject();
	bg->components.push_back(new view::rendererComponent(sh, squareS, whiteT));

	bg->components.push_back(new timer());
	
	oge::gameLoop();
	
}
