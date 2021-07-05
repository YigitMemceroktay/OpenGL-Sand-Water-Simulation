#include "Window.h"
namespace Engine{


	bool firstMouse = true;
	double lastX;
	double lastY;

	

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

	void Window::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		props.window = glfwCreateWindow(props.Width, props.Height, props.Name.c_str(), NULL, NULL);
		
		
		glfwMakeContextCurrent(props.window);
	
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize OpenGL context" << std::endl;

		}
		glViewport(0, 0, props.Width, props.Height);

		glEnable(GL_DEPTH_TEST);

		
		
		glfwSetFramebufferSizeCallback(props.window,FrameBufferCallback);
	
		glEnable(GL_BLEND);

		glfwSetInputMode(props.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		
	}

	void Window::GameLoop()
	{
		while (!glfwWindowShouldClose(props.window))
		{
			glClearColor(0.5f, 0.2, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			glfwSwapBuffers(props.window);
			glfwPollEvents();
		}
	}


	
};
