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
		shader(const char * vertex_file_path,const char * fragment_file_path);
		
		void bindShader(unsigned int prog);
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
		shape(const float *uvArr, int uvSize, const float *verArr, int verSize, int stripLength);
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
		
		float* transform;
		
		rendererComponent(shader* prog, shape* sh, unsigned int tex);
		rendererComponent();
		
		std::string toString() override;
		void update() override;
		
		float getX();
		float getY();
		float getZ();
		
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		
		void setPos(float x, float y, float z);
	};
	
	class camera : public oge::component {
	public:
		static float position[3];
		
		std::string toString() override;
		
		static float getX();
		static float getY();
		static float getZ();
		
		static void setX(float x);
		static void setY(float y);
		static void setZ(float z);
		
		static void setPos(float x, float y, float z);
	};
	
	unsigned int LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
	unsigned int loadBMP_custom(const char * imagepath);
}
