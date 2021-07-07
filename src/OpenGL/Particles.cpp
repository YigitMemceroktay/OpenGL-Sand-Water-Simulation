#include "Particles.h"

Engine::ParticleGenerator::ParticleGenerator()
{
	
}

void Engine::ParticleGenerator::GenerateParticles()
{
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	
	for(int i = 0; i <gridY; i++)
	{
		std::vector<Particle> particlesRow;
		
		for (int j = 0; j < gridX; j++)
		{
			
			
			//std::cout << "GLGEN" << std::endl;

		
			Particle particle;
			/*
			if (j >= 30 && j <= 150 && i >=30 && i <= 150)
			{
				
				
			}
			*/
			
				
				particle.exist = false;
			
			particlesRow.push_back(particle);
		}
		
		Particles.push_back(particlesRow);
	
	}

}

void Engine::ParticleGenerator::updateSand(Shader& shader, Particle& particle, int y, int x)
{
	if (x != 0 && x != gridX-1) {
		if (!Particles[y + 1][x].exist)
		{
			particle.Position.y += 10.0f;
			Particles[y + 1][x] = particle;
			Particles[y][x].exist = false;

		}
		

		else if (!Particles[y + 1][x - 1].exist)
		{
			particle.Position.y += 10.0f;
			particle.Position.x -= 10.0f;
			Particles[y + 1][x - 1] = particle;
			Particles[y][x].exist = false;
		}
		else if (!Particles[y + 1][x + 1].exist)
		{
			particle.Position.y += 10.0f;
			particle.Position.x += 10.0f;
			Particles[y + 1][x + 1] = particle;
			Particles[y][x].exist = false;
		}
		else if (Particles[y + 1][x].exist && Particles[y + 1][x].type == ParticleType::WATER)
		{
			Particles[y + 1][x].type = ParticleType::SAND;
			Particles[y][x].type = ParticleType::WATER;
		}
	}
	else if (x == gridX-1)
	{
		if (!Particles[y + 1][x].exist)
		{
			particle.Position.y += 10.0f;
			Particles[y + 1][x] = particle;
			Particles[y][x].exist = false;

		}


		else if (!Particles[y + 1][x - 1].exist)
		{
			particle.Position.y += 10.0f;
			particle.Position.x -= 10.0f;
			Particles[y + 1][x - 1] = particle;
			Particles[y][x].exist = false;
		}
		else if (Particles[y + 1][x].exist && Particles[y + 1][x].type == ParticleType::WATER)
		{
			Particles[y + 1][x].type = ParticleType::SAND;
			Particles[y][x].type = ParticleType::WATER;
		}
	}
	else
	{
		if (!Particles[y + 1][x].exist)
		{
			particle.Position.y += 10.0f;
			Particles[y + 1][x] = particle;
			Particles[y][x].exist = false;

		}
		else if (!Particles[y + 1][x + 1].exist)
		{
			particle.Position.y += 10.0f;
			particle.Position.x += 10.0f;
			Particles[y + 1][x + 1] = particle;
			Particles[y][x].exist = false;
		}
		else if (Particles[y + 1][x].exist && Particles[y + 1][x].type == ParticleType::WATER)
		{
			Particles[y + 1][x].type = ParticleType::SAND;
			Particles[y][x].type = ParticleType::WATER;
		}
	}

}

