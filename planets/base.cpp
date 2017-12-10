#define _USE_MATH_DEFINES 
#include "math.h"
#include "Camera.h"
#include "Shader.h"
#include "Header.h"
#include "sphere.h"
#include "Noise.h"
// #include "Perlin.h"
#include "Solar.h"
// #include "Texture.h"
#include "Skybox.h"
#include "Square.h"
#include "Meteor.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, -22.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
float lastX = 400, lastY = 300;
bool firstMouse = true;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(1200, 800, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 400, 100);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // register resizing of window

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader earth_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_earth.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_earth.fp");

	Shader sun_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_sun.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_sun.fp");

	Shader moon_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_moon.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_moon.fp");

	Shader saturn_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_saturn.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_saturn.fp");

	Shader saturn_ring_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_saturn_ring.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_saturn_ring.fp");

	Shader meteor_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_meteor.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_meteor.fp");

	Shader meteor_poly_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_poly_meteor.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_poly_meteor.fp");

	Shader skybox_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_skybox.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_skybox.fp");

	init_buffers(); // Initialize noise buffers for sun

	const unsigned int len = 100; // grid structure of sphere
	const unsigned int len_meteor = 10;
	const unsigned int size = 6 * len * len * 36; // number of points in sphere array
	const unsigned int size_meteor = 6 * len_meteor * len_meteor * 36;
	float * planet = sphere(len);
	float * ring = square();
	float * meteor = meteor_f(len_meteor);

	// EARTH
	unsigned int VAO_earth, VBO_earth;
	glGenVertexArrays(1, &VAO_earth);
	glGenBuffers(1, &VBO_earth);
	glBindVertexArray(VAO_earth);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_earth);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), planet, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// SUN
	unsigned int VAO_sun, VBO_sun;
	glGenVertexArrays(1, &VAO_sun);
	glGenBuffers(1, &VBO_sun);
	glBindVertexArray(VAO_sun);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_sun);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), planet, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// MOON
	unsigned int VAO_moon, VBO_moon;
	glGenVertexArrays(1, &VAO_moon);
	glGenBuffers(1, &VBO_moon);
	glBindVertexArray(VAO_moon);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_moon);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), planet, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// SATURN
	unsigned int VAO_saturn, VBO_saturn;
	glGenVertexArrays(1, &VAO_saturn);
	glGenBuffers(1, &VBO_saturn);
	glBindVertexArray(VAO_saturn);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_saturn);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), planet, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// SATURN RING
	unsigned int VAO_saturn_ring, VBO_saturn_ring;
	glGenVertexArrays(1, &VAO_saturn_ring);
	glGenBuffers(1, &VBO_saturn_ring);
	glBindVertexArray(VAO_saturn_ring);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_saturn_ring);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), ring, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// METEOR
	unsigned int VAO_meteor, VBO_meteor;
	glGenVertexArrays(1, &VAO_meteor);
	glGenBuffers(1, &VBO_meteor);
	glBindVertexArray(VAO_meteor);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_meteor);
	glBufferData(GL_ARRAY_BUFFER, size_meteor * sizeof(float), meteor, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// METEOR RING
	glm::mat4 * meteor_rings = init_meteor_rings();
	unsigned int VBO_meteor_ring;
	glGenBuffers(1, &VBO_meteor_ring);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_meteor_ring);
	glBufferData(GL_ARRAY_BUFFER, n_meteors * sizeof(glm::mat4), glm::value_ptr(*meteor_rings), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);

	// SKYBOX
	unsigned int VAO_skybox, VBO_skybox;
	glGenVertexArrays(1, &VAO_skybox);
	glGenBuffers(1, &VBO_skybox);
	glBindVertexArray(VAO_skybox);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_skybox);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Set the uniform Matrix for vertex shader - contains view and projection matrices
	unsigned int uniformBlockIndexEarth = glGetUniformBlockIndex(earth_shader.ID, "Matrices");
	unsigned int uniformBlockIndexSun = glGetUniformBlockIndex(sun_shader.ID, "Matrices");
	unsigned int uniformBlockIndexMoon = glGetUniformBlockIndex(moon_shader.ID, "Matrices");

	glUniformBlockBinding(earth_shader.ID, uniformBlockIndexEarth, 0);
	glUniformBlockBinding(sun_shader.ID, uniformBlockIndexSun, 0);
	glUniformBlockBinding(moon_shader.ID, uniformBlockIndexMoon, 0);

	unsigned int uboMatrices;
	glGenBuffers(1, &uboMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Set the uniform DirLight for fragment shader - contains light properties
	unsigned int uniformBlockIndexSaturn = glGetUniformBlockIndex(saturn_shader.ID, "DirLight");
	unsigned int uniformBlockIndexMeteor = glGetUniformBlockIndex(meteor_shader.ID, "DirLight");
	unsigned int uniformBlockIndexEarth2 = glGetUniformBlockIndex(earth_shader.ID, "DirLight");

	glUniformBlockBinding(saturn_shader.ID, uniformBlockIndexSaturn, 1);
	glUniformBlockBinding(meteor_shader.ID, uniformBlockIndexMeteor, 1);
	glUniformBlockBinding(earth_shader.ID, uniformBlockIndexEarth2, 1);

	unsigned int uboDirLight;
	glGenBuffers(1, &uboDirLight);

	glBindBuffer(GL_UNIFORM_BUFFER, uboDirLight);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 1);
	glBindBufferRange(GL_UNIFORM_BUFFER, 1, uboDirLight, 0, 2 * sizeof(glm::vec4));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(sunlight_ambient));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(sunlight_diffuse));
	glBindBuffer(GL_UNIFORM_BUFFER, 1);

	// Set noise for Sun texture
	sun_shader.use();
	sun_shader.set("p", SIZE, p);
	sun_shader.set("r", GRID, r);
	sun_shader.set("planetCol", sun_color);

	// Set noise for Skybox texture
	skybox_shader.use();
	skybox_shader.set("p", SIZE, p);
	skybox_shader.set("r", GRID, r);
	skybox_shader.set("projection", projection);
	skybox_shader.set("model", glm::mat4(1.0f));

	moon_shader.use();
	moon_shader.set("planetCol", moon_color);

	earth_shader.use();
	earth_shader.set("planetCol", earth_color);
	earth_shader.set("p", SIZE, p); // GRID instead of SIZE -> only 1D Perlin
	earth_shader.set("r", GRID, r);

	saturn_shader.use();
	saturn_shader.set("p", GRID, p); // GRID instead of SIZE -> only 1D Perlin
	saturn_shader.set("r", GRID, r);
	saturn_shader.set("planetCol", saturn_color);

	saturn_ring_shader.use();
	saturn_ring_shader.set("p", GRID, p); // GRID instead of SIZE -> only 1D Perlin
	saturn_ring_shader.set("r", GRID, r);
	saturn_ring_shader.set("planetCol", saturn_ring_color);

	meteor_shader.use();
	meteor_shader.set("p", GRID, p); // GRID instead of SIZE -> only 1D Perlin
	meteor_shader.set("r", GRID, r);
	meteor_shader.set("planetCol", meteor_color);
	
	while (!glfwWindowShouldClose(window)) // render loop
	{
		processInput(window);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		glEnable(GL_DEPTH_TEST);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		
		glm::mat4 view = camera.GetViewMatrix();
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		
		// SKYBOX RENDERING
		glDepthMask(GL_FALSE);

		glBindVertexArray(VAO_skybox);
		skybox_shader.use();
		glm::mat4 view_skybox = glm::mat4(glm::mat3(view));
		skybox_shader.set("view", view_skybox);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthMask(GL_TRUE);
		
		// EARTH RENDERING
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glBindVertexArray(VBO_earth);

		earth_shader.use(); 

		float earth_x = earth_distance * glm::sin(earth_dispos * currentFrame);
		float earth_z = -earth_distance * glm::cos(earth_dispos * currentFrame);

		glm::mat4 model_earth = glm::translate(glm::mat4(), glm::vec3(earth_x, 0.0f, earth_z));
		model_earth = glm::scale(model_earth, earth_scale);

		earth_shader.set("model", model_earth);
		earth_shader.set("viewPos", camera.Position);
		
		glDrawArrays(GL_TRIANGLES, 0, 36 * len * len);
	
		// SUN RENDERING
		glBindVertexArray(VAO_sun);

		sun_shader.use();

		glm::mat4 model_sun = glm::translate(glm::mat4(1.0f), sun_pos);
		model_sun = glm::scale(model_sun, sun_scale);

		sun_shader.set("model", model_sun);

		glDrawArrays(GL_TRIANGLES, 0, 36 * len * len);
		
		// MOON RENDERING
		glBindVertexArray(VAO_sun);

		moon_shader.use();

		float moon_z = glm::sin(moon_dispos * currentFrame) * moon_distance + earth_z;
		float moon_x = glm::cos(moon_dispos * currentFrame) * moon_distance + earth_x;

		glm::mat4 model_moon = glm::translate(glm::mat4(1.0f), glm::vec3(moon_x, 0.0f, moon_z));
		model_moon = glm::scale(model_moon, moon_scale);

		moon_shader.set("model", model_moon);

		glDrawArrays(GL_TRIANGLES, 0, 36 * len * len);

		// SATURN RENDERING
		glBindVertexArray(VAO_saturn);

		saturn_shader.use();

		float saturn_x = saturn_distance * glm::sin(saturn_dispos * currentFrame);
		float saturn_z = -saturn_distance * glm::cos(saturn_dispos * currentFrame);

		glm::vec3 saturn_rotate = glm::cross(glm::vec3(saturn_x, 0.0f, saturn_z), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 model_saturn = glm::translate(glm::mat4(), glm::vec3(saturn_x, 0.0f, saturn_z));
		model_saturn = glm::rotate(model_saturn, glm::radians(saturn_angle), saturn_rotate);
		model_saturn = glm::scale(model_saturn, saturn_scale);

		saturn_shader.set("model", model_saturn);
		saturn_shader.set("viewPos", camera.Position); 

		glDrawArrays(GL_TRIANGLES, 0, 36 * len * len);

		// METEOR RENDERING
		glBindVertexArray(VAO_meteor);

		meteor_shader.use();

		float meteor_x = meteor_distance * glm::sin(meteor_dispos * currentFrame);
		float meteor_z = - meteor_distance * glm::cos(meteor_dispos * currentFrame);

		glm::mat4 model_meteor = {
			glm::vec4(0.0f),
			glm::vec4(0.0f),
			glm::vec4(0.0f),
			glm::vec4(meteor_x, 0.0f, meteor_z, 1.0f) 
		};

		meteor_shader.set("model", model_meteor);
		meteor_shader.set("viewPos", camera.Position);

		glDrawArraysInstanced(GL_TRIANGLES, 0, 36 * len_meteor * len_meteor, n_meteors);

		// glDrawArrays(GL_TRIANGLES, 0, 36 * len_meteor * len_meteor);
		
		/* // Polygon Mode of Meteors
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		meteor_poly_shader.use();

		meteor_poly_shader.set("model", model_meteor);
		glDrawArrays(GL_TRIANGLES, 0, 36 * len * len);
		*/
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDisable(GL_CULL_FACE);

		// SATURN RING RENDERING -> at the end of rendering because of face culling
		glEnable(GL_BLEND); // blend those parts of the square not encapsulated by the circle
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindVertexArray(VAO_saturn_ring);

		saturn_ring_shader.use();

		glm::mat4 model_saturn_ring = glm::translate(glm::mat4(), glm::vec3(saturn_x, 0.0f, saturn_z));
		model_saturn_ring = glm::rotate(model_saturn_ring, glm::radians(saturn_angle), saturn_rotate);
		model_saturn_ring = glm::scale(model_saturn_ring, saturn_ring_scale);

		saturn_ring_shader.set("model", model_saturn_ring);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisable(GL_BLEND);

		// EARTH POLYGONS RENDERING
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete[] planet;
	delete[] ring;	
	delete[] meteor;
	delete[] meteor_rings;

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
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

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(std::string filename, bool flip)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(flip);
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		std::cout << nrComponents << std::endl;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}