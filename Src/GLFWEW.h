/*
@file GLFWEW.h
*/
#ifndef GLFWEW_H_INCLUDED
#define GLFWEW_H_INCLUDED
#include <GL/glew.h>
#include "GamePad.h"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace GLFWEW {

	/*
	GLFW、GLEWを統合したもの
	*/
	class Window
	{
	public:
		static Window& Instance();
		bool Init(int w, int h, const char* title);
		bool ShouldClose() const;
		void SwapBuffers() const;
		void Update();

		void InitTimer();
		void UpdateTimer();
		double DeltaTime() const;

		bool IsKeyDown(int key) const;
		bool IsKeyPressed(int key) const;
		glm::vec2 GetMousePosition() const;
		int GetMouseButton(int button) const;
		const GamePad& GetGamePad() const;

	private:
		Window();
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		void UpdateGamePad();

		bool isGLFWInitialized = false;
		bool isInitialized = false;
		GLFWwindow* window = nullptr;
		double previousTime = 0;
		double deltaTime = 0;
		GamePad gamePad;

		enum class KeyState : char {
			release,
			press1st,
			press,
		};

		KeyState keyState[GLFW_KEY_LAST + 1];
	};

} // namespace GLFWEW

#endif // GLFWEW_H_INCLUDED