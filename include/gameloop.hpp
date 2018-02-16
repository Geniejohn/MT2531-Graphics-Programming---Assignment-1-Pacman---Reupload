#pragma once
#include "glm/glm/glm.hpp"

//#include "spriteAnimated.hpp"
#include "constants.h"
#include "level.hpp"
#include "pacman.hpp"
#include "inputManager.hpp"
#include "ghost.hpp"

extern Level level;
extern InputManager inputManager;
extern Pacman player;
extern Ghost ghosts[];

class GameLoop
{
    private:
      bool running;			//True as long as game is running.


    public:
        GameLoop()
		{
			running = true;
		}


		~GameLoop()
		{

		}


		void makeSprites()
		{
			player = Pacman(478);												//478 Start on the 0x17th tile.
			ghosts[0] = Ghost(113);
			ghosts[1] = Ghost(114);
			ghosts[2] = Ghost(115);
			ghosts[3] = Ghost(116);
		}


        void run()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			inputManager.update();
			player.update();
			ghosts[0].update();
			ghosts[1].update();
			ghosts[2].update();
			ghosts[3].update();
			
			level.draw();
			player.draw();
			ghosts[0].draw();
			ghosts[1].draw();
			ghosts[2].draw();
			ghosts[3].draw();

			glfwSwapBuffers(resourceManager.window);
			glfwPollEvents();

			if(glfwGetKey(resourceManager.window, GLFW_KEY_ESCAPE))								//If user exits:
			{
				endLoop();														//End the gameloop.
			}
		}


 		//Retuns false if game should quit.
        bool getRunning()
		{
		    return running;
		}


		//Closes game at end of current loop.
        void endLoop()
		{
		    running = false;
		}

};
