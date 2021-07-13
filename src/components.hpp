#pragma once

namespace oge {
	class component {
	public:
		virtual std::string toString() { return "Empty component"; }
		
		virtual void update() {}
		virtual void intervalUpdate() {}
	
	};
	
	class helloWorldComponent : public component {
	public:
		std::string toString() override { return "Hello World component"; }
		
		void update() override { std::cout<<"Hello World updated"<<std::endl; }
		void intervalUpdate() override { std::cout<<"Hello World updated"<<std::endl; }
	};
	
	class gameObject {
	public:
		int goId;
		std::vector<component*> components;
		float* transform;
		
		gameObject(int id) : goId(id), components({}) {
			transform = new float[4];
			
			for (int i = 0; i < 4; i++) {
				transform[i] = 0.0;
			}
		}
		
		void update() {
			for(component* v : components) {
				v->update();
			}
		}
		
		void intervalUpdate() {
			for(component* v : components) {
				v->intervalUpdate();
			}
		}
		
		template<class T>
		T* getComponent() {
			T* toRet;
			for(component* comp : components) {
				if(toRet = dynamic_cast<T*>(comp))
					return toRet;
			}
			return NULL;
		}
		
		template<class T>
		std::vector<T*> getComponents() {
			std::vector<T*> toRet;
			T* temp;
			for(component* comp : components) {
				if(temp = dynamic_cast<T*>(comp))
					toRet.push_back(temp);
			}
			return toRet;
		}
		
		float getX() { return transform[0]; }
		float getY() { return transform[1]; }
		float getZ() { return transform[2]; }
		
		void setX(float x) { transform[0] = x; }
		void setY(float y) { transform[1] = y; }
		void setZ(float z) { transform[2] = z; }
		
		void setPos(float x, float y, float z) {
			transform[0] = x;
			transform[1] = y;
			transform[2] = z;
		}
		
		void setAngle(float ang) { transform[3] = ang; }
		float getAngle() { return transform[3]; }
	};
}
