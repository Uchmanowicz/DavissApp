#pragma once

#include <memory>
#include <vector>
#include <functional>

namespace Templates
{
	template<typename Interface>
	class Publisher
	{
	protected:
		std::vector<std::weak_ptr<Interface>> listeners;

	public:
		//	template <typename Interface>
		void addListener(const std::weak_ptr<Interface> &listener)
		{
			if(listener.expired()) {
				return;
			}

			for(auto it = listeners.begin(); it != listeners.end(); ++it) {
				if(it->lock().get() == listener.lock().get()) {
					return;
				}
			}

			listeners.push_back(listener);
		}

		//	template <typename Interface>
		void removeListener(const std::weak_ptr<Interface> &listener)
		{
			for(auto it = listeners.begin(); it != listeners.end(); ++it) {
				if(it->lock().get() == listener.lock().get()) {
					listeners.erase(it);
					return;
				}
			}
		}
	};
}
