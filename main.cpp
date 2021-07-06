#include "src/odysseyGameEngine.h"

#include "src/view-module/viewHidden.h"

class customComponent : public oge::component {
	std::string toString() override { return "Custom Component"; }

	void update() override {
		//std::cout<<"Framerate "<<1/chr::deltaTime<<std::endl;
	}
	
	void intervalUpdate() override {
	
	}
};

int main() {
	view::init();
	
	view::shape* block;
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint billboard_vertex_buffer, billboard_uv_buffer;
	
	static const GLfloat g_vertex_buffer_data[] = {
		 0, -0.5, 0.5,
		 0, 0.5, -0.5,
		 0, -0.5, -0.5,
		 0, -0.5, 0.5,
		 0, 0.5, 0.5,
		 0, 0.5, -0.5,
	};
	
		
	
	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	
	float borderUV = 0.01f;
	
	static const GLfloat g_uv_buffer_data[] = {
		 1 - borderUV, 0 + borderUV,
		 0+ borderUV, 1- borderUV,
		 0+ borderUV, 0+ borderUV,
		 1- borderUV, 0+ borderUV,
		 1- borderUV, 1- borderUV,
		 0+ borderUV, 1- borderUV
	};
	

	
	glGenBuffers(1, &billboard_uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_DYNAMIC_DRAW);

	block = new view::shape(billboard_vertex_buffer, billboard_uv_buffer, 6);
	
	oge::gameObject* gm = oge::createNewGameObject();
	gm->components.push_back(new customComponent());
	
	view::shader *sh = new view::shader();
	sh->program = view::LoadShaders("src/view-module/basicVertex.glsl","src/view-module/basicFragment.glsl");
	
	sh->textureId = glGetUniformLocation(sh->program, "myTextureSampler");
	sh->MVPID = glGetUniformLocation(sh->program, "MVP");
	sh->posId = glGetUniformLocation(sh->program, "offset");
	
	view::rendererComponent *rend = new view::rendererComponent(sh,block, view::loadBMP_custom("atlas2.bmp"));
	(void) rend;
	gm->components.push_back(rend);
	//chr::subscribeInterval(2.0, [](){ std::cout<<"This closure will be called every 2 seconds"<<std::endl;});
	
	double lastTime = glfwGetTime();
	
	double currentTime = glfwGetTime();
		//deltaTime = float(currentTime - lastTime);
	
	int frame = -1;
	
	do {
		
		frame++;
		//std::cout<<frame<<std::endl;
		
		currentTime = glfwGetTime();
		view::clearFrame();
		view::computeMatricesFromInputs();
		//usleep(100000);
		
		chr::updateTime(float(currentTime - lastTime));
		chr::updateQueue();
		
		oge::updateAllGameObjects();
		
		lastTime = currentTime;
		
		view::pushFrame();
	} while(view::isContextOpen());
	
	view::clearContext();
	
}
