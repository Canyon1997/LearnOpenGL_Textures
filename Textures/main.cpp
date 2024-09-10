// Core Libraries
#include <stdio.h>
#include <stdlib.h>

// Personal/External Libraries
#include "OpenGLOperations.h"
#include "Shader.h"
#include "stb_image.h"

int main()
{
	GLFWwindow* window = InitializeOpenGL("Textures");

	Shader brickShader("", "");

	float Triangle1[] = {
		-1.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	float brickTextureCords[] = {
		0.0f, 0.0f, // lower left corner
		1.0f, 0.0f, // lower right corner
		0.5f, 1.0f // top center
	};


	// Initialize texture
	unsigned int woodenTexture;
	glGenTextures(1, &woodenTexture);

	// set texture wrapping/filtering options on currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE, woodenTexture);

	// load texture image
	int width, height, nrChannels;
	unsigned char* woodenTextureData = stbi_load("Textures//TextureResources//woodencontainer.jpg", &width, &height, &nrChannels, 0);
	if (woodenTextureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, woodenTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	
	stbi_image_free(woodenTextureData);

	// initialize VAO & VBO
	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1), Triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render shader
		brickShader.Use();

		//Bind VAO 1
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//Swap color buffer and shows output to screen
		glfwSwapBuffers(window);

		//check if any events triggered
		glfwPollEvents();
	}


	// Clean-up
	glDeleteProgram(brickShader.ID);
	glfwTerminate();

	return 0;
}