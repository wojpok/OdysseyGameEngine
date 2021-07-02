#pragma once

namespace oge {
	class subscription {
	public:
		subscription* next;
		int subId;
		subscription(subscription* n, int id) : next(n), subId(id) {}
		virtual bool update() { return false; }
	};
	
	class timeSubs : public subscription {
	public:
		std::function<void()> action;
		float expirationTime;
		
		timeSubs(subscription* n, int id, float time, std::function<void()> foo) 
			: subscription(n, id), expirationTime(time + currentTime), action(foo) {
		}
		
		bool update() override { 
			if (expirationTime < currentTime) {
				action();
				return true;
			}
			return false;	
		}
	};
	
	class timeSubsProgress : public subscription {
	public:
		std::function<void()> action;
		float expirationTime, beginning;
		float* progress;
		
		timeSubsProgress(subscription* n, int id, float time, float* prog, std::function<void()> foo) 
			: subscription(n, id), expirationTime(time + currentTime), action(foo), progress(prog), beginning(currentTime) {
		}
		
		bool update() override {
			*progress = (currentTime - beginning)/(expirationTime - beginning); 
			if (expirationTime < currentTime) {
				*progress = 1;
				action();
				return true;
			}
			return false;	
		}
	};
	
	class intervalSubs : public subscription {
	public:
		std::function<void()> action;
		float interval;
		float nextInterval;
		
		intervalSubs(subscription* n, int id, float inter, std::function<void()> foo) 
			: subscription(n, id), nextInterval(inter + currentTime), interval(inter), action(foo) {}
		
		bool update() override{ 
			if (nextInterval < currentTime) {
				nextInterval += interval;
				action();
			}
			return false;
		}	
	};
	
	class intervalSubsProgress : public subscription {
	public:
		std::function<void()> action;
		float interval;
		float nextInterval, beginning;
		float* progress;
		
		intervalSubsProgress(subscription* n, int id, float inter, float* prog, std::function<void()> foo) 
			: subscription(n, id), nextInterval(inter + currentTime), interval(inter), action(foo), beginning(currentTime), 
			progress(prog) {}
		
		bool update() override{ 
			if (nextInterval < currentTime) {
				beginning = nextInterval;
				nextInterval += interval;
				action();
			}
			
			*progress = (currentTime - beginning)/(nextInterval - beginning); 
			return false;
		}	
	};
}
