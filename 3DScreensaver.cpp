// 3DScreensaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <GLFW/glfw3.h>
#include "utility.hpp"

float x = 0.0f, y = 0.0f;

void drawColorWheel() {
	float x = 0.0f, y = 0.0f;
	float r = 0.0f, g = 0.0f, b = 0.0f;
	float circum = 0.01745329252f;
	float radius = 0.2f;
	float k = 0.01666666666f;
	
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(r, g, b);
		glVertex3f(x, y, 0.0f);
		r = 1.0f;
		for (int i = 0; i < 360; i++) {
			if (i < 60) {
				b += k;
			}
			else if (i < 120) {
				r -= k;
			}
			else if (i < 180) {
				g += k;
			}
			else if (i < 240) {
				b -= k;
			}
			else if (i < 300) {
				r += k;
			}
			else if (i < 360) {
				g -= k;
			}
			glColor3f(r, g, b);
			glVertex3f(radius * sin(i * circum), radius * cos(i * circum), 0.0f);
		}
		g -= k;
		glColor3f(r, g, b);
		glVertex3f(radius * sin(0.0f), radius * cos(0.0f), 0.0f);
	glEnd();
	
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W || key == GLFW_KEY_UP) {
		switch (action)
		{
		case GLFW_PRESS:
			y = (y >= 0.8f) ? y : y + 0.1f;
			break;
		case GLFW_REPEAT:
			y = (y >= 0.8f) ? y : y + 0.1f;
			break;
		case GLFW_RELEASE:
			break;
		default:
			break;
		}
	}
	if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN) {
		switch (action)
		{
		case GLFW_PRESS:
			y = (y <= -0.8f) ? y : y - 0.1f;
			break;
		case GLFW_REPEAT:
			y = (y <= -0.8f) ? y : y - 0.1f;
			break;
		case GLFW_RELEASE:
			break;
		default:
			break;
		}
	}
	if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT) {
		switch (action)
		{
		case GLFW_PRESS:
			x = (x <= -0.8f) ? x : x - 0.1f;
			break;
		case GLFW_REPEAT:
			x = (x <= -0.8f) ? x : x - 0.1f;
			break;
		case GLFW_RELEASE:
			break;
		default:
			break;
		}
	}
	if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) {
		switch (action)
		{
		case GLFW_PRESS:
			x = (x >= 0.8f) ? x : x + 0.1f;
			break;
		case GLFW_REPEAT:
			x = (x >= 0.8f) ? x : x + 0.1f;
			break;
		case GLFW_RELEASE:
			break;
		default:
			break;
		}
	}

	if (key == GLFW_KEY_ESCAPE) {
		switch (action)
		{
		case GLFW_PRESS:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_REPEAT:
			break;
		case GLFW_RELEASE:
			break;
		default:
			break;
		}
		
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	REQUIRED(glfwInit());
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "3D Screensaver", glfwGetPrimaryMonitor(), NULL);
	REQUIRED(window);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	float angle = 0.0f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

		glPushMatrix();
			glTranslatef(x, y, 0.0f);
			glPushMatrix();
				glRotatef(angle, 0.0f, 0.0f, 1.0f);
				drawColorWheel();
			glPopMatrix();
		glPopMatrix();

		angle = (angle == 360.0f)? 0.0f : angle + 5.0f;
		//std::cout << angle << std::endl;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}