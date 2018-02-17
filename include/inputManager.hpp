#pragma once
#include "pacman.hpp"
#include "constants.h"
#include "GLFW/glfw3.h"
#include "movableCharacter.hpp"
#include "resourceManager.hpp"

extern Pacman player;

//Each space in the map except for the walls are tiles:
class InputManager
{
	private:
		int state;

	public:
		//Constructor:
		InputManager()
		{

		}


		//Deconstructor:
		~InputManager()
		{

		}

		void update()
		{
			state = glfwGetKey(resourceManager.window, GLFW_KEY_ESCAPE);
			if(state == GLFW_PRESS)
			{
				//Toggle menu
			}
			state = glfwGetKey(resourceManager.window, GLFW_KEY_ENTER);
			if(state == GLFW_PRESS)
			{
				//Menu.enter();
			}
			state = glfwGetKey(resourceManager.window, GLFW_KEY_UP);
			if(state == GLFW_PRESS)
			{
				//UI.up();
			}
			state = glfwGetKey(resourceManager.window, GLFW_KEY_DOWN);
			if(state == GLFW_PRESS)
			{
				//UI.down();
			}

			//Pacman movement:
			state = glfwGetKey(resourceManager.window, GLFW_KEY_W);
			if(state == GLFW_PRESS)
			{
				LOG_DEBUG("UP!");
				player.MovableCharacter::changeDesiredDir(up);
			}
			state = glfwGetKey(resourceManager.window, GLFW_KEY_A);
			if(state == GLFW_PRESS)
			{
				LOG_DEBUG("LEFT!");
				player.MovableCharacter::changeDesiredDir(left);
			}
			state = glfwGetKey(resourceManager.window, GLFW_KEY_S);
			if(state == GLFW_PRESS)
			{
				LOG_DEBUG("DOWN!")
				player.MovableCharacter::changeDesiredDir(down);
			}
			state = glfwGetKey(resourceManager.window, GLFW_KEY_D);
			if(state == GLFW_PRESS)
			{
				LOG_DEBUG("RIGHT!");
				player.MovableCharacter::changeDesiredDir(right);
			}
			state = glfwGetKey(resourceManager.window, GLFW_KEY_ESCAPE)//If user exits:
			if(state == GLFW_PRESS)
			{
				LOG_DEBUG("The user pressed ESC, time to exit game.");
				gameLoop.endLoop();														//End the gameloop.
			}
		}

};
