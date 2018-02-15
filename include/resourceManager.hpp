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


		void loadTextureFromFile(char* path, int no)
		{
			LOG_DEBUG("Loaded texture: %d from file: %s", no, path);
			int width, height;
			unsigned char* image;
			float x, y, widthT, heightT;

			glActiveTexture(GL_TEXTURE0 +1);
			glBindTexture(GL_TEXTURE_2D, textures[no]);
			image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_AUTO);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);


			glUniform1i(glGetUniformLocation(shaderProgram, "texOne"), no);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		}

	public:

		GLuint shaderProgram;													//ShaderProgram loaded once, shared between all sprites.

		ResourceManager()
		{

		}

		//Setting up attributes for shaderProgram:
		void loadShaderAttributes()
		{
			GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
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
			shaderProgram = create_program("vertex.vert", "fragment.frag");

		
			glGenTextures(TEXTURE_COUNT, textures);

			for(int i = 0; i < TEXTURE_COUNT; i++)
			{
				loadTextureFromFile(FILES[i], i);
			}

			return 0;
		}

		GLuint getTexture(Texture textureIndex)
		{
			return textures[textureIndex];
		}

};





















//
