#pragma once

namespace view {
	
	extern int windowHeight;
	extern int windowWidth;
	
	void refreshFuncSet(void (*ptr)());
	
	class shader {
	public:	
		unsigned int program;
		unsigned int MVPID;
		unsigned int posId;
		unsigned int time;
		unsigned int textureId;
		
		shader();
	
		void useProgram();
		void bindTexture(unsigned int tex);
		virtual void bindMVP();
		void bindPos(float pos[16]);
	};
	
	// shape class - provides buffers with mesh UVs and Vertices
	class shape {
	private:
		unsigned int vertexBuffer;
		unsigned int uvBuffer;
		int bufferSize;	
		
	public:
		shape(unsigned int vb, unsigned int ub, int bs);
		void draw();
		void drawInstantiated(int count);
		~shape();
	};
	
	
	class rendererComponent : public oge::component {
	public:
		shader* program;
		shape*  mesh;
		unsigned int texture;
		
		rendererComponent(shader* prog, shape* sh, unsigned int tex);
		rendererComponent();
		
		std::string toString() override;
		void update() override;
	
	};
	
	unsigned int LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
	unsigned int loadBMP_custom(const char * imagepath);
}
