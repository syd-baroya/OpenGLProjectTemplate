#pragma  once

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


 // interface for detecting input events
class EventCallbacks
{

	public:

		virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

		virtual void mouseCallback(GLFWwindow* window, int button, int action, int mods) = 0;

		virtual void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) = 0;

		virtual void scrollCallback(GLFWwindow* window, double dX, double dY) = 0;

		virtual void resizeCallback(GLFWwindow* window, int in_width, int in_height) = 0;

};

class WindowManager
{

public:

	WindowManager();
	~WindowManager();

	WindowManager(const WindowManager&) = delete;
	WindowManager& operator= (const WindowManager&) = delete;

	bool init(int const width, int const height);
	void shutdown();

	void setEventCallbacks(EventCallbacks* callbacks);

	GLFWwindow* getHandle();

protected:

	// This class implements the singleton design pattern
	static WindowManager* instance;

	GLFWwindow* windowHandle = nullptr;
	EventCallbacks* callbacks = nullptr;

private:

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypox);
	static void scroll_callback(GLFWwindow* window, double dX, double dY);
	static void resize_callback(GLFWwindow* window, int in_width, int in_height);

};

#endif
