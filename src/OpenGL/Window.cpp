#include "Window.h"
#include "ResourceManager.h"
#include "Particles.h"
namespace Engine{


	bool firstMouse = true;
	double lastX;
	double lastY;

	float deltaTime;
	float currentTime;
	float lastTime = 0.0f;
	ParticleGenerator particleGen;
	void FrameBufferCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}


	Window::Window(std::string name, int Width, int Height)
	{
		props.Name = name;
		props.Width = Width;
		props.Height = Height;

	}
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
		}
	}
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
			particleGen.SetType(ParticleType::SAND);
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
			particleGen.SetType(ParticleType::WATER);
	}

	void Window::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		props.window = glfwCreateWindow(props.Width, props.Height, props.Name.c_str(), NULL, NULL);
		
		glfwSetKeyCallback(props.window, key_callback);
		glfwMakeContextCurrent(props.window);
	
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize OpenGL context" << std::endl;

		}
		glViewport(0, 0, props.Width, props.Height);


		glfwSetMouseButtonCallback(props.window, mouse_button_callback);
		glfwSetCursorPosCallback(props.window, [](GLFWwindow* window, double xpos, double ypos) {
			
			});
		
		glfwSetFramebufferSizeCallback(props.window,FrameBufferCallback);
	
		glEnable(GL_BLEND);

		//glfwSetInputMode(props.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		
	}

	void Window::GameLoop()
	{
		Shader shader = ResourceManager::LoadShader("shader","C:\\Users\\yigit\\source\\repos\\Particles\\Particles\\src\\Shaders\\Defaultvs.glsl", "C:\\Users\\yigit\\source\\repos\\Particles\\Particles\\src\\Shaders\\Defaultfs.glsl");
		float vertices[] = {
			// pos      // tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};
		
		unsigned int VAO;
		unsigned int VBO;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
			
		//ParticleGenerator particleGen;

		particleGen.GenerateParticles();

		ResourceManager::LoadTexture("sand", "C:\\Users\\yigit\\source\\repos\\Particles\\Particles\\src\\Textures\\sand.jpg");
		
		glm::mat4 projection = glm::ortho(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, 1.0f);
		//glfwSwapInterval(0);
		while (!glfwWindowShouldClose(props.window))
		{
			currentTime = glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			//std::cout << "DT: " <<deltaTime;
			glClearColor(1.f, 1., 1.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Use();
			shader.SetMat4("projection", projection);

			
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(5.0f, 5.0f, 0.0f));
			model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
			
			shader.SetMat4("model", model);
			// std::cout << glGetError() << std::endl;
			glBindVertexArray(VAO);
			
			glDrawArrays(GL_TRIANGLES, 0, 6);


			particleGen.update(shader);
			particleGen.Draw(shader);

			int state = glfwGetMouseButton(props.window, GLFW_MOUSE_BUTTON_LEFT);
			if (state == GLFW_PRESS)
			{

				double xpos, ypos;
				//getting cursor position


				glfwGetCursorPos(props.window, &xpos, &ypos);


				particleGen.newParticle(xpos, ypos);
			}

			glfwSwapBuffers(props.window);


			glfwPollEvents();
		}	}


	
};
