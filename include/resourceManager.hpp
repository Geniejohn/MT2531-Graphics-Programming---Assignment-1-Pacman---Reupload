#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include "SOIL.h"
#include "logger.h"

#include "shaderload.h"
#include "constants.h"



class ResourceManager
{

	private:

		GLuint textures[TEXTURE_COUNT];										//Holds the textures for all possible sprites in the game.


		int loadTextureFromFile(char* path, int no)								//Loads a texture form file into video memory.
		{																		//gives error code if fails.
			LOG_DEBUG("Attempting to load texture: %d from file: %s", no, path);
			int width, height;
			unsigned char* image = nullptr;
			float x, y, widthT, heightT;

			// glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[no]);
			image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_AUTO);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);


			glUniform1i(glGetUniformLocation(shaderProgram, "texOne"), 0);		//The last peramiter in the setting of the texture glUniform1i
																				//is that index in the shader it is, and not which of the stored
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//textures. So we can store 500 textures, but if we're only using
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//one texture at a time in the shader, this will always be 0!!
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if(image == nullptr)
			{
				LOG_DEBUG("Failure!! %d from file: %s did not load.", no, path);
				return -1;
			}
			else
			{
				LOG_DEBUG("Done.");
				return 0;
			}

		}

	public:

		GLFWwindow* window;
		GLuint shaderProgram;													//ShaderProgram loaded once, shared between all sprites.

		ResourceManager()
		{

		}

		//Setting up attributes for shaderProgram:
		void loadShaderAttributes()												//Setup shader attribs, is called in setup, and in every sprite's setup.
		{																		//binds the sprite's corrsponding VAO and VBO. Alot of debugging and trouble
			GLint posAttrib = glGetAttribLocation(shaderProgram, "position");	//went in to finding out that this setup had do be done for every VAO-VBO-set.
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

			GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
			glEnableVertexAttribArray(colAttrib);
			glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

			GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
			glEnableVertexAttribArray(texAttrib);
			glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
		}

		int startup()
		{
			if (!glfwInit())													//Start up glfw, will then open window of set size in constatns.h.
			{
				LOG_DEBUG("Failed to initialize GLFW\n");
				getchar();
				return -1;
			}

			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 				// To make MacOS happy; should not be needed
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


			window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pacman", NULL, NULL);
			glfwMakeContextCurrent(window);
			if (window == NULL) {
				LOG_DEBUG("Failed to open GLFW window.\n");
				getchar();
				glfwTerminate();
				return -1;
			}


			glewExperimental = GL_TRUE;
			// Initialize GLEW
			if (glewInit() != GLEW_OK) {										//Initialize GLEW needs be happen before any other GL functions
				LOG_DEBUG("Failed to initialize GLEW\n");						//can be called.
				getchar();
				glfwTerminate();
				return -1;
			}


			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);				//Input method, dictates how keypresses are interprited.
			glfwSwapInterval(1);


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glClearColor(	BACKGROUND_COLOR.x,
							BACKGROUND_COLOR.y,
							BACKGROUND_COLOR.z,
							BACKGROUND_COLOR.w);												//The background color for the window.



			shaderProgram = create_program("vertex.vert", "fragment.frag");		//Create shaderProgram, attribs will be set at end of setup sequence.



			glGenTextures(TEXTURE_COUNT, textures);

			for(int i = 0; i < TEXTURE_COUNT; i++)
			{
				if(loadTextureFromFile(FILES[i], i) != 0)						//If a texture didn't load:
				{
					LOG_DEBUG("A texture number %d failed to load.", i);
					return -1;													//stop, loading, return, then stop the program.
				}
			}

			return 0;															//Everyting is set up correctly.
		}

		void shutdown()
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		GLuint getTexture(Texture textureIndex)
		{
			return textures[textureIndex];
		}

};





















//
