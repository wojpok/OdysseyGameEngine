#include "src/odysseyGameEngine.h"

class customComponent : public oge::component {
	std::string toString() override { return "Custom Component"; }

	void update() override {
		std::cout<<"Custom component updated"<<std::endl<<"Current time: "<<chr::currentTime<<std::endl;
	}
	
	void intervalUpdate() override {
	
	}
};

int main() {
	
	oge::gameObject* gm = oge::createNewGameObject();
	gm->components.push_back(new customComponent());
	
	chr::subscribeInterval(2.0, [](){ std::cout<<"This closure will be called every 2 seconds"<<std::endl;});
	
	while(1) {
		usleep(500000);
		
		chr::updateTime(0.5);
		chr::updateQueue();
		
		oge::updateAllGameObjects();
	}
	
}
