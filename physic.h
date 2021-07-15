#pragma once

class physic : public oge::component {
	void update() override;
};

class staticCollider : public physic {
public:
	vector2 size;
	vector2 origin;
	staticCollider();
	void update() override;
};

class dynamicCollider : public physic {
public:
	oge::gameObject* parent;

	vector2 velocity;	
	vector2 size;
	vector2 origin;
	
	dynamicCollider();
	
	void update() override;
};
