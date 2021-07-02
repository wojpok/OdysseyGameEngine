#pragma once

namespace chr {
	extern float currentTime;
	extern float deltaTime;
	
	void init();
	void finish();
	
	void updateTime(float delta);
	void updateQueue();
	
	// If you are subscribing a time event, don't forget to cancel it when subsriber is removed
	
	int subscribeTime					(float time, 							std::function<void()> action);
	int subscribeInterval				(float interval, 						std::function<void()> action);
	int subscribeTimeWithProgress	 	(float time, 		float* progress, 	std::function<void()> action);
	int subscribeIntervalWithProgress	(float interval, 	float* progress, 	std::function<void()> action);
	
	void cancelSubscription(int id);
	void cancelAllSubscriptions();
}
