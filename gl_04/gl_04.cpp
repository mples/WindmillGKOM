#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "WallsModel.h"
#include "TurbineModel.h"
#include "RoofModel.h"
#include "Quern.h"
#include "SkyBox.h"
#include "BoxModel.h"
#include "Lamp.h"

using namespace std;

const GLuint WIDTH = 1600, HEIGHT = 900;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
int turbineSpeed = 1;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 lightPoss(0.0f, 0.0f, 0.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		++turbineSpeed;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		--turbineSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 04", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window, mouse_callback);

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;
		
		glEnable(GL_DEPTH_TEST);

		// Build, compile and link shader program
		ShaderProgram theProgram("gl_04.vert", "gl_04.frag");

		WallsModel walls1(1.0f, glm::vec3(0.9f, 0.9f, 0.9f));
		WallsModel walls3(1.0f, glm::vec3(0.9f, 0.9f, 0.9f));

		TurbineModel turbine(1.0f, glm::vec3(0.56f, 0.27f, 0.19f),  1.0f);

		RoofModel roofTop(1.0f, glm::vec3(0.56f, 0.27f, 0.19f));

		Quern quernTop(0.5f, glm::vec3(0.5f, 0.5f, 0.5f));
		Quern quernBottom(0.5f, glm::vec3(0.5f, 0.5f, 0.5f));

		BoxModel floor(0.95f, 0.05f, 0.95f, glm::vec3(0.0f, -1.45f, 0.0f), 1.0f, glm::vec3(0.56f, 0.27f, 0.19f), 1.0f);

		BoxModel door(0.3f,0.7f,0.1f,glm::vec3(0.0f, 0.0f, -0.475f),1.0f,glm::vec3(0.3f,0.3f,0.3f),1.0f);

		BoxModel desk(0.05f, 1.4f, 0.05f, glm::vec3(0.0f, -0.7f, 0.0f), 1.0f, glm::vec3(0.56f, 0.27f, 0.19f), 1.0f);

		BoxModel ground(50.0f, 0.05f, 50.0f, glm::vec3(0.0f, -1.5f, 0.0f), 1.0f, glm::vec3(0.0f, 0.3f, 0.0f), 50.0f);

		Lamp lamp(0.15f, 0.15f, 0.15f, lightPoss, 1.0f, lightColor, 1.0f);
	
		SkyBox skyBox(50.0f, 50.0f, 50.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.3f, 0.3f, 0.3f), 1.0f);

		walls1.setTexture("wall-texture.jpg");
		walls3.setTexture("wall-texture.jpg");
		turbine.setTexture("wood_planks.jpg");
		quernTop.setTexture("tex-wall.jpg");
		quernBottom.setTexture("tex-wall.jpg");
		roofTop.setTexture("roof-tex.jpg");
		floor.setTexture("wood_planks.jpg");
		door.setTexture("door-testure.jpg");
		desk.setTexture("wood_planks.jpg");
		ground.setTexture("grass_tex.jpg");
		skyBox.setTexture("night-testure.jpg");

		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			theProgram.Use();

			theProgram.setVec3("lightColor", lightColor);
			theProgram.setVec3("lightPos", lightPoss);

			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 projection;

			model = glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));
			model = glm::translate(model, glm::vec3(1.0f , 1.0f, 0.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

			view = camera.GetViewMatrix();

			unsigned int modelLoc = glGetUniformLocation(theProgram.get_programID(), "model");

			theProgram.setMat4("view", view);

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			theProgram.setMat4("projection", projection);

			
			glm::mat4 trans;
			walls1.bindTexture(theProgram.get_programID());
			walls1.draw(trans,modelLoc);
			glm::mat4 trans2;
			trans2 = glm::translate(trans2, glm::vec3(0.0f, -1.0f, 0.0f));
			walls3.bindTexture(theProgram.get_programID());
			walls3.draw(trans2, modelLoc);
			trans2 = glm::translate(trans2, glm::vec3(0.0f, 1.0f, 0.0f));
			roofTop.bindTexture(theProgram.get_programID());
			roofTop.draw(trans2, modelLoc);


			turbine.bindTexture(theProgram.get_programID());
			glm::mat4 transTurbine;
			transTurbine = glm::rotate(transTurbine, (float)glfwGetTime() * (float)turbineSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
			transTurbine = glm::translate(transTurbine, glm::vec3(0.0f, 0.0f, 0.6f));
			turbine.draw(transTurbine, modelLoc);


			glm::mat4 transQuern;
			transQuern = glm::rotate(transQuern, (float)glfwGetTime() * (float)turbineSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
			transQuern = glm::translate(transQuern, glm::vec3(0.0f, -1.15f, 0.0f));
			quernTop.bindTexture(theProgram.get_programID());
			quernTop.draw(transQuern, modelLoc);


			glm::mat4 transFloor;
			floor.bindTexture(theProgram.get_programID());
			floor.draw(transFloor, modelLoc);

			glm::mat4 transDoor;
			transDoor = glm::translate(transDoor, glm::vec3(0.0f, -1.1f, 0.0f));
			door.bindTexture(theProgram.get_programID());
			door.draw(transDoor,modelLoc);

			glm::mat4 transQuernB;
			transQuernB = glm::translate(transQuernB, glm::vec3(0.0f, -1.3f, 0.0f));
			quernBottom.bindTexture(theProgram.get_programID());
			quernBottom.draw(transQuernB, modelLoc);

			glm::mat4 transDesk;
			transDesk = glm::rotate(transDesk, (float)glfwGetTime() * (float)turbineSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
			desk.bindTexture(theProgram.get_programID());
			desk.draw(transDesk, modelLoc);

			glm::mat4 transGround;
			ground.bindTexture(theProgram.get_programID());
			ground.draw(transGround, modelLoc);

			glm::mat4 transSB;
			skyBox.bindTexture(theProgram.get_programID());
			skyBox.draw(transSB, modelLoc);

			lamp.shader = new ShaderProgram("LampShader.vert", "LampShader.frag");

			lamp.shader->Use();

			modelLoc = glGetUniformLocation(lamp.shader->get_programID(), "model");

			lamp.shader->setMat4("view", view);

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			lamp.shader->setMat4("projection", projection);

			glm::mat4 transLamp;
			lamp.draw(transLamp, modelLoc);

			glfwSwapBuffers(window);
		}
	
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
