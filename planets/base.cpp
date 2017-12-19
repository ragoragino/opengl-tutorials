#include "Header.h"
#include "Camera.h"
#include "Shader.h"
#include "sphere.h"
#include "Noise.h"
// #include "Perlin.h"
#include "Solar.h"
// #include "Texture.h"
#include "Skybox.h"
#include "Square.h"
#include "Meteor.h"
#include "Planet.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
float lastX = 400, lastY = 300;
bool firstMouse = true;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
uint32_t Planet::len; // declare a static Planet member len
uint32_t screen_width = 1200, screen_height = 800;
uint32_t screen_pos_x = 500, screen_pos_y = 200;

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, screen_pos_x, screen_pos_y);

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

	Shader shadow_shader = Shader("D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\vshader_shadow.vp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\fshader_shadow.fp",
		"D:\\Materials\\Programming\\Projekty\\opengl-tutorial\\planets\\resources\\gshader_shadow.gp");

	// Inefficient to construct and render Sun as a Planet object
	Planet earth = Planet(earth_distance, earth_speed, earth_scale, earth_color, earth_rotation, 0.0f);

	Planet saturn = Planet(saturn_distance, saturn_speed, saturn_scale, saturn_color, saturn_rotation, saturn_angle);

	Moon earth_moon = Moon(&earth, moon_distance, moon_speed, moon_scale, moon_color, moon_rotation, 0.0f);

	init_buffers(); // Initialize noise buffers
	
	const uint32_t len = 100; // grid structure of sphere
	Planet::len = len; // Assign length to the static Planet member len
	const uint32_t len_meteor = 10; // grid structureof the meteor
	const uint32_t size = 6 * len * len * 18; // number of points in sphere array
	const uint32_t size_meteor = 6 * len_meteor * len_meteor * 18;
	float * planet = sphere(len);
	float * ring = square();
	float * meteor = meteor_f(len_meteor);

	/* *********************************************
	// BUFFERS
	********************************************* */
	// PLANET
	uint32_t VAO_planet, VBO_planet;
	glGenVertexArrays(1, &VAO_planet);
	glGenBuffers(1, &VBO_planet);
	glBindVertexArray(VAO_planet);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_planet);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), planet, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// SATURN RING
	uint32_t VAO_saturn_ring, VBO_saturn_ring;
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
	uint32_t VAO_meteor, VBO_meteor;
	glGenVertexArrays(1, &VAO_meteor);
	glGenBuffers(1, &VBO_meteor);
	glBindVertexArray(VAO_meteor);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_meteor);
	glBufferData(GL_ARRAY_BUFFER, size_meteor * sizeof(float), meteor, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// METEOR RING
	glm::mat4 * meteor_rings = InitializeMeteorRing();
	uint32_t VBO_meteor_ring;
	glGenBuffers(1, &VBO_meteor_ring);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_meteor_ring);
	glBufferData(GL_ARRAY_BUFFER, N_METEORS * sizeof(glm::mat4), glm::value_ptr(*meteor_rings), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);

	// METEOR RING y OFFSET
	float * meteor_ring_fluctation = InitializeMeteorRingFlucation(); 
	uint32_t * meteor_order = new uint32_t[N_METEORS];
	for(uint32_t i = 0; i < N_METEORS; ++i)
	{
		meteor_order[i] = i;
	}

	uint32_t VBO_meteor_ring_fluctuation;
	glGenBuffers(1, &VBO_meteor_ring_fluctuation);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_meteor_ring_fluctuation);
	glBufferData(GL_ARRAY_BUFFER, N_METEORS * sizeof(uint32_t), meteor_order, GL_STATIC_DRAW);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(uint32_t), (void*)0);
	glVertexAttribDivisor(5, 1);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// SKYBOX
	uint32_t VAO_skybox, VBO_skybox;
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

	/* *********************************************
	// UNIFORMS
	********************************************* */
	// Set the uniform Matrix for vertex shader - contains view and projection matrices
	uint32_t uniformBlockIndexEarth = glGetUniformBlockIndex(earth_shader.ID, "Matrices");
	uint32_t uniformBlockIndexSun = glGetUniformBlockIndex(sun_shader.ID, "Matrices");
	uint32_t uniformBlockIndexMoon = glGetUniformBlockIndex(moon_shader.ID, "Matrices");

	glUniformBlockBinding(earth_shader.ID, uniformBlockIndexEarth, 0);
	glUniformBlockBinding(sun_shader.ID, uniformBlockIndexSun, 0);
	glUniformBlockBinding(moon_shader.ID, uniformBlockIndexMoon, 0);

	uint32_t uboMatrices;
	glGenBuffers(1, &uboMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / (float)screen_height, 0.1f, 100.0f);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));

	// Set the uniform DirLight for fragment shader - contains light properties
	uint32_t uniformBlockIndexSaturn = glGetUniformBlockIndex(saturn_shader.ID, "DirLight");
	uint32_t uniformBlockIndexMeteor = glGetUniformBlockIndex(meteor_shader.ID, "DirLight");
	uint32_t uniformBlockIndexEarth2 = glGetUniformBlockIndex(earth_shader.ID, "DirLight");
	uint32_t uniformBlockIndexMoon2 = glGetUniformBlockIndex(moon_shader.ID, "DirLight");

	glUniformBlockBinding(saturn_shader.ID, uniformBlockIndexSaturn, 1);
	glUniformBlockBinding(meteor_shader.ID, uniformBlockIndexMeteor, 1);
	glUniformBlockBinding(earth_shader.ID, uniformBlockIndexEarth2, 1);
	glUniformBlockBinding(moon_shader.ID, uniformBlockIndexMoon2, 1);

	uint32_t uboDirLight;
	glGenBuffers(1, &uboDirLight);

	glBindBuffer(GL_UNIFORM_BUFFER, uboDirLight);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 1, uboDirLight, 0, 2 * sizeof(glm::vec4));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(sunlight_ambient));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(sunlight_diffuse));
	
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	/* *********************************************
	// SHADOWS
	********************************************* */
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int shadow_buffer;
	glGenFramebuffers(1, &shadow_buffer);

	unsigned int shadow_texture;
	glGenTextures(1, &shadow_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_texture);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, shadow_buffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadow_texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	float near_plane = 1.0f;
	float far_plane = 50.0f;
	glm::mat4 shadowProj = glm::perspective((float)M_PI * 0.5f, (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
	glm::mat4 shadowTransforms[6];
	shadowTransforms[0] = shadowProj * glm::lookAt(sun_pos, sun_pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	shadowTransforms[1] = shadowProj * glm::lookAt(sun_pos, sun_pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	shadowTransforms[2] = shadowProj * glm::lookAt(sun_pos, sun_pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	shadowTransforms[3] = shadowProj * glm::lookAt(sun_pos, sun_pos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	shadowTransforms[4] = shadowProj * glm::lookAt(sun_pos, sun_pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	shadowTransforms[5] = shadowProj * glm::lookAt(sun_pos, sun_pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));

	/* *********************************************
	// SHADERS
	********************************************* */
	sun_shader.use();
	sun_shader.set("p", SIZE, p);
	sun_shader.set("r", GRID, r);
	sun_shader.set("planetCol", sun_color);

	skybox_shader.use();
	skybox_shader.set("p", SIZE, p);
	skybox_shader.set("r", GRID, r);
	skybox_shader.set("projection", projection);
	skybox_shader.set("model", glm::mat4(1.0f));

	moon_shader.use();
	moon_shader.set("planetCol", moon_color);
	moon_shader.set("shadow_texture", 0);
	moon_shader.set("far_plane", far_plane);

	earth_shader.use();
	earth_shader.set("planetCol", earth_color);
	earth_shader.set("p", SIZE, p); // GRID instead of SIZE -> only 1D Perlin
	earth_shader.set("r", GRID, r);
	earth_shader.set("shadow_texture", 0);
	earth_shader.set("far_plane", far_plane);

	saturn_shader.use(); // TODO 512
	saturn_shader.set("p", 512, p); // GRID instead of SIZE -> only 1D Perlin
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
	meteor_shader.set("offset", N_METEORS, meteor_ring_fluctation);
	uint32_t meteor_counter = 0;

	shadow_shader.use();
	shadow_shader.set("shadowMatrices", 6, shadowTransforms);
	shadow_shader.set("far_plane", far_plane);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	
	while (!glfwWindowShouldClose(window)) // render loop
	{
		processInput(window);

		glEnable(GL_DEPTH_TEST);

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* *********************************************
		// FILLING SHADOW BUFFER
		********************************************* */
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, shadow_buffer);
		glClear(GL_DEPTH_BUFFER_BIT);
		
		// Face culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CCW);

		// EARTH RENDERING
		glBindVertexArray(VAO_planet);
		earth.render(shadow_shader, currentFrame, camera);

		// MOON RENDERING
		earth_moon.render(shadow_shader, currentFrame, camera);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glDisable(GL_CULL_FACE);

		/* *********************************************
		// SCENE RENDERING
		********************************************* */

		glViewport(0, 0, screen_width, screen_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
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
	
		// Face culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		// EARTH RENDERING
		glBindVertexArray(VAO_planet);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_texture);
		earth.render(earth_shader, currentFrame, camera);
	
		// SUN RENDERING
		sun_shader.use();

		// Sun is always in the centre - no translation needed
		glm::mat4 model_sun = glm::scale(glm::mat4(), sun_scale);
		sun_shader.set("model", model_sun);

		glDrawArrays(GL_TRIANGLES, 0, 36 * len * len);
		
		// MOON RENDERING
		earth_moon.render(moon_shader, currentFrame, camera);

		// SATURN RENDERING 
		saturn.render(saturn_shader, currentFrame, camera);

		// METEOR RENDERING
		glBindVertexArray(VAO_meteor);

		meteor_shader.use();

		// Move the meteors
		glm::mat4 model_meteor = glm::rotate(glm::mat4(), - meteor_dispos * currentFrame, glm::vec3(0.0f, 1.0f, 0.0f));

		meteor_shader.set("model", model_meteor);
		meteor_shader.set("viewPos", camera.Position);
		meteor_counter = (meteor_counter + 1) % N_METEORS;
		meteor_shader.set("i", meteor_counter);

		glDrawArraysInstanced(GL_TRIANGLES, 0, 36 * len_meteor * len_meteor, N_METEORS);

		glDisable(GL_CULL_FACE);

		// SATURN RING RENDERING -> at the end of rendering because of face culling
		glEnable(GL_BLEND); // blend those parts of the square not encapsulated by the circle
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindVertexArray(VAO_saturn_ring);

		saturn_ring_shader.use();

		glm::mat4 model_saturn_ring = glm::translate(glm::mat4(), glm::vec3(saturn.x, 0.0f, saturn.z));
		model_saturn_ring = glm::rotate(model_saturn_ring, glm::radians(saturn_angle), saturn.rotate_vec);
		model_saturn_ring = glm::scale(model_saturn_ring, saturn_ring_scale);

		saturn_ring_shader.set("model", model_saturn_ring);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisable(GL_BLEND);
	
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete[] planet;
	delete[] ring;	
	delete[] meteor;
	delete[] meteor_rings;
	delete[] meteor_ring_fluctation;

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
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
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