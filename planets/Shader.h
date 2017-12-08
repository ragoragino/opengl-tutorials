#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Header.h"

class Shader
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void use();
	// utility uniform functions
	template <typename T>
	void set(const std::string &name, T value) const;
	template <typename T>
	void set(const std::string &name, unsigned int count, T * value) const;
};

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Compile shaders
	int success;
	char infoLog[512];

	// vertex Shader
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// fragment Shader
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

template <typename T>
void Shader::set(const std::string &name, T value) const
{
	std::cout << "Incorrect base overload!" << std::endl;
	std::cout << "Name: " << name << std::endl;
}

template <>
void Shader::set(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

template <>
void Shader::set(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

template <>
void Shader::set(const std::string &name, glm::mat4 model) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(model));
}

template <>
void Shader::set(const std::string &name, glm::vec3 model) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), model.x, model.y, model.z);
}

// set overload for arrays
template<typename T>
void Shader::set(const std::string &name, unsigned int count, T * value) const
{
	std::cout << "Incorrect array overload!" << std::endl;
}

template<>
void Shader::set(const std::string &name, unsigned int count, float * value) const
{
	glUniform1fv(glGetUniformLocation(ID, name.c_str()), count, value);
}

template<>
void Shader::set(const std::string &name, unsigned int count, int * value) const
{
	glUniform1iv(glGetUniformLocation(ID, name.c_str()), count, value);
}

template<>
void Shader::set(const std::string &name, unsigned int count, glm::vec3 value[]) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), count, &value[0].x);
}