#include <iostream>
#include <vector>

#include "../components.hpp"
#include "../odysseyGameEngine.h"
//#include "odyssey.h"
#include "../view-module/viewHidden.h"

namespace oge {
	void gameLoop() {
		double lastTime = glfwGetTime();
	
		double currentTime = glfwGetTime();
		
		int frame = -1;
		
		
		do {	
			currentTime = glfwGetTime();
			view::clearFrame();
			view::computeMatricesFromInputs();
			
			chr::updateTime(float(currentTime - lastTime));
			chr::updateQueue();
			
			updateAllGameObjects();
			
			lastTime = currentTime;
			
			view::pushFrame();
		} while(view::isContextOpen());
		
		view::clearContext();
	}
	
	
	gameObject* parent = NULL;
	std::vector<gameObject*> objects = {};
	int uniqueId = 0;
	
	gameObject* createNewGameObject() {
		uniqueId++;
		gameObject* ptr = new gameObject(uniqueId);
		parent = ptr;
		objects.push_back(ptr);
		return ptr;
	}
	
	gameObject* findGameObject(int goId) {
		for(gameObject* v : objects) {
			if(v->goId == goId)
				return v;
		}
		return NULL;
	}
	
	void removeGameObject(int goId) {
		int i = 0;
		for(gameObject* v : objects) {
			if(v->goId == goId) {
				objects.erase(objects.begin()+i);
				return;
			}
			i++;
		}
		return;
	}

	void updateAllGameObjects() {
		for(gameObject* v : objects) {
			parent = v;
			v->update();
		}
	}
	
	void updateIntervalAllGameObjects() {
		for(gameObject* v : objects) {
			parent = v;
			v->intervalUpdate();
		}
	}
}
