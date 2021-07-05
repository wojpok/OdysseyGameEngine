#include <iostream>
#include <vector>

#include "../components.hpp"
#include "odyssey.h"
#include "../view-module/viewHidden.h"

namespace oge {
	gameObject* parent = NULL;
	std::vector<gameObject*> objects = {};
	int uniqueId = 0;
	
	gameObject* createNewGameObject() {
		uniqueId++;
		gameObject* ptr = new gameObject(uniqueId);
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
