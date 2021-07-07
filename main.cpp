#include "src/odysseyGameEngine.h"

#include "src/view-module/viewHidden.h"

float playerSpeed = 2;

class playerLeft : public oge::component {
	std::string toString() override { return "Player Left Component"; }
public:
	view::rendererComponent* rend;
	
	playerLeft() { rend = NULL; }
	
	void update() override {
		if(rend == NULL) {
			rend = oge::parent->getComponent<view::rendererComponent>();
			return;
		}
		
		rend->setZ(-3.5);
		
		if (glfwGetKey( view::window, GLFW_KEY_W ) == GLFW_PRESS){
			rend->setY(rend->getY() + 2*chr::deltaTime);
		}
		if (glfwGetKey( view::window, GLFW_KEY_S ) == GLFW_PRESS){
			rend->setY(rend->getY() - 2*chr::deltaTime);
		}
		
		if(rend->getY() > 1.5) rend->setY(1.5);
		if(rend->getY() < -1.5) rend->setY(-1.5);
	}
};

class playerRight : public oge::component {
	std::string toString() override { return "Player Right Component"; }
public:
	view::rendererComponent* rend;
	
	playerRight() { rend = NULL; }
	
	void update() override {
		if(rend == NULL) {
			rend = oge::parent->getComponent<view::rendererComponent>();
			return;
		}
		
		rend->setZ(3.5);
		
		if (glfwGetKey( view::window, GLFW_KEY_UP ) == GLFW_PRESS){
			rend->setY(rend->getY() + 2*chr::deltaTime);
		}
		if (glfwGetKey( view::window, GLFW_KEY_DOWN ) == GLFW_PRESS){
			rend->setY(rend->getY() - 2*chr::deltaTime);
		}
		
		if(rend->getY() > 1.5) rend->setY(1.5);
		if(rend->getY() < -1.5) rend->setY(-1.5);
	}
};

oge::gameObject *pl, *pr;

class ball : public oge::component {
	std::string toString() override { return "Ball Component"; }
	
	float velocityY;
	float velocityZ;
	
	view::rendererComponent *rend, *rendR, *rendL;
	
public:

	ball() {
		rend = rendR = rendL = NULL;
		velocityY = velocityZ = 0;
		chr::subscribeTime(1, [&](){ velocityY = 1; velocityZ = 1; });
	}
	
	void update() override {
		if(rend == NULL || rendL == NULL || rendR == NULL) {
			rend = oge::parent->getComponent<view::rendererComponent>();
			rendL = pl->getComponent<view::rendererComponent>();
			rendR = pr->getComponent<view::rendererComponent>();
			rend->setPos(0,0,0);
			return;
		}
		
		rend->setZ(rend->getZ() + velocityZ * chr::deltaTime);
		rend->setY(rend->getY() + velocityY * chr::deltaTime);
		
		if(rend->getZ() < -3.25) {
			float p = rendL->getY();
			if(p + 0.5  > rend->getY() && p - 0.5  < rend->getY()) 
				velocityZ = -1.2*velocityZ;
			else {
				velocityY = velocityZ = 0;
				rend->setPos(0,0,0);
				chr::subscribeTime(1, [&](){ velocityY = 1; velocityZ = 1; });
			} 
		}
		if(rend->getZ() >  3.25) { 
			float p = rendR->getY();
			if(p + 0.5  > rend->getY() && p - 0.5  < rend->getY()) 
				velocityZ = -1.2*velocityZ;
			else {
				velocityY = velocityZ = 0;
				rend->setPos(0,0,0);
				chr::subscribeTime(1, [&](){ velocityY = -1; velocityZ = -1; });
			} 
		}
		
		if(rend->getY() >  1.875) { velocityY = -1.05*velocityY; }
		if(rend->getY() < -1.875) { velocityY = -1.05*velocityY; }
	}
};

int main() {
	view::init();
	
	view::shader *sh = new view::shader("src/view-module/basicVertex.glsl","src/view-module/basicFragment.glsl");
	
	static const GLfloat square[] = {
		 0, -0.125, 0.125,
		 0, 0.125, -0.125,
		 0, -0.125, -0.125,
		 0, -0.125, 0.125,
		 0, 0.125, 0.125,
		 0, 0.125, -0.125,
	};
	
	static const GLfloat background[] = {
		 1, -10, 10,
		 1, 10, -10,
		 1, -10, -10,
		 1, -10, 10,
		 1, 10, 10,
		 1, 10, -10,
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
			
	pl = oge::createNewGameObject();
	pl->components.push_back(new view::rendererComponent(sh, playerS, whiteT));
	pl->components.push_back(new playerLeft());
	
	pr = oge::createNewGameObject();
	pr->components.push_back(new view::rendererComponent(sh, playerS, whiteT));
	pr->components.push_back(new playerRight());
	
	oge::gameObject* bg = oge::createNewGameObject();
	bg->components.push_back(new view::rendererComponent(sh, bgS, blackT));
	
	oge::gameObject* bll = oge::createNewGameObject();
	bll->components.push_back(new view::rendererComponent(sh, squareS, whiteT));
	bll->components.push_back(new ball());
	
	
	oge::gameLoop();
	
}
