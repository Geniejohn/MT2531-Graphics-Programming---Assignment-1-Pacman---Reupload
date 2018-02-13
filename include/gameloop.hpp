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
        GameLoop()
		{
		    running = true;
		    nbFrames = 0;
		    lastTime = glfwGetTime();
			std::cout << "\nGameLoop constructor.";

		}


		// Initialise GLFW window. Returns -1 if failed.
		int startup()
		{
			std::cout << "\n\n\nGameLoop startup.";

			if (!glfwInit())
			{
				std::cout << "\nGameLoop failtest 0a.";

				fprintf(stderr, "Failed to initialize GLFW\n");
				getchar();
				return -1;
			}
			std::cout << "\nGameLoop failtest 0b.";

			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 				// To make MacOS happy; should not be needed
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			std::cout << "\nGameLoop failtest 1.";

			window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pacman", NULL, NULL);
			glfwMakeContextCurrent(window);
			if (window == NULL) {
				fprintf(stderr, "Failed to open GLFW window.\n");
				getchar();
				glfwTerminate();
				return -1;
			}

			std::cout << "\nGameLoop failtest 2.";

			glewExperimental = GL_TRUE;
			// Initialize GLEW
			if (glewInit() != GLEW_OK) {
				fprintf(stderr, "Failed to initialize GLEW\n");
				getchar();
				glfwTerminate();
				return -1;
			}

			std::cout << "\nGameLoop failtest 3.";


			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
			glfwSwapInterval(1);


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glClearColor(1,1,1,1);
			std::cout << "\nGameLoop setup done.\n\n";

			return 0;															//All went well.
		}

        void run()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		    																	// Measure speed:
		    double currentTime = glfwGetTime();
		    if (currentTime - lastTime >= 1.0) { 								// If last prinf() was more than 1sec ago
		                                            							// printf and reset
		        printf("%f ms/frame\n", 1000.0 / double(nbFrames));
		        nbFrames = 0;
		        lastTime += 1.0;
		    }

			//dynamic code//

			glfwSwapBuffers(window);
			glfwPollEvents();
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

        ~GameLoop()
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}
};