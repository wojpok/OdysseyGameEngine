#pragma once

namespace oge {
	
	gameObject* createNewGameObject();
	gameObject* findGameObject(int goId);
	void removeGameObject(int goId);
	
	extern std::vector<gameObject*> objects;
	void updateAllGameObjects();
	void updateIntervalAllGameObjects();
	
	extern gameObject* parent;
	
}
