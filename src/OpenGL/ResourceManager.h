#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Shader.h"
#include <fstream>
namespace Engine
{
	class ResourceManager
	{
	public:
		static std::map<std::string, Shader> shaders;
		static std::map<std::string,unsigned int> textures;
	public:
		static Shader& LoadShader(std::string name, const char* vertexSrc, const char* fragmentSrc);
		static Shader LoadShaderFromFile(const char* vertexSrc, const char* fragmentSrc);
		static std::string ReadFile(const char* location);
		static Shader& GetShader(std::string name);
		static unsigned int LoadTexture(std::string name, std::string location);
		static unsigned int GetTexture(std::string name);
	};

}