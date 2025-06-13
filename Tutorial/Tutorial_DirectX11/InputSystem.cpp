#include "InputSystem.h"
#include <Windows.h>


InputSystem* InputSystem::m_input_system = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	InputSystem::m_input_system = nullptr;
}

void InputSystem::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);
	if (m_first_time) 
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y) 
	{
		//MOUSE MOVE
		std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

		while (it != m_map_listeners.end()) {
			it->second->OnMouseMove(Point(current_mouse_pos.x - m_old_mouse_pos.m_x, current_mouse_pos.y - m_old_mouse_pos.m_y));
			++it;
		}
	}

	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);


	if (::GetKeyboardState(m_keys_state)) 
	{
		for (unsigned int i = 0; i < 256; i++) 
		{
			//KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();
					
				while (it != m_map_listeners.end()) {

					if (i == VK_LBUTTON) {
						if (m_keys_state[i] != m_old_keys_state[i]) {
							it->second->OnLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
					}
					else if (i == VK_RBUTTON) {
						if (m_keys_state[i] != m_old_keys_state[i]) {
							it->second->OnRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
					}
					else {
						it->second->OnKeyDown(i);
						
					}

					++it;
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i]) 
				{
					std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.begin();

					while (it != m_map_listeners.end()) {

						if (i == VK_LBUTTON) {
							it->second->OnLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
							
						}
						else if (i == VK_RBUTTON) {
							it->second->OnRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
							
						}
						else {
							it->second->OnKeyUp(i);
						
						}

						++it;
					}

				}

			}

		}

		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_map_listeners.insert(std::make_pair<InputListener*, InputListener*>(std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)
						  ));
}

void InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.find(listener);

	if (it != m_map_listeners.end()) {
		m_map_listeners.erase(it);
	}
}


InputSystem* InputSystem::get()
{
	return m_input_system;
}

void InputSystem::create()
{
	if (InputSystem::m_input_system) throw std::exception("Input System already created.");

	InputSystem::m_input_system = new InputSystem();
}

void InputSystem::release()
{
	if (!InputSystem::m_input_system) return;
	delete InputSystem::m_input_system;
}
