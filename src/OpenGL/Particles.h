#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "ResourceManager.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include <map>
#include <vector>

namespace Engine {
	enum ParticleType
	{
		SAND,
		WATER
	};
	struct Particle
	{
		float mass;
		float velocity;
		glm::vec4 color;
		glm::vec2 Position;
		bool updated = false;
		bool exist;
		ParticleType type;
		Particle(ParticleType type =ParticleType::SAND,bool exist = false,float mass = 1.0f, float velocity = 1.0f, glm::vec4 color = glm::vec4(0.5f, 0.2f, 0.3f, 1.0f), glm::vec2 Position = glm::vec2(0.0f, 0.0f))
			:mass(mass), velocity(velocity), color(color), Position(Position),exist(exist),type(type)
		{

		};
	};

	class ParticleGenerator
	{
	public:
		ParticleGenerator();

		void GenerateParticles();

		void update(Shader &shader);

		void updateSand(Shader& shader,Particle &particle, int y, int x);

		void updateWater(Shader& shader,Particle &particle, int y, int x);

		void newParticle(double x, double y);

		void SetType(ParticleType type);

		void Draw(Shader &shader);
	private:
		int gridX = 100;
		int gridY = 100;
		ParticleType type;
		std::vector < std::vector<Particle>> Particles;
	
		unsigned int VAO;

	};

}