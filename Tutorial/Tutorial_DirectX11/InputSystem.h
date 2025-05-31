#pragma once
#include "InputListener.h"
#include "Point.h"
#include <map>
#include <unordered_set>

class InputSystem
	{
	public:
		InputSystem();
		~InputSystem();

		void update();
		void addListener(InputListener* listener);
		void removeListener(InputListener* listener);

	public:
		static InputSystem* get();

	private:
		std::map<InputListener*, InputListener*> m_map_listeners;
		//std::unordered_set<InputListener*> m_set_listeners;
		unsigned char m_keys_state[256] = {};
		unsigned char m_old_keys_state[256] = {};
		Point m_old_mouse_pos;
		bool m_first_time = true;
};

