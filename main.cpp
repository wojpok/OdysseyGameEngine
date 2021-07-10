#include "src/odysseyGameEngine.h"

#include "src/view-module/viewHidden.h"

float playerSpeed = 2;
view::shader *sh2;

class timer : public oge::component {
	std::string toString() override { return "Player Left Component"; }
public:
	view::rendererComponent* rend;
	
	float x, y;
	
	timer() { x = y = 0; }
	
	void update() override {
		//sh2->customValues[0] = chr::currentTime;
		
		if (glfwGetKey(view::window, GLFW_KEY_W ) == GLFW_PRESS){
			x += 0.1 * chr::deltaTime;
		}
		
		if (glfwGetKey(view::window, GLFW_KEY_S ) == GLFW_PRESS){
			x -= 0.1 * chr::deltaTime;
		}
		
		if (glfwGetKey(view::window, GLFW_KEY_A ) == GLFW_PRESS){
			y -= 0.1 * chr::deltaTime;
		}
		
		if (glfwGetKey(view::window, GLFW_KEY_D ) == GLFW_PRESS){
			y += 0.1 * chr::deltaTime;
		}
		
		sh2->customValues[0] = 0.7*cos(0.05*chr::currentTime);
		sh2->customValues[1] = 0.5*sin(0.05*chr::currentTime);
	}
};

int main() {
	view::init();
	
	view::shader *sh = new view::shader("src/view-module/basicVertex.glsl","src/view-module/basicFragment.glsl");
	sh2 = new view::shader("src/view-module/basicVertex.glsl","src/view-module/mandFragment.glsl");
	
	static const GLfloat square[] = {
		 0, -0.125, 0.125,
		 0, 0.125, -0.125,
		 0, -0.125, -0.125,
		 0, -0.125, 0.125,
		 0, 0.125, 0.125,
		 0, 0.125, -0.125,
	};
	
	static const GLfloat background[] = {
		 1, -3.5, 3.5,
		 1, 3.5, -3.5,
		 1, -3.5, -3.5,
		 1, -3.5, 3.5,
		 1, 3.5, 3.5,
		 1, 3.5, -3.5,
	};
	
	static const GLfloat player[] = {
		 0, -0.5, 0.125,
		 0, 0.5, -0.125,
		 0, -0.5, -0.125,
		 0, -0.5, 0.125,
		 0, 0.5, 0.125,
		 0, 0.5, -0.125,
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
	view::shape* bgS = new view::shape(g_uv_buffer_data, 12, background, 18, 6);
	view::shape* playerS = new view::shape(g_uv_buffer_data, 12, player, 18, 6);
			
	oge::gameObject* bg = oge::createNewGameObject();
	bg->components.push_back(new view::rendererComponent(sh2, bgS, blackT));
	bg->components.push_back(new timer());
	sh2->findUniform("offX", 0);
	sh2->findUniform("offY", 1);

	
	oge::gameLoop();
	
}
