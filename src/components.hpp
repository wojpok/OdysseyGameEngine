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
		
		gameObject(int id) : goId(id), components({}) {}
		
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
	};
}
