
#include "src/view-module/viewHidden.h"
#include "src/odysseyGameEngine.h"
#include "math2D.hpp"
#include "physic.h"

static std::vector<physic*> staticColliders = {};
static std::vector<physic*> dynamicColliders = {};

void physic::update() {
	for(physic* pd : dynamicColliders) {
		for(physic* ps : staticColliders) {
			
			dynamicCollider* dc = dynamic_cast<dynamicCollider*>(pd);
			staticCollider* sc = dynamic_cast<staticCollider*>(ps);
			
			if(dc == NULL || sc == NULL)
				return;
			
		}
	}
}


vector2 gravity(0, -3);

staticCollider::staticCollider() {
	staticColliders.push_back(this);
}

void staticCollider::update() {
	origin = vector2(oge::parent->transform[1], oge::parent->transform[2]);
}

	
dynamicCollider::dynamicCollider() {
	dynamicColliders.push_back(this);
}

void dynamicCollider::update() {	
	
	velocity += gravity * chr::deltaTime;
	
	oge::parent->transform[1] += velocity.y * chr::deltaTime;
	oge::parent->transform[2] += velocity.x * chr::deltaTime;
	
	origin = vector2(oge::parent->transform[1], oge::parent->transform[2]);
}


class timer : public oge::component {
public:
	dynamicCollider* col = NULL;
	
	void update() override {
		if(col == NULL) {
			col = oge::parent->getComponent<dynamicCollider>();
			return;
		}
		
		if(glfwGetKey(view::window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			col->velocity = vector2(0, 3);
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
	// ==========================================================
	oge::gameObject* bg = oge::createNewGameObject();
	bg->components.push_back(new view::rendererComponent(sh, squareS, whiteT));

	dynamicCollider* col = new dynamicCollider();
	col->velocity = vector2(0, 3);
	col->size = vector2(0.125, 0.125);
	
	bg->components.push_back(new timer());
	bg->components.push_back(col);
	
	// ==========================================================
	oge::gameObject* bg2 = oge::createNewGameObject();
	bg2->components.push_back(new view::rendererComponent(sh, squareS, whiteT));
	
	bg2->setPos(0, -1, 0);
	
	staticCollider* col2 = new staticCollider();
	col2->size = vector2(0.125, 0.125);
	
	bg2->components.push_back(col2);
	// ==========================================================
	oge::gameObject* physicEngine = oge::createNewGameObject();
	physicEngine->components.push_back(new physic());
	
	
	oge::gameLoop();
	
}
