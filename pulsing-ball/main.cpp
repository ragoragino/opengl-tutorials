#define _CRT_SECURE_NO_WARNINGS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtx/norm.hpp>
#define _USE_MATH_DEFINES 
#include "math.h"
#include "string.h"
#include "Shader.h"
#include "spire.h"
#include "D:\\Materials\\Programming\\C++\\Libraries\\FreeImage\\Dist\\x64\\FreeImage.h"

unsigned int ID; // ID of the shader
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0); // current camera position
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // current camera target
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // current camera up vector
float lastX = 400, lastY = 300; // initial positions of mouse
bool firstMouse = true; // initial mouse indicator
float yaw = -90.0f, pitch = 0.0f; // initial yaw and pitch values
float fov = 90.0f; // initial fov
unsigned int width = 1200, height = 800; // window parameters

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const int LEN = 30; // INPUT : Number of bottom triangles

int main()
{
	// Create the spire object and initialize variables
	int n_triangles = 0; // number of triangles on one side of the spire
	for (int i = 2 * LEN - 1; i >= 1; i -= 2)
	{
		n_triangles += i;
	}
	const float size = 10.0; // size of all sides of the spire
	float* spire_obj = spire(size, LEN, n_triangles);
	const int side = n_triangles * 3 * 3; // number of floats representing one sides
	const float spire_height = pow(pow(size, 2.0) / 2.0, 0.5); // hei9ght of the spire
	const int steps = 1000; // number of expanding/stretching steps
	int step = steps;
	float ratio, rotation_param; // ratio for expansion/stretching and parameter for rotation
	int time_counter = 0; // counter used to take snapshots
	BYTE* pixels = new BYTE[3 * width * height]; // Create buffer to hold pixel values for snapshots
	cameraPos = glm::vec3(0.0f, 0.0f, spire_height * 2); // Initialize camera position
	const float theta = M_PI / 2; // angle for rotation

	// Setting up directories for saving snapshots
	const char dir[] = "visuals\\snapshot_";
	const size_t N = sizeof(dir);
	const char end[] = ".tiff";
	const size_t N_add = N + sizeof(end) + 4; // 4 bytes for time_counter signifier appended
	char cur_dir[N_add];

	// Initialize GLFW 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 100, 100);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\pulsing-ball\\data\\vshader.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\pulsing-ball\\data\\fshader.fp"); // Paths to shaders
	ID = shader.ID;
	
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); 
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * side, spire_obj, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shader.use();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // set polygon line mode drawing

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glEnable(GL_DEPTH_TEST);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * side, spire_obj, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// each 2 * pi seconds the object makes one rotation
		rotation_param = 2 * glfwGetTime() / theta; 
				
		for (int i = 0; i != 4; ++i)
		{
			glm::mat4 model;
			model = glm::rotate(model, theta * i + rotation_param, glm::vec3(0.0f, 1.0f, 0.0f));
			shader.set("model", model);
			glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			shader.set("view", view);
			glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 10000.0f);
			shader.set("projection", projection);
			glDrawArrays(GL_TRIANGLES, 0, n_triangles * 3);
		}

		for (int i = 0; i != 4; ++i)
		{
			glm::mat4 model;
			model = glm::rotate(model, theta * i + rotation_param, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, theta * 2, glm::vec3(0.0f, 0.0f, 1.0f));
			shader.set("model", model);
			glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			shader.set("view", view);
			glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
			shader.set("projection", projection);
			glDrawArrays(GL_TRIANGLES, 0, n_triangles * 3);
		}

		// Change the data buffer by expanding or shrinking the object
		if (step > 0)
		{
			for (int i = 0; i != n_triangles * 3 * 3; i += 3)
			{
				ratio = spire_height / pow(spire_obj[i] * spire_obj[i] + spire_obj[i + 1] * 
					spire_obj[i + 1] + spire_obj[i + 2] * spire_obj[i + 2], 0.5);

				spire_obj[i] += (ratio * spire_obj[i] - spire_obj[i]) / step;
				spire_obj[i + 1] += (ratio * spire_obj[i + 1] - spire_obj[i + 1]) / step;
				spire_obj[i + 2] += (ratio * spire_obj[i + 2] - spire_obj[i + 2]) / step;
			}

			step -= 1;

			if (step == 0)
			{
				step = -steps;
			}
		}
		else
		{
			for (int i = 0; i != n_triangles * 3 * 3; i += 3)
			{
				ratio = spire_height * 0.5 * size / (size * 0.5 * spire_obj[i + 1] + 
					spire_height * spire_obj[i + 2]);

				// the order is reversed because step is negative
				spire_obj[i] -= (ratio * spire_obj[i] - spire_obj[i]) / step; 
				spire_obj[i + 1] -= (ratio * spire_obj[i + 1] - spire_obj[i + 1]) / step;
				spire_obj[i + 2] -= (ratio * spire_obj[i + 2] - spire_obj[i + 2]) / step;
			}

			step += 1;

			if (step == 0)
			{
				step = steps;
			}
		}

		// Save sanpshots
		if (time_counter < glfwGetTime())
		{
			glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

			char char_num[9];
			_itoa(time_counter, char_num, 10);
			memcpy(cur_dir, dir, N);

			FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0x0000FF, 0xFF0000, 0x00FF00, false);
			FreeImage_Save(FIF_TIFF, image, strcat(strcat(cur_dir, char_num), end), TIFF_NONE);

			FreeImage_Unload(image);

			time_counter += 2; // Take snapshots every two seconds
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete[] pixels;

	glfwTerminate();

	return 0;
}

// Resizing the window after user resizes it
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Check whether the user ESC the window and change the position of camera based on
// pressing of WASD keys
void processInput(GLFWwindow *window)
{
	float cameraSpeed = 0.005f;
	glm::vec3 stabilizer = glm::vec3(1.0, 0.0, 1.0);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront * stabilizer;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront * stabilizer;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * stabilizer * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * stabilizer * cameraSpeed;
}


// Change the target direction of camera based on mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}


// Change fov on mouse scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}



