/*
@file GLFWEW.cpp
*/
#include "GLFWEW.h"
#include <iostream>

/// GLFW��GLEW�����b�v���邽�߂̖��O���.
namespace GLFWEW {

	void APIENTRY OutputGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
	{
		std::cerr << message << "\n";
	}

	/*
	GLFW����̃G���[�񍐂���������.
	
	@param error �G���[�ԍ�.
	@param desc  �G���[�̓��e.
	*/
	void ErrorCallback(int error, const char* desc)
	{
		std::cerr << "ERROR: " << desc << std::endl;
	}

	/*
	�V���O���g���C���X�^���X���擾����.
	
	@return Window�̃V���O���g���C���X�^���X.
	*/
	Window& Window::Instance()
	{
		static Window instance;
		return instance;
	}

	/*
	�R���X�g���N�^.
	*/
	Window::Window()
	{
	}

	/*
	�f�X�g���N�^.
	*/
	Window::~Window()
	{
		if (isGLFWInitialized) {
			glfwTerminate();
		}
	}

	/*
	GLFW/GLEW�̏�����.
	
	@param w �E�B���h�E�̕`��͈͂̕�(�s�N�Z��).
	@param h �E�B���h�E�̕`��͈͂̍���(�s�N�Z��).
	@param title �E�B���h�E�^�C�g��(UTF-8��0�I�[������).
	
	@retval true ����������.
	@retval false ���������s.
	*/
	bool Window::Init(int w, int h, const char* title)
	{
		if (isInitialized) {
			std::cerr << "ERROR: GLFWEW�͊��ɏ���������Ă��܂�." << std::endl;
			return false;
		}
		if (!isGLFWInitialized) {
			glfwSetErrorCallback(ErrorCallback);
			if (glfwInit() != GL_TRUE) {
				return false;
			}
			isGLFWInitialized = true;
		}

		if (!window) {
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
			window = glfwCreateWindow(w, h, title, nullptr, nullptr);
			if (!window) {
				return false;
			}
			glfwMakeContextCurrent(window);
		}

		if (glewInit() != GLEW_OK) {
			std::cerr << "ERROR: GLEW�̏������Ɏ��s���܂���." << std::endl;
			return false;
		}

		glDebugMessageCallback(GLDEBUGPROC(OutputGLDebugMessage), nullptr);

		const GLubyte* renderer = glGetString(GL_RENDERER);
		std::cout << "Renderer: " << renderer << std::endl;
		const GLubyte* version = glGetString(GL_VERSION);
		std::cout << "Version: " << version << std::endl;

		isInitialized = true;
		return true;
	}

