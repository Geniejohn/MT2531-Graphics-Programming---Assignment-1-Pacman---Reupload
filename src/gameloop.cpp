#include "gameloop.h"

// Initialise GLFW window. Returns -1 if failed.
int GameLoop::startup()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pacman", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glewExperimental = GL_TRUE;
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}


	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSwapInterval(1);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(1,1,1,1);
}




GameLoop::GameLoop()
{
    running = true;
    nbFrames = 0;
    lastTime = glfwGetTime();

}

void GameLoop::run()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Measure speed
    double currentTime = glfwGetTime();
    if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
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
bool GameLoop::getRunning()
{
    return running;
}

//Closes game at end of current loop.
void GameLoop::endLoop()
{
    running = false;
}

//Close application window
GameLoop::~GameLoop()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
