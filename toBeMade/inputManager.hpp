#include "pacman.hpp"
#include "constants.h"
#include "GLFW/glfw3.h"
#include "MovableCharacter.hpp"

//extern Pacman

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
			state = glfwGetKey(window, GLFW_KEY_ESCAPE);
			if(state == GLFW_PRESS)
			{
				//Toggle menu
			}
			state = glfwGetKey(window, GLFW_KEY_ENTER);
			if(state == GLFW_PRESS)
			{
				//Menu.enter();
			}
			state = glfwGetKey(window, GLFW_KEY_UP);
			if(state == GLFW_PRESS)
			{
				//UI.up();
			}
			state = glfwGetKey(window, GLFW_KEY_DOWN);
			if(state == GLFW_PRESS)
			{
				//UI.down();
			}

			//Pacman movement:
			state = glfwGetKey(window, GLFW_KEY_W);
			if(state == GLFW_PRESS)
			{
				pacman.MovableCharacter::changeDesiredDir(up);
			}
			state = glfwGetKey(window, GLFW_KEY_A);
			if(state == GLFW_PRESS)
			{
				pacman.MovableCharacter::changeDesiredDir(left);
			}
			state = glfwGetKey(window, GLFW_KEY_S);
			if(state == GLFW_PRESS)
			{
				pacman.MovableCharacter::changeDesiredDir(down);
			}
			state = glfwGetKey(window, GLFW_KEY_D);
			if(state == GLFW_PRESS)
			{
				pacman.MovableCharacter::changeDesiredDir(right);
			}
		}

};