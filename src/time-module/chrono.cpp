#include <iostream>
#include <functional>
#include "chrono.h"
#include "chronoCl.h"

#include <unistd.h>

namespace oge {
	float currentTime = 0;
	float deltaTime = 0;
	
	void init() { 
		std::cout<<"Starting time module"<<std::endl;
	}
	
	void finish() {
		cancelAllSubscriptions();
		updateQueue();
		std::cout<<"Finishing time module"<<std::endl;
	}
	
	int nextId = 0;
	subscription* subsQueue = NULL;
	
	void updateTime(float deltaTime) {
		currentTime += deltaTime;
		
		subscription* ptr = subsQueue;
		subscription** prev = &subsQueue;
		while(ptr != NULL) {		
			if(ptr->update()) {
				subscription* temp = ptr->next;
				delete ptr;
				ptr = temp;
				*prev = temp;
			}
			else {
				prev = &(ptr->next);
				ptr = ptr->next;
			}
		}
	}
	
	bool removeAll;
	std::vector<int> pidsToRemove;
	
	void cancelSubscription(int id) { pidsToRemove.push_back(id); }
	void cancelAllSubscriptions() {removeAll = true; }
	
	void cancel(int id) {
		subscription* ptr = subsQueue;
		subscription** prev = &subsQueue;
		while(ptr != NULL) {		
			if(ptr->subId == id) {
				subscription* temp = ptr->next;
				delete ptr;
				ptr = temp;
				*prev = temp;
			}
			else {
				prev = &(ptr->next);
				ptr = ptr->next;
			}
		}
	}
	
	void cancelAll() {
		subscription* ptr = subsQueue, *temp;
		while(ptr != NULL) {
			temp = ptr -> next;
			delete ptr;
			ptr = temp;
		}
		
		subsQueue = NULL;
	}
	
	void updateQueue() {
		if(removeAll) {
			cancelAll();
			removeAll = false;
		}
		else {
			for(int i : pidsToRemove) {
				cancel(i);
			}
			
			pidsToRemove = {};
		}
	}
	
	int subscribeTime(float time, std::function<void()> action) {
		nextId++;
		subscription* ns = new timeSubs(subsQueue, nextId, time, action);
		subsQueue = ns;
		return nextId;
	}
	
	int subscribeInterval(float interval, std::function<void()> action) {
		nextId++;
		subscription* ns = new intervalSubs(subsQueue, nextId, interval, action);
		subsQueue = ns;
		return nextId;
	}
	
	int subscribeTimeWithProgress(float time, float* prog, std::function<void()> action) {
		nextId++;
		subscription* ns = new timeSubsProgress(subsQueue, nextId, time, prog, action);
		subsQueue = ns;
		return nextId;
	}
	
	int subscribeIntervalWithProgress(float interval, float* prog, std::function<void()> action) {
		nextId++;
		subscription* ns = new intervalSubsProgress(subsQueue, nextId, interval, prog, action);
		subsQueue = ns;
		return nextId;
	}
}






