void Engine::ParticleGenerator::updateWater(Shader& shader,Particle &particle, int y, int x)
{
	
			
				if (x != 0 && x != gridX-1) {
					if (!Particles[y + 1][x].exist)
					{
						particle.Position.y += 10.0f;
						Particles[y + 1][x] = particle;
						Particles[y][x].exist = false;

					}


					else if (!Particles[y + 1][x - 1].exist)
					{
						particle.Position.y += 10.0f;
						particle.Position.x -= 10.0f;
						Particles[y + 1][x - 1] = particle;
						Particles[y][x].exist = false;
					}
					else if (!Particles[y + 1][x + 1].exist)
					{
						particle.Position.y += 10.0f;
						particle.Position.x += 10.0f;
						Particles[y + 1][x + 1] = particle;
						Particles[y][x].exist = false;
					}
					else if (!Particles[y][x + 1].exist)
					{
						particle.Position.x += 10.0f;
						Particles[y][x + 1] = particle;
						Particles[y][x].exist = false;
					}
					else if (!Particles[y][x - 1].exist)
					{
						particle.Position.x -= 10.0f;
						Particles[y][x - 1] = particle;
						Particles[y][x].exist = false;
					}
				}
				else if (x == gridX-1)
				{
					if (!Particles[y + 1][x].exist)
					{
						particle.Position.y += 10.0f;
						Particles[y + 1][x] = particle;
						Particles[y][x].exist = false;

					}


					else if (!Particles[y + 1][x - 1].exist)
					{
						particle.Position.y += 10.0f;
						particle.Position.x -= 10.0f;
						Particles[y + 1][x - 1] = particle;
						Particles[y][x].exist = false;
					}
					
					else if (!Particles[y][x - 1].exist)
					{
						particle.Position.x -= 10.0f;
						Particles[y][x - 1] = particle;
						Particles[y][x].exist = false;
					}
				}
				else
				{
					if (!Particles[y + 1][x].exist)
					{
						particle.Position.y += 10.0f;
						Particles[y + 1][x] = particle;
						Particles[y][x].exist = false;

					}
					else if (!Particles[y + 1][x + 1].exist)
					{
						particle.Position.y += 10.0f;
						particle.Position.x += 10.0f;
						Particles[y + 1][x + 1] = particle;
						Particles[y][x].exist = false;
					}
					else if (!Particles[y][x + 1].exist)
					{
						particle.Position.x += 10.0f;
						Particles[y][x + 1] = particle;
						Particles[y][x].exist = false;
					}
				
				}



		
	
}

void Engine::ParticleGenerator::update(Shader& shader)
{
	for (int y = gridY - 2; y >= 0; y--)
	{

		for (int x = 0; x < gridX; x++)
		{

			Particle particle = Particles[y][x];
			if (particle.exist && !particle.updated) {
				if (particle.type == ParticleType::SAND)
				{
					particle.updated = true;
					updateSand(shader, particle, y, x);
				}
				else if (particle.type == ParticleType::WATER)
				{
					particle.updated = true;
					updateWater(shader, particle, y, x);
				}

				
			}
		
		}
		}
	for (int y =0; y<gridY; y++)
	{

		for (int x = 0; x < gridX; x++)
		{
			Particles[y][x].updated = false;
				
		}
	}
	
}

void Engine::ParticleGenerator::newParticle(double x, double y)
{
	int X = x / 10.0f;
	int Y = y / 10.0f;

	if (X >= gridX)
		X = gridX-1;
	if (X < 0)
		X = 1;
	if (Y >= gridY)
		Y = gridY-1;
	if (Y < 0)
		Y = 1;

	std::cout << "X: " << X << " Y:" << Y << "\n";
	
						Particle particle;
						particle.type = type;
						particle.exist = true;

						particle.Position = glm::vec2(X * 10., Y * 10.0f);
						
						Particles[Y][X] = particle;
					
			
			
		
	
	}

void Engine::ParticleGenerator::SetType(ParticleType type)
{
	this->type = type;
}
	

void Engine::ParticleGenerator::Draw(Shader& shader)
{
	shader.Use();
	unsigned int sand = ResourceManager::GetTexture("sand");
	for (std::vector<Particle> particleRow : Particles)
	{
		for (const Particle &particle : particleRow)
		{
			if (particle.exist) {
				glm::mat4 model(1.0f);
				model = glm::translate(model, glm::vec3(particle.Position, 0.0));
				model = glm::scale(model, glm::vec3(10.0f,10.0f, 0.0));
			
				shader.SetMat4("model", model);
				if(particle.type == ParticleType::WATER)
				{
					shader.SetFloat4("color", glm::vec4(0.00, 1.00, 1.00, 0.75));
				}
				else if (particle.type == ParticleType::SAND)
				{
					//shader.SetFloat4("color", glm::vec4(194 / 255., 178. / 255., 128. / 255., 1.0f));
					shader.SetFloat4("color", glm::vec4(0.80, 0.63, 0.33,1.0f));
				}
				glBindTexture(GL_TEXTURE_2D,sand);
				glBindVertexArray(VAO);
				
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
			}
	}
	

	
}
