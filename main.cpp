#include "src/odysseyGameEngine.h"

#include "src/view-module/viewHidden.h"

class customComponent : public oge::component {
	std::string toString() override { return "Custom Component"; }

	void update() override {
		std::cout<<"Custom component updated"<<std::endl<<"Current time: "<<chr::currentTime<<std::endl;
	}
	
	void intervalUpdate() override {
	
	}
};

int main() {
	
	view::init();
	
	oge::gameObject* gm = oge::createNewGameObject();
	gm->components.push_back(new customComponent());
	
	chr::subscribeInterval(2.0, [](){ std::cout<<"This closure will be called every 2 seconds"<<std::endl;});
	
	do {
		view::clearFrame();
		usleep(100000);
		
		chr::updateTime(0.1);
		chr::updateQueue();
		
		oge::updateAllGameObjects();
		
		view::pushFrame();
	} while(view::isContextOpen());
	
	view::clearContext();
	
}
