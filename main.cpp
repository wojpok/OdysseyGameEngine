
#include "src/view-module/viewHidden.h"
#include "src/odysseyGameEngine.h"
#include "math2D.hpp"
#include "physic.h"

#include <cstring>

static std::vector<physic*> staticColliders = {};
static std::vector<physic*> dynamicColliders = {};

void physic::update() {
	for(physic* pd : dynamicColliders) {
		
	}
}


vector2 gravity(0, -10);

staticCollider::staticCollider() {
	staticColliders.push_back(this);
	origin = vector2(oge::parent->transform[2], oge::parent->transform[1]);
}

void staticCollider::update() {
	origin = vector2(oge::parent->transform[2], oge::parent->transform[1]);
}

	
dynamicCollider::dynamicCollider() {
	parent = NULL;
	dynamicColliders.push_back(this);
	origin = vector2(oge::parent->transform[2], oge::parent->transform[1]);
}

void dynamicCollider::update() {	
	if(parent == NULL) parent = oge::parent;
	
	velocity += gravity * chr::deltaTime;
	vector2 prediction = origin + velocity * chr::deltaTime;
	
	for(physic* ps : staticColliders) {
		staticCollider* sc = dynamic_cast<staticCollider*>(ps);
		
		if(sc == NULL)
			continue;
		
		// left-bottom corners
		vector2 lbC = prediction + originOffset;
		vector2 lbCS = sc->origin + sc->originOffset;
		//std::cout<<lbC<<" "<<lbCS<<" "<<sc->size<<std::endl;
		if(aabbCollisionDetection(lbC, size, lbCS, sc->size)) {
			
			float correctionX = 0 , correctionY;
			
			float collisionOffset = 0.0001;
			
			if(lbC.x > lbCS.x)
				correctionX =  lbCS.x + sc->size.x - lbC.x  + collisionOffset;
			else
				correctionX =  lbCS.x - lbC.x - size.x - collisionOffset;
				
			
			
			if(lbC.y > lbCS.y)
				correctionY =  lbCS.y + sc->size.y - lbC.y  + collisionOffset;
			else
				correctionY =  lbCS.y - lbC.y - size.y - collisionOffset;
			
			if(std::abs(correctionY) < std::abs(correctionX)) {
				prediction.y += correctionY;
				velocity.y = 0;
			}
			else {
				prediction.x += correctionX;
				velocity.x = 0;
			}
		}
	}
	
	oge::parent->transform[1] = prediction.y;
	oge::parent->transform[2] = prediction.x;
	
	origin = prediction;
	
	//std::cout<<origin<<std::endl;
}


class timer : public oge::component {
public:
	dynamicCollider* col = NULL;

	void update() override {
		if(col == NULL) {
			col = oge::parent->getComponent<dynamicCollider>();
			return;
		}
		
		if(glfwGetKey(view::window, GLFW_KEY_S) == GLFW_PRESS) {
			col->velocity.y -= chr::deltaTime*3;
		}
		if(glfwGetKey(view::window, GLFW_KEY_W) == GLFW_PRESS) {
			col->velocity.y = 4;
		}
		
		if(glfwGetKey(view::window, GLFW_KEY_A) == GLFW_PRESS) {
			col->velocity.x -= chr::deltaTime*3;
		}
		if(glfwGetKey(view::window, GLFW_KEY_D) == GLFW_PRESS) {
			col->velocity.x += chr::deltaTime*3;
		}
		
		view::camera::position[2] = (oge::parent->getZ() + 2*view::camera::position[2])/3;
		view::camera::position[1] = (oge::parent->getY() + 2*view::camera::position[1])/3;
	}
};

float* shapeGen(float height, float width) {
	float* square = new float[18];
	float arr[] = {
		 0, -height, width,
		 0, height, -width,
		 0, -height, -width,
		 0, -height, width,
		 0, height, width,
		 0, height, -width,
	};
	
	memcpy(square, arr, 18*sizeof(float));
	
	return square;
}

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
	
	view::shape* squareS = new view::shape(g_uv_buffer_data, 12, shapeGen(0.125, 0.125), 18, 6);
	view::shape* platformS = new view::shape(g_uv_buffer_data, 12, shapeGen(0.125, 1), 18, 6);
	
	
	// ==========================================================
	oge::gameObject* bg = oge::createNewGameObject();
	bg->components.push_back(new view::rendererComponent(sh, squareS, whiteT));

	dynamicCollider* col = new dynamicCollider();
	col->velocity = vector2(0, -1);
	col->size = vector2(0.25, 0.25);
	col->originOffset = vector2(-0.125, -0.125);
	
	bg->components.push_back(new timer());
	bg->components.push_back(col);
	
	// ==========================================================
	for(int i = 0; i < 10; i++) {
		oge::gameObject* bg2 = oge::createNewGameObject();
		bg2->components.push_back(new view::rendererComponent(sh, platformS, whiteT));
		
		bg2->setPos(0, 2*i - 2, 3*i);
		
		staticCollider* col2 = new staticCollider();
		col2->size = vector2(2, 0.25);
		col2->originOffset = vector2(-1, -0.125);
		
		bg2->components.push_back(col2);
	}
	// ==========================================================
	oge::gameObject* physicEngine = oge::createNewGameObject();
	physicEngine->components.push_back(new physic());
	
	oge::gameLoop();
	
}