	/*
	�E�B���h�E�����ׂ������ׂ�.
	
	@retval true ����.
	@retval false ���Ȃ�.
	*/
	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(window) != 0;
	}

	/*
	�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@��؂�ւ���.
	*/
	void Window::SwapBuffers() const
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	/*
	�L�[��������Ă��邩���ׂ�.
	
	@param key ���ׂ�L�[��ID(GLFW_KEY_A�Ȃ�).
	
	@retval true  �L�[��������Ă���.
	@retval false �L�[��������Ă��Ȃ�.
	*/
	bool Window::IsKeyPressed(int key) const
	{
		if (key < 0 || key >= GLFW_KEY_LAST + 1) {
			return false;
		}
		return keyState[key] != KeyState::release;
	}

	/*
	�L�[�������ꂽ�u�Ԃ����ׂ�.
	
	@param key ���ׂ�L�[��ID(GLFW_KEY_A�Ȃ�).
	
	@retval true  �L�[�������ꂽ�u��.
	@retval false �L�[�������ꂽ�u�Ԃł͂Ȃ�.
	*/
	bool Window::IsKeyDown(int key) const
	{
		if (key < 0 || key >= GLFW_KEY_LAST + 1) {
			return false;
		}
		return keyState[key] == KeyState::press1st;
	}

	/*
	�^�C�}�[������������.
	
	@sa UpdateTimer, GetDeltaTime
	*/
	void Window::InitTimer()
	{
		glfwSetTime(0.0);
		previousTime = 0.0;
		deltaTime = 0.0;
	}

	/*
	�^�C�}�[���X�V����.
	
	@sa InitTimer, GetDeltaTime
	*/
	void Window::UpdateTimer()
	{
		// �o�ߎ��Ԃ��v��.
		const double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// �o�ߎ��Ԃ������Ȃ肷���Ȃ��悤�ɒ���.
		const float upperLimit = 0.25f; // �o�ߎ��ԂƂ��ċ��e�������.
		if (deltaTime > upperLimit) {
			deltaTime = 0.1f;
		}

		UpdateGamePad();
	}

	/*
	�o�ߎ��Ԃ��擾����.
	
	@return ���O��2���UpdateTimer()�Ăяo���̊ԂɌo�߂�������.
	
	@sa InitTimer, UpdateTimer
	*/
	double Window::DeltaTime() const
	{
		return deltaTime;
	}

	/*
	��Ԃ��X�V����.
	*/
	void Window::Update()
	{
		UpdateTimer();
		for (size_t i = 0; i < GLFW_KEY_LAST + 1; ++i) {
			const bool pressed = glfwGetKey(window, i) == GLFW_PRESS;
			if (pressed) {
				if (keyState[i] == KeyState::release) {
					keyState[i] = KeyState::press1st;
				}
				else if (keyState[i] == KeyState::press1st) {
					keyState[i] = KeyState::press;
				}
			}
			else if (keyState[i] != KeyState::release) {
				keyState[i] = KeyState::release;
			}
		}
	}

	/*

	*/
	glm::vec2 Window::GetMousePosition() const
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return glm::vec2(x, y);
	}

	/*

	*/
	int Window::GetMouseButton(int button) const
	{
		return glfwGetMouseButton(window, button);
	}

	/*
	�Q�[���p�b�h�̏�Ԃ��擾����
	
	@return �Q�[���p�b�h�̏��
	*/
	const GamePad& Window::GetGamePad() const
	{
		return gamePad;
	}

	/*
	�Q�[���p�b�h�̃A�i���O���͑��u
	
	@note ������XBOX360�Q�[���p�b�h����
	*/
	enum GAMEPAD_AXIS
	{
		GAMEPAD_AXIS_LEFT_X,  // ���X�e�B�b�N��X��
		GAMEPAD_AXIS_LEFT_Y,  // ���X�e�B�b�N��Y��
		GAMEPAD_AXIS_TRIGGER, // �A�i���O�g���K�[
		GAMEPAD_AXIS_RIGHT_X, // �E�X�e�B�b�N��X��
		GAMEPAD_AXIS_RIGHT_Y, // �E�X�e�B�b�N��Y��
	};

	/*
	�Q�[���p�b�h�̃f�W�^�����͑��uID
	
	@note XBOX360�Q�[���p�b�h����
	*/
	enum GAME_PAD_BUTTON 
	{
		GAMEPAD_BUTTON_A, // A�{�^��
		GAMEPAD_BUTTON_B, // B�{�^��
		GAMEPAD_BUTTON_X, // X�{�^��
		GAMEPAD_BUTTON_Y, // Y�{�^��
		GAMEPAD_BUTTON_L, // L�{�^��
		GAMEPAD_BUTTON_R, // R�{�^��
		GAMEPAD_BUTTON_BACK, // Back�{�^��
		GAMEPAD_BUTTON_START, // Start�{�^��
		GAMEPAD_BUTTON_L_THUMB, // ���X�e�B�b�N�{�^��
		GAMEPAD_BUTTON_R_THUMB, // �E�X�e�B�b�N�{�^��
		GAMEPAD_BUTTON_UP, // ��L�[
		GAMEPAD_BUTTON_RIGHT, // �E�L�[
		GAMEPAD_BUTTON_DOWN, // ���L�[
		GAMEPAD_BUTTON_LEFT, // ���L�[
	};

	/*
	�Q�[���p�b�h�̏�Ԃ��X�V����
	*/
	void Window::UpdateGamePad()
	{
		// buttonDown�𐶐����邽�߂ɁA�X�V�O�̓��͏�Ԃ�ۑ����Ă���
		const uint32_t prevButtons = gamePad.buttons;

		// �A�i���O���͂ƃ{�^�����͂��擾
		int axisCount, buttonCount;
		const float* axis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCount);
		const uint8_t* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		// �����̔z��nullptr�łȂ��A�Œ���K�v�ȃf�[�^���𖞂����Ă���΁A
		// �L���ȃQ�[���p�b�h�Ƃ��Đڑ��Ƃ݂Ȃ�
		if (axis && buttons && axisCount >= 2 && buttonCount >= 8) {
			// �L���ȃQ�[���p�b�h���ڑ�����Ă���ꍇ

			// �����L�[�̓��͏�Ԃ��������āA���X�e�B�b�N�̓��͂Œu��������
			gamePad.buttons &=
				~(GamePad::DPAD_UP | GamePad::DPAD_DOWN | GamePad::DPAD_LEFT | GamePad::DPAD_RIGHT);
			static const float digitalThreashold = 0.3f; // �f�W�^�����͂Ƃ݂Ȃ��������l
			if (axis[GAMEPAD_AXIS_LEFT_Y] >= digitalThreashold)
			{
				gamePad.buttonDown |= GamePad::DPAD_UP;
			}
			else if (axis[GAMEPAD_AXIS_LEFT_Y] <= -digitalThreashold)
			{
				gamePad.buttonDown |= GamePad::DPAD_DOWN;
			}
			if (axis[GAMEPAD_AXIS_LEFT_X] >= digitalThreashold)
			{
				gamePad.buttonDown |= GamePad::DPAD_LEFT;
			}
			else if (axis[GAMEPAD_AXIS_LEFT_X] <= -digitalThreashold)
			{
				gamePad.buttonDown |= GamePad::DPAD_RIGHT;
			}

			// �z��C���f�b�N�X��GamePad�L�[�̑Ή��\
			static const struct
			{
				int dataIndex;
				uint32_t gamePadBit;
			}
			keyMap[] = 
			{
				{ GAMEPAD_BUTTON_A, GamePad::A },
				{ GAMEPAD_BUTTON_B, GamePad::B },
				{ GAMEPAD_BUTTON_X, GamePad::X },
				{ GAMEPAD_BUTTON_Y, GamePad::Y },
				{ GAMEPAD_BUTTON_L, GamePad::L },
				{ GAMEPAD_BUTTON_R, GamePad::R },
				{ GAMEPAD_BUTTON_START, GamePad::START },
				{ GAMEPAD_BUTTON_UP, GamePad::DPAD_UP },
				{ GAMEPAD_BUTTON_DOWN, GamePad::DPAD_DOWN },
				{ GAMEPAD_BUTTON_LEFT, GamePad::DPAD_LEFT },
				{ GAMEPAD_BUTTON_RIGHT, GamePad::DPAD_RIGHT },
			};

			for (const auto& e : keyMap)
			{
				if (buttons[e.dataIndex] == GLFW_PRESS)
				{
					gamePad.buttons |= e.gamePadBit;
				}
				else if (buttons[e.dataIndex] == GLFW_RELEASE)
				{
					gamePad.buttons &= ~e.gamePadBit;
				}
			}
		}
		else
		{
			// �L���ȃQ�[���p�b�h���ڑ�����Ă��Ȃ��̂ŁA�L�[�{�[�h���͂ő�p

			// �z��C���f�b�N�X��GamePad�L�[�̑Ή��\
			static const struct
			{
				int keyCode;
				uint32_t gamePadBit;
			}
			keyMap[] =
			{
				{ GLFW_KEY_J, GamePad::A },
				{ GLFW_KEY_K, GamePad::B },
				{ GLFW_KEY_U, GamePad::X },
				{ GLFW_KEY_I, GamePad::Y },
				{ GLFW_KEY_O, GamePad::L },
				{ GLFW_KEY_L, GamePad::R },
				{ GLFW_KEY_ENTER, GamePad::START },
				{ GLFW_KEY_W, GamePad::DPAD_UP },
				{ GLFW_KEY_S, GamePad::DPAD_DOWN },
				{ GLFW_KEY_A, GamePad::DPAD_LEFT },
				{ GLFW_KEY_D, GamePad::DPAD_RIGHT },
			};

			for (const auto& e : keyMap)
			{
				const int key = glfwGetKey(window, e.keyCode);
				if (key == GLFW_PRESS)
				{
					gamePad.buttons |= e.gamePadBit;
				}
				else if (key == GLFW_RELEASE)
				{
					gamePad.buttons &= ~e.gamePadBit;
				}
			}
		}

		// �O���Update�ŉ�����Ă��Ȃ��āA���񂨂���Ă����炻�̃L�[�̏���buttonDown�Ɋi�[����
		gamePad.buttonDown = gamePad.buttons & ~prevButtons;
	}

} // namespace GLFWEW