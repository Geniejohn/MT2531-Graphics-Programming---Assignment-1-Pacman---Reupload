#pragma once
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <cstdlib>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "constants.h"


class GameLoop
{
    private:
      bool running;			//True as long as game is running.
      int nbFrames;
      double lastTime;

	  GLFWwindow* window;

    public:
        GameLoop();
		int startup();              // Initialise GLFW window. Returns -1 if failed.

        void run();

        bool getRunning();  //Retuns false if game should quit.

        void endLoop();     //Closes game at end of current loop.

        ~GameLoop();
};
