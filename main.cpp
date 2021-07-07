#include "src/odysseyGameEngine.h"

#include "src/view-module/viewHidden.h"

class customComponent : public oge::component {
	std::string toString() override { return "Custom Component"; }
public:
	view::rendererComponent* rend;
	
	customComponent() { rend = NULL; }
	
	void update() override {
		if(rend == NULL) {
			rend = oge::parent->getComponent<view::rendererComponent>();
		}
		else {
			if (glfwGetKey( view::window, GLFW_KEY_UP ) == GLFW_PRESS){
				rend->setY(rend->getY() + chr::deltaTime);
			}
			
			if (glfwGetKey( view::window, GLFW_KEY_DOWN ) == GLFW_PRESS){
				rend->setY(rend->getY() - chr::deltaTime);
			}
			
			if (glfwGetKey( view::window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
				rend->setZ(rend->getZ() + chr::deltaTime);
			}
			
			if (glfwGetKey( view::window, GLFW_KEY_LEFT ) == GLFW_PRESS){
				rend->setZ(rend->getZ() - chr::deltaTime);
			}
		}
	}
	
	void intervalUpdate() override {
	
	}
};

int main() {
	view::init();
	
	static const GLfloat g_vertex_buffer_data[] = {
		 0, -0.5, 0.5,
		 0, 0.5, -0.5,
		 0, -0.5, -0.5,
		 0, -0.5, 0.5,
		 0, 0.5, 0.5,
		 0, 0.5, -0.5,
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

	view::shape* block = new view::shape(g_uv_buffer_data, 12, g_vertex_buffer_data, 18, 6);
			
	oge::gameObject* gm = oge::createNewGameObject();
	gm->components.push_back(new customComponent());
	
	view::shader *sh = new view::shader("src/view-module/basicVertex.glsl","src/view-module/basicFragment.glsl");
	
	view::rendererComponent *rend = new view::rendererComponent(sh,block, view::loadBMP_custom("atlas2.bmp"));
	(void) rend;
	gm->components.push_back(rend);
	
	double lastTime = glfwGetTime();
	
	double currentTime = glfwGetTime();
	
	int frame = -1;
	
	chr::subscribeTime(15.0f, [](){ std::cout<<"Thanks for playing this 15-second demo" <<std::endl; exit(0); });
	
	
	do {	
		currentTime = glfwGetTime();
		view::clearFrame();
		view::computeMatricesFromInputs();
		
		chr::updateTime(float(currentTime - lastTime));
		chr::updateQueue();
		
		oge::updateAllGameObjects();
		
		lastTime = currentTime;
		
		view::pushFrame();
	} while(view::isContextOpen());
	
	view::clearContext();
	
}
